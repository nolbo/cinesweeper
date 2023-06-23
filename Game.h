#ifndef GAME_H
#define GAME_H

class Game {
    private:
        const int VIEW_UNVISIBLE;
        const int VIEW_VISIBLE;
        const int VIEW_FLAG;

        const int GROUND_VOID;
        const int GROUND_MINESWEEPER;
        const int GROUND_HINT1;
        const int GROUND_HINT2;
        const int GROUND_HINT3;
        const int GROUND_HINT4;
        const int GROUND_HINT5;
        const int GROUND_HINT6;
        const int GROUND_HINT7;
        const int GROUND_HINT8;

        const int GROUND_X_SIZE;
        const int GROUND_Y_SIZE;

        int numOfFlag;
        bool isGameEnded;
};

#endif