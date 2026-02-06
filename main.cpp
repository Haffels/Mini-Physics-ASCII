#include <iostream>
#include <chrono>
#include <thread>

// world size
constexpr int HEIGHT = 15, WIDTH = 20;
// values for calculating acceleration speed
constexpr double G = 9.8, V = 0.0, mass = 1.0;

//program

int world[HEIGHT][WIDTH];

struct Vec2{ int x, y; };

class Board
{
    public:
    static void print()
    {
        std::cout << "\033[2]\033[H";
        for (auto& i : world) {
            for (const int j : i) {
                if (j == 0) std::cout << "•";
                else std::cout << "█";
            }
            std::cout << std::endl;
        }
    }
};

Vec2 genRandomStartPos() {
    int x = rand() % WIDTH;
    return {x, 0};
}

void start() {
    Vec2 blockPos = genRandomStartPos();
    int y = 0;
    double tempV = V;

    while (y + 1 < HEIGHT && world[y + 1][blockPos.x] == 0) {
        //calc for acceliration
        double t = (-tempV + sqrt (tempV * tempV + 2*G*mass)) / G;

        //display movement
        world[y][blockPos.x] = 1;
        Board::print();
        std::this_thread::sleep_for(std::chrono::milliseconds(int(t * 1000)));
        world[y][blockPos.x] = 0;
        tempV = tempV + G*t;
        y++;
    }

    //lock blocks in place
    world[y][blockPos.x] = 1;
    Board::print();
}

[[noreturn]]int main() {
    srand(time(nullptr));
    while (true) { start(); }

}