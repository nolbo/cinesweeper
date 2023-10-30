#include <iostream>
#include <string>
#include "Game.h"

int main() {
    Game game = Game(60, 28, 336);
    std::cout << std::to_string(game.isGameEnded()) << std::endl;
    game.startGame();
    return 0;
}