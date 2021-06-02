#include <iostream>
#include <vector>
#include <random>
#include <deque>
#include <conio.h>
using namespace std;

#include "Unity.hpp"


class Canvas {
public:
	Canvas(){}
	Canvas(string name, unsigned short w, unsigned short h):
		name(name), width(w), height(h)
	{
		ConsoleUnity::hideCursor();
	}
public:
	static void init(string name, unsigned short w, unsigned short h) {
		ConsoleUnity::setTitle(name);
		ConsoleUnity::setSize(w, h);
		ConsoleUnity::hideCursor();
	}
	static void drawSnake(const deque<Coor>& snk_list) {
		for (size_t i = 0; i < snk_list.size(); i++) {
			if (i == 0) out("●", snk_list[i]);
			else out("■", snk_list[i]);
		}
	}
	static void out(string str, const Coor& c) {
		ConsoleUnity::setPosition(c.x, c.y);
		printf("%s", str.c_str());

	}
public:
	string name;
	unsigned short width = 0;
	unsigned short height = 0;
};

class SnakeGame {
public:
	SnakeGame() {
		width = 88;
		height = 28;
		Canvas::init("CHG", width, height);
		Coor start(16, 8);
		for (int i = 5; i >= 0; i--) {
			Coor coor(start.x + (i << 1), start.y);
			snakecoor.emplace_back(coor);
		} Canvas::drawSnake(snakecoor);

		food.set(40, 8);
		Canvas::out("★", food);
		string s = "[" + to_string(food.x) + ", " + to_string(food.y) + "]";

		Coor info{0, height-1};
		Canvas::out(s, Coor{0, height-1});
	}
	Coor getFoodCoor() {
		Coor food = Coor::randCoor(0, width-1, 1, height-2);
		if (food.x%2 and food.x>1) {
			food.x--;
		} else if (food.x ==1) {
			food.x++;
		}
		for (auto&& i : snakecoor) {
			if (i == food) {
				food = getFoodCoor();
			}
		}
		return food;
	}

public:
	Coor getDire(Coor nexthead) {
		static char key = 'd';// 這 static 最初第一次的時候預設是往右邊跑
		if (_kbhit()) {
			char temp = _getch();
			if (temp == 'w' or temp == 'a' or temp == 's' or temp == 'd') {
				if ( (key == 'w' and temp != 's') or (key == 's' and temp != 'w')
				 or  (key == 'a' and temp != 'd') or (key == 'd' and temp != 'a')
				){
					key = temp;
				}
			}
		}
		if (key=='w') {
			nexthead.y -= 1;
		} else if (key=='a') {
			nexthead.x -= 2;
		} else if (key=='s') {
			nexthead.y += 1;
		} else if (key=='d') {
			nexthead.x += 2;
		}
		return nexthead;
	}
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
			ConsoleUnity::out("遊戲結束", 40, 14);
			ConsoleUnity::out("得分" + to_string(score), 40, 16);
			exit(0);
		}
	}



	void move() {
		Canvas::out("得分:" + to_string(score), Coor{ 0, 0 });
		Coor nexthead = getDire(snakecoor[0]);
		snakecoor.push_front(nexthead);
		checkGameOver(score);

		// 吃到食物
		bool getFood=0;
		if (food == snakecoor[0]) {
			score++, getFood=1;
			food = getFoodCoor();
		} Canvas::out("★", food);

		// 前進
		Canvas::out("●", snakecoor[0]);
		Canvas::out("■", snakecoor[1]);
		if (!getFood) {
			Canvas::out("　", snakecoor.back());
			snakecoor.pop_back();
		}
	}

private:
	deque<Coor> snakecoor;
	unsigned short width = 0;
	unsigned short height = 0;
	Coor food{-1, -1};
	int score = 0;
	Canvas cv;
};
//====================================================================================
int main(int argc, char const* argv[]) {
	SnakeGame game;

	while (true) {
		game.move();
		Sleep(100);
	}

	return 0;
}
//====================================================================================
