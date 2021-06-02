#include <iostream>
#include <conio.h>
using namespace std;

#include "Unity.hpp"


class SnakeGame {
public:
	SnakeGame(string name, unsigned short w, unsigned short h) {
		width = w;
		height = h;
		Canvas::init(name, w, h);
		Coor start(16, 8);
		for (int i = 5; i >= 0; i--) {
			Coor coor(start.x + (i << 1), start.y);
			snk_list.emplace_back(coor);
		} Canvas::drawSnake(snk_list);

		food.set(40, 8);
		Canvas::out("★", food);
		string s = "[" + to_string(food.x) + ", " + to_string(food.y) + "]";
		Canvas::out(s, Coor{0, h-1});
	}
	Coor getFoodCoor(unsigned short w, unsigned short h) {
		Coor food = Coor::randCoor(0, w-1, 1, h-2);
		if (food.x%2 and food.x>1) {
			food.x--;
		} else if (food.x ==1) {
			food.x++;
		}
		for (auto&& i : snk_list) {
			if (i == food) {
				food = getFoodCoor(w, h);
			}
		}
		return food;
	}
	void checkGameOver(const int& score, const int& x_max, const int& y_max) {
		bool gameOver = 0;
		//撞墙
		auto&& c = snk_list[0];
		if (c.x >= x_max or c.x < 0 or
			c.y >= y_max or c.y < 0) {
			gameOver = 1;
		}
		//撞自己
		for (int i = 1; i < snk_list.size(); i++) {
			if (snk_list[0] == snk_list[i]) {
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
public:
	void move() {
		Canvas::out("得分:" + to_string(score), Coor{ 0, 0 });
		Coor nexthead = getDire(snk_list[0]);
		snk_list.push_front(nexthead);
		checkGameOver(score, width, height);

		// 吃到食物
		bool getFood=0;
		if (food == snk_list[0]) {
			score++, getFood=1;
			food = getFoodCoor(width, height);
		}
		Canvas::out("★", food);
		string s = "[" + to_string(food.x) + ", " + to_string(food.y) + "]";
		Canvas::out(s, Coor{0, height-1});

		// 前進
		Canvas::out("●", snk_list[0]);
		Canvas::out("■", snk_list[1]);
		if (!getFood) {
			Canvas::out("　", snk_list.back());
			snk_list.pop_back();
		}
	}

private:
	deque<Coor> snk_list;
	unsigned short width = 0;
	unsigned short height = 0;
	Coor food{-1, -1};
	int score = 0;
};
//====================================================================================
int main(int argc, char const* argv[]) {
	int w=88, h=28;

	SnakeGame game("CHG", w, h);
	while (true) {
		game.move();
		Sleep(100);
	}

	return 0;
}
//====================================================================================
