#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <string>
#include <stdlib.h>
#include <crtdbg.h>
#include "Game.h"



int main() {
    Game game = Game(60, 28, 336); // 60 28 336
    game.startGame();

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    return 0;
}