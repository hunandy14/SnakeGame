#pragma once
#include <string>



#include <windows.h>
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
public:
	static void out(string str, short x, short y) {
		setPosition(x, y);
		printf("%s", str.c_str());
	}
};



#include <random>
class Coor {
public:
	Coor(){}
	Coor(const int& x, const int& y): x(x), y(y) {}
public:
	void set(const int& x, const int& y) {
		this->x = x, this->y = y;
	}
	friend bool operator==(const Coor& lhs, const Coor& rhs){
		bool cmp=false;
		if (lhs.x == rhs.x and lhs.y == rhs.y) {cmp=true;}
		return cmp;
	}
	friend std::ostream& operator<<(std::ostream& os, const Coor& obj) {
		os << "[" << obj.x << ",  " << obj.y << "]";
		return os;
	}
public:
	static Coor randCoor(int x_min, int x_max, int y_min, int y_max) {
		return Coor(rand(x_min, x_max), rand(y_min, y_max));
	}
private:
	static int rand(int min, int max) {
		static mt19937 gen{random_device{}()};
		uniform_int_distribution<int> distribution{min, --max};
		return distribution(gen);
	}
public:
	int x = 0;
	int y = 0;
};



#include <deque>
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