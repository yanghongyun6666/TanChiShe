#include <iostream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <thread>
#include <random>
#define X 15 //��ͼ�߶�
#define Y 40 //��ͼ���
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
//�����б�
void input(int* a);//���뷽��
void move(int dirct, std::vector<SnakePoint>& V);//���ƶ�
void grow(SnakePoint lastpoint, std::vector<SnakePoint>& s);//�߳ɳ�
int main(){
	//���ʳ��λ�� x
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution <> dist(2, X-2);
	//���ʳ��λ�� y
	std::random_device rd2;
	std::mt19937 gen2(rd2());
	std::uniform_int_distribution <> dist2(2, Y-2);
	//���˶�����
	int dirct = 0;
	int* dirctX = &dirct;
	//�����ձ�
	char mainArr[20][50] = { ' ' };
	//�ߺͿ��
	std::vector<SnakePoint> snake;
	std::vector<Framework> frameworklist;
	//ʵ������
	snake.push_back(SnakePoint(X/2, Y/2, '@'));
	//����ʳ���
	std::vector<Food> foodList;
	foodList.push_back(Food(dist(gen), dist2(gen2)));
	//�������뷽���߳�
	std::thread t1(input, dirctX);
	t1.detach();
	bool game = 1;
	//��ӡ�ܱ�
	while(1){
		//�ж���Ϸ�Ƿ����
		if (game == 0){
			break;
		}
		//�ƶ����и�������
			move(dirct, snake);
		//�ж��Ƿ�Ե�ʳ��
		for (std::vector<Food>::iterator it = foodList.begin(); it != foodList.end(); it++){
			if (snake[0].x == it->x && snake[0].y == it->y){
				SnakePoint temp = *(snake.end()-1);
				grow(temp, snake);
				foodList[0].x = dist(gen);
				foodList[0].y = dist2(gen2);
			}
		}
		//�ж��Ƿ�ײǽ
		for (std::vector<Framework>::iterator it = frameworklist.begin(); it != frameworklist.end(); it++){
			if (snake[0].x == it->x && snake[0].y == it->y){
				game = 0;
			}
		}
		//ʵ�������
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
	//�ѿ������ת�Ƶ��ܱ�
	for (std::vector<Framework>::iterator it = frameworklist.begin(); it != frameworklist.end(); it++){
		mainArr[it->x][it->y] = '*';
	}
	//���ߵ������vectorת���ܱ�
	for (std::vector<SnakePoint>::iterator it = snake.begin(); it != snake.end(); it++){
		mainArr[it->x][it->y] = it->body;
	}
	//��ʳ���vector�ƶ�������
	for (std::vector<Food>::iterator it = foodList.begin(); it != foodList.end(); it++){
		mainArr[it->x][it->y] = '$';
	}
	//����ss����
	std::stringstream ss;
	for (int i = 0; i < sizeof(mainArr) / sizeof(mainArr[0]); i++){
		for (int j = 0; j < sizeof(mainArr[0]) / sizeof(mainArr[0][0]); j++){
			ss << mainArr[i][j];
		}
		ss << '\n';
	}//��ss�����������Ļ�洢Ϊһ���ַ���
	std::cout << "\r" << ss.str() << std::flush;
	Sleep(100);
	}
	std::cout << "��Ϸ����!" << std::endl;
	std::cout << "�ܷ֣�" << snake.size()-1 << std::endl;
	Sleep(2000);
	system("pause");
	return 0;
}
void input(int* a){
	    while (true) {
        // ������ϼ�ͷ
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            *a = 1;
        }
        // ������¼�ͷ
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            *a = 2;
        }
        // ��������ͷ
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            *a = 3;
        }
        // ������Ҽ�ͷ
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            *a = 4;
        }
        Sleep(50);  // �ȴ� 100 ����
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