#pragma once
#include <windows.h>
#include <string>



class ConsoleUnity {
public:
	static void hideCursor(){
		CONSOLE_CURSOR_INFO cursor_info = {1, false};
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	}
	static void setPosition(short x, short y){
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{x, y});
	}
	static void setSize(unsigned short w, unsigned short h) {
		string cmd="mode con cols=" + to_string(w) +  "lines=" + to_string(h);
		system(cmd.c_str());
	}
	static void setTitle(string name) {
		string cmd="title "+name;
		system(cmd.c_str());
	}
	static void out(const char* str) {
		printf("%s", str);
	}
public:
	static void init(string name, unsigned short w, unsigned short h) {
		setTitle("CHG");
		setSize(88, 28);
		hideCursor();
	}
	static void out(string str, short x, short y) {
		setPosition(x, y);
		out(str.c_str());
	}
};



class Coor {
public:
	Coor(): x(0), y(0) {};
	Coor(const int& x, const int& y): x(x), y(y) {}
	friend bool operator==(const Coor& lhs, const Coor& rhs){
		bool cmp=false;
		if (lhs.x == rhs.x and lhs.y == rhs.y) {cmp=true;}
		return cmp;
	}
public:
	void set(const int& x, const int& y) {
		this->x = x;
		this->y = y;
	}
public:
	static Coor randCoor(int x_max, int y_max) {
		return Coor(rand(0, x_max), rand(1, y_max));
	}
	static int rand(int min, int max) {
		static mt19937 gen{random_device{}()};
		uniform_int_distribution<int> distribution{min, --max};
		return distribution(gen);
	}
public:
	friend std::ostream& operator<<(std::ostream& os, const Coor& obj) {
		os << "[" << obj.x << ",  " << obj.y << "]";
		return os;
	}
public:
	int x;
	int y;
};


class Canvas {
public:
	Canvas() {}

	static void drawSnake(const deque<Coor>& snk_list) {
		for (size_t i = 0; i < snk_list.size(); i++) {
			auto&& c = snk_list[i];
			if (i==0) {
				ConsoleUnity::out("●", c.x, c.y);
			} else {
				ConsoleUnity::out("■", c.x, c.y);
			}
		}
	}
	static void out(string str, const Coor& c) {
		ConsoleUnity::out(str.c_str(), c.x, c.y);
	}
};