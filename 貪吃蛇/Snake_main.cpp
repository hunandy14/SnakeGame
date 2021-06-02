#include <iostream>
#include <vector>
#include <random>
#include <deque>
#include <conio.h>
using namespace std;

#include "Unity.hpp"


enum CanvasData {
    Head = -1, // "●"
    Body = -1, // "■"
    Food = -2, // "★"
    Empty = 0  // "　"
};




class SnakeGame {
public:
    SnakeGame() {

    }
    void init() {
		width = 88;
		height = 28;
        ConsoleUnity::init("CHG", width, height);
        Coor start(16, 8);
        for (int i = 5; i >= 0; i--) {
            Coor coor(start.x + (i<<1), start.y);
            snakecoor.emplace_back(coor);
        }
        Canvas::drawSnake(snakecoor);


		food.set(40, 8);
		ConsoleUnity::out("★", food.x, food.y);
    }

	void getNewFood() {
		while ((food = Coor::randCoor(width-1, height-2)).x % 2) {

		}


		Canvas::out("★", food);

		string s = "[" + to_string(food.x) + ", " + to_string(food.y) + "]";
		ConsoleUnity::out(s.c_str(), 0, height-1);
	}

public:
	//enum Dire {W=119, A=97, S=115, D=100};
	Coor degdir(){
		Coor nexthead{snakecoor[0].x, snakecoor[0].y};

		static char key = 'd';// 這 static 最初第一次的時候預設是往右邊跑

		if (_kbhit())
		{
			char temp = _getch();

			if (temp=='w' or temp=='a' or temp=='s' or temp=='d')
			{
				if (
					(key == 'w' && temp != 's') || (key == 's' && temp != 'w') ||
					(key == 'a' && temp != 'd') || (key == 'd' && temp != 'a')
					)
				{
					key = temp;
				}
			}
		}


		switch (key)
		{
		case 'd':
			nexthead.x += 2;
			break;
		case 'a':
			nexthead.x -= 2;
			break;
		case 'w':
			nexthead.y -= 1;
			break;
		case 's':
			nexthead.y += 1;
		}

		//cout << nexthead << endl;
		return nexthead;
	}


	//游戏结束时需要做的事情
	void finmatt(const int score) {
		system("cls");
		ConsoleUnity::out("游戏结束", 40, 14);
		string s = "得分"+to_string(score);
		ConsoleUnity::out(s.c_str(), 40, 16);
		exit(0);
	}

	//游戏结束的情况
	void finishgame(const int score) {
		//撞墙情况
		if (snakecoor[0].x >= width || snakecoor[0].x < 0 || 
			snakecoor[0].y >= height || snakecoor[0].y < 0)
		{
			finmatt(score);
		}

		//撞到自己情况
		for (int i = 1; i < snakecoor.size(); i++)
			if (snakecoor[0] == snakecoor[i]) {
				finmatt(score);
			}
	}





	void move() {
		Coor nexthead = degdir();
		snakecoor.push_front(nexthead);
		Canvas::out("得分:"+to_string(score), Coor{0, 0});//每次移动都在左上角刷新得分
		finishgame(score);
		




		if (snakecoor[0] == food)	//蛇头与食物重合
		{
			Canvas::out("●", snakecoor[0]);//吃到食物时因为直接返回此次移动没有输出蛇身，会少输出一次蛇
											//所以在这里补上蛇移动时需要输出的字符
			Canvas::out("■", snakecoor[1]);

			score++;			 //吃到食物得分+1

			auto a= food;
			getNewFood();//如果蛇头坐标和食物坐标重合则重新产生一个食物
			return;				 //直接结束本次移动
		}

		//遍历容器，判断食物与蛇身是否重合并输出整条蛇
		for (int i = 0; i < snakecoor.size(); i++)
		{
			if (!i)								//头部输出圆形否则输出方块
				Canvas::out("●", snakecoor[i]);
			else
				Canvas::out("■", snakecoor[i]);

			//如果食物刷新到了蛇身上，则重新产生一个食物
			if (snakecoor[i] == food){
				getNewFood();
			}
		}





		Coor c=snakecoor.back();
		ConsoleUnity::out("　", c.x, c.y);
		snakecoor.pop_back();
		//Canvas::drawSnake(snakecoor);
	}

	void printHead() {
		cout << snakecoor[0];
	}

private:
    deque<Coor> snakecoor;
	unsigned short width  = 0;
	unsigned short height = 0;
	Coor food;
	int score = 0;
};
//====================================================================================
int main(int argc, char const* argv[]) {
    SnakeGame game;
    game.init();

	

	while (true) {
		game.move();
		Sleep(100);
	}
    //cout << _getch() << endl;
    return 0;
}
//====================================================================================
