#include <iostream>
#include <vector>
#include <random>
#include <deque>
#include <conio.h>
using namespace std;

#include "Unity.hpp"


enum CanvasData {
    Head = -1, // "¡´"
    Body = -1, // "¡½"
    Food = -2, // "¡¹"
    Empty = 0  // "¡@"
};


class Canvas {
public:
    Canvas() {}

    static void draw(const deque<Coor>& snk_list) {
        for (auto&& coor : snk_list) {
            
        }
        for (size_t i = 0; i < snk_list.size(); i++) {
            auto&& coor = snk_list[i];
            if (i==0) {
                ConsoleUnity::out("¡´", coor.x, coor.y);
            } else {
                ConsoleUnity::out("¡½", coor.x, coor.y);
            }
        }
    }
};

class SnakeGame {
public:
    SnakeGame() {

    }
    void init() {
        ConsoleUnity::init("CHG", 88, 28);
        Coor start(16, 8);
        for (int i = 5; i >= 0; i--) {
            Coor coor(start.x + (i<<1), start.y);
            snk_list.emplace_back(coor);
        }
        Canvas::draw(snk_list);
    }


private:
    deque<Coor> snk_list;
};
//====================================================================================
int main(int argc, char const* argv[]) {
    SnakeGame game;
    game.init();

    getchar();
    return 0;
}
//====================================================================================
