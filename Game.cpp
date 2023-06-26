#include "Game.h"
#include "Position.h"
#include <time.h>

Game::Game(int _y_size, int _x_size, int _numOfMinesweeper) {
    y_size = _y_size - 1;
    x_size = _x_size - 1;
    numOfMinesweeper = _numOfMinesweeper;

    numOfFlag = 0;
    ground[y_size][x_size] = {0};
    view[y_size][x_size] = {0};
    startTime = time(NULL);
    gameEnded = false;
    pos = Position(y_size, x_size, y_size / 2, x_size / 2);
}

void Game::printGround(int y, int x) {
    
}