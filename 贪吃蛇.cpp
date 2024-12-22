#include <iostream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <thread>
#include <random>
#define X 15 //地图高度
#define Y 40 //地图宽度
class SnakePoint {
public:
	int x;
	int y;
	char body;
	SnakePoint(int x, int y,char body){
		this->x = x;
		this->y = y;
		this->body = body;
	}
};
class Framework{
public:
	int x;
	int y;
	Framework(int x, int y){
		this->x = x;
		this->y = y;
	}
};
class Food{
public:
	int x;
	int y;
	Food(int x, int y){
		this->x = x;
		this->y = y;
	}
};
//函数列表
void input(int* a);//输入方向
void move(int dirct, std::vector<SnakePoint>& V);//蛇移动
void grow(SnakePoint lastpoint, std::vector<SnakePoint>& s);//蛇成长
int main(){
	//随机食物位置 x
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution <> dist(2, X-2);
	//随机食物位置 y
	std::random_device rd2;
	std::mt19937 gen2(rd2());
	std::uniform_int_distribution <> dist2(2, Y-2);
	//蛇运动方向
	int dirct = 0;
	int* dirctX = &dirct;
	//创建空表
	char mainArr[20][50] = { ' ' };
	//蛇和框架
	std::vector<SnakePoint> snake;
	std::vector<Framework> frameworklist;
	//实例化蛇
	snake.push_back(SnakePoint(X/2, Y/2, '@'));
	//创建食物表
	std::vector<Food> foodList;
	foodList.push_back(Food(dist(gen), dist2(gen2)));
	//创建输入方向线程
	std::thread t1(input, dirctX);
	t1.detach();
	bool game = 1;
	//打印总表
	while(1){
		//判断游戏是否继续
		if (game == 0){
			break;
		}
		//移动进行更新坐标
			move(dirct, snake);
		//判断是否吃到食物
		for (std::vector<Food>::iterator it = foodList.begin(); it != foodList.end(); it++){
			if (snake[0].x == it->x && snake[0].y == it->y){
				SnakePoint temp = *(snake.end()-1);
				grow(temp, snake);
				foodList[0].x = dist(gen);
				foodList[0].y = dist2(gen2);
			}
		}
		//判断是否撞墙
		for (std::vector<Framework>::iterator it = frameworklist.begin(); it != frameworklist.end(); it++){
			if (snake[0].x == it->x && snake[0].y == it->y){
				game = 0;
			}
		}
		//实例化框架
		for (int i = 0; i < X; i++){
			for (int j = 0; j < Y; j++){
				if (i == 0 || j == 0 || i == X - 1 || j == Y - 1){
					frameworklist.push_back(Framework(i, j));
				}
				else{
					mainArr[i][j] = ' ';
				}
			}
		}
	//把框架坐标转移到总表
	for (std::vector<Framework>::iterator it = frameworklist.begin(); it != frameworklist.end(); it++){
		mainArr[it->x][it->y] = '*';
	}
	//把蛇的坐标从vector转到总表
	for (std::vector<SnakePoint>::iterator it = snake.begin(); it != snake.end(); it++){
		mainArr[it->x][it->y] = it->body;
	}
	//把食物从vector移动到主表
	for (std::vector<Food>::iterator it = foodList.begin(); it != foodList.end(); it++){
		mainArr[it->x][it->y] = '$';
	}
	//创建ss对象
	std::stringstream ss;
	for (int i = 0; i < sizeof(mainArr) / sizeof(mainArr[0]); i++){
		for (int j = 0; j < sizeof(mainArr[0]) / sizeof(mainArr[0][0]); j++){
			ss << mainArr[i][j];
		}
		ss << '\n';
	}//用ss对象把整个屏幕存储为一个字符串
	std::cout << "\r" << ss.str() << std::flush;
	Sleep(100);
	}
	std::cout << "游戏结束!" << std::endl;
	std::cout << "总分：" << snake.size()-1 << std::endl;
	Sleep(2000);
	system("pause");
	return 0;
}
void input(int* a){
	    while (true) {
        // 检查向上箭头
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            *a = 1;
        }
        // 检查向下箭头
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            *a = 2;
        }
        // 检查向左箭头
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            *a = 3;
        }
        // 检查向右箭头
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            *a = 4;
        }
        Sleep(50);  // 等待 100 毫秒
    }
}

void move(int dirct, std::vector<SnakePoint> &V){
	if (dirct == 1){
		std::vector<SnakePoint> temp;
		for (std::vector<SnakePoint>::iterator it = V.begin(); it != V.end(); it++){
			temp.push_back(*it);
		}
		V[0].x--;
		std::vector<SnakePoint>::iterator mainit = V.begin() + 1;
		std::vector<SnakePoint>::iterator it = temp.begin();
		for (; mainit != V.end(); mainit++,it++){
			mainit->x = it->x;
			mainit->y = it->y;
		}
	}
	else if (dirct == 2){
		std::vector<SnakePoint> temp;
		for (std::vector<SnakePoint>::iterator it = V.begin(); it != V.end(); it++){
			temp.push_back(*it);
		}
		V[0].x++;
		std::vector<SnakePoint>::iterator mainit = V.begin() + 1;
		std::vector<SnakePoint>::iterator it = temp.begin();
		for (; mainit != V.end(); mainit++, it++){
			mainit->x = it->x;
			mainit->y = it->y;
		}
	}
	else if (dirct == 3){
		std::vector<SnakePoint> temp;
		for (std::vector<SnakePoint>::iterator it = V.begin(); it != V.end(); it++){
			temp.push_back(*it);
		}
		V[0].y--;
		std::vector<SnakePoint>::iterator mainit = V.begin() + 1;
		std::vector<SnakePoint>::iterator it = temp.begin();
		for (; mainit != V.end(); mainit++, it++){
			mainit->x = it->x;
			mainit->y = it->y;
		}
	}
	else if (dirct == 4){
		std::vector<SnakePoint> temp;
		for (std::vector<SnakePoint>::iterator it = V.begin(); it != V.end(); it++){
			temp.push_back(*it);
		}
		V[0].y++;
		std::vector<SnakePoint>::iterator mainit = V.begin() + 1;
		std::vector<SnakePoint>::iterator it = temp.begin();
		for (; mainit != V.end(); mainit++, it++){
			mainit->x = it->x;
			mainit->y = it->y;
		}
	}
}
void grow(SnakePoint lastpoint,std::vector<SnakePoint>& s){
	s.push_back(SnakePoint(lastpoint.x, lastpoint.y, '#'));
} 