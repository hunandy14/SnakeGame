#include <iostream>
#include <conio.h>

#include "Unity.hpp"
using namespace std;


class SnakeGame {
public:
	// 初始化介面
	SnakeGame(string name) {
		int w=100, h=34;
		width = w%2? w+1: w;
		height = h;
		Canvas::init(name, width, height);
		// 初始化蛇身
		Coor start(16, height/4);
		for (int i = 5; i >= 0; i--) {
			Coor coor(start.x + (i << 1), start.y);
			if (i == 0) Canvas::out("●", coor);
			else Canvas::out("■", coor);
			snk_list.emplace_back(coor);
		}
		// 初始化食物
		food.set(start.x+40, start.y);
		Canvas::out("★", food);
		string s = "[" + to_string(food.x) + ", " + to_string(food.y) + "]";
		Canvas::out(s, {0, height-1});
	}
	// 獲取隨機的食物座標
	Coor getFoodCoor(unsigned short w, unsigned short h) {
		Coor food = Coor::randCoor(0, w-1, 1, h-2);
		food.x%2? food.x--: food.x; // 校正奇數(顯示問題只能在偶數欄位)
		for (auto&& i : snk_list) {
			if (i == food) { // 正好位於蛇身重做一個
				food = getFoodCoor(w, h);
			}
		}
		return food;
	}
	// 確認遊戲是否結束
	bool checkGameOver() {
		bool gameOver = 0;
		//撞墙
		auto&& c = snk_list[0];
		if (c.x >= width-1 or c.x < 0 or
			c.y >= height-1 or c.y < 0) {
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
			ConsoleUnity::clearScreen();
			ConsoleUnity::out("遊戲結束", 40, 14);
			ConsoleUnity::out("得分" + to_string(score), 40, 16);
			return 1;
		} return 0;
	}
	// 獲取下一個前進方向
	Coor getDire(Coor nextCoor) {
		static char key = 'd'; // 紀錄上一次方向(預設第一次是向右)
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
			nextCoor.y -= 1;
		} else if (key=='a') {
			nextCoor.x -= 2;
		} else if (key=='s') {
			nextCoor.y += 1;
		} else if (key=='d') {
			nextCoor.x += 2;
		}
		return nextCoor;
	}
public:
	// 運行程序
	bool run() {
		Canvas::out("得分:" + to_string(score), Coor{ 0, 0 });
		Coor nextCoor = getDire(snk_list[0]);
		snk_list.push_front(nextCoor);
		if (checkGameOver()) return 0;
		// 吃到食物
		bool getFood = 0;
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
		return 1;
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
	SnakeGame game("Snake Gmae ------By:CHG");
	while (game.run()) {
		Sleep(100);
	}

	return 0;
}
//====================================================================================
