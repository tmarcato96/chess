#include <iostream>
#include "game.h"

int main() {
    Game* chess = new Game();

    chess->run();

    delete chess;
}