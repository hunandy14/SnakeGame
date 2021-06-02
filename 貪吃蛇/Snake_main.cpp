#include <iostream>
#include <vector>
#include <random>
#include <deque>
#include <conio.h>
using namespace std;

#include "Unity.hpp"


class Canvas {
public:
	Canvas() {}

	static void drawSnake(const deque<Coor>& snk_list) {
		for (size_t i = 0; i < snk_list.size(); i++) {
			auto&& c = snk_list[i];
			if (i == 0) {
				ConsoleUnity::out("●", c.x, c.y);
			} else {
				ConsoleUnity::out("■", c.x, c.y);
			}
		}
	}
	static void out(string str, const Coor& c) {
		ConsoleUnity::out(str.c_str(), c.x, c.y);
	}
private:
	unsigned short width = 0;
	unsigned short height = 0;
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
			Coor coor(start.x + (i << 1), start.y);
			snakecoor.emplace_back(coor);
		}
		Canvas::drawSnake(snakecoor);


		food.set(40, 8);
		ConsoleUnity::out("★", food.x, food.y);
	}

	void getNewFood() {
		do {
			food = Coor::randCoor(0, width-1, 1, height-2);
		} while (food.x % 2);

		string s = "[" + to_string(food.x) + ", " + to_string(food.y) + "]";
		ConsoleUnity::out(s.c_str(), 0, height - 1);
	}

public:
	Coor degdir(Coor nexthead) {
		static char key = 'd';// 這 static 最初第一次的時候預設是往右邊跑
		if (_kbhit()) {
			char temp = _getch();
			if (temp == 'w' or temp == 'a' or temp == 's' or temp == 'd') {
				if ((key == 'w' && temp != 's') || (key == 's' && temp != 'w') ||
					(key == 'a' && temp != 'd') || (key == 'd' && temp != 'a'))
				{
					key = temp;
				}
			}
		}
		switch (key) {
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
		return nexthead;
	}

	//游戏结束的情况
	void checkGameOver(const int& score) {
		bool gameOver = 0;
		//撞墙
		if (snakecoor[0].x >= width or snakecoor[0].x < 0 or
			snakecoor[0].y >= height or snakecoor[0].y < 0) {
			gameOver = 1;
		}
		//撞自己
		for (int i = 1; i < snakecoor.size(); i++) {
			if (snakecoor[0] == snakecoor[i]) {
				gameOver = 1;
			}
		}
		// 遊戲結束
		if (gameOver) {
			system("cls");
			ConsoleUnity::out("游戏结束", 40, 14);
			ConsoleUnity::out("得分" + to_string(score), 40, 16);
			exit(0);
		}
	}



	void move() {
		Canvas::out("得分:" + to_string(score), Coor{ 0, 0 });

		Coor nexthead = degdir(snakecoor[0]);

		snakecoor.push_front(nexthead);
		checkGameOver(score);

		Canvas::out("●", snakecoor[0]);
		Canvas::out("■", snakecoor[1]);


		// 吃到食物
		bool getFood=0;
		if (snakecoor[0] == food) {
			score++;
			getFood=1;
			getNewFood();
		}
		//檢查食物是不是在蛇身上
		for (int i = 0; i < snakecoor.size(); i++) {
			if (snakecoor[i] == food) {
				getNewFood();
			}
		}
		Canvas::out("★", food);

		if (!getFood) {
			Canvas::out("　", snakecoor.back());
			snakecoor.pop_back();
		}
	}

private:
	deque<Coor> snakecoor;
	unsigned short width = 0;
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

	return 0;
}
//====================================================================================
