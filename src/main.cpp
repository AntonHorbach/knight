#include <iostream>

#include "game.hpp"

int main() {
    Game game;

    if(!game.init("knight", 640, 480, true)) {
        return 1;
    }

    return game.exec();
}