#ifndef GAME_H
#define GAME_H

#include <vector>

class Position;

class Game {
    private:
        static const int VIEW_UNVISIBLE = 0;
        static const int VIEW_VISIBLE = 1;
        static const int VIEW_FLAG = 2;

        static const int GROUND_MINESWEEPER = -1;
        static const int GROUND_VOID = 0;
        static const int GROUND_HINT1 = 1;
        static const int GROUND_HINT2 = 2;
        static const int GROUND_HINT3 = 3;
        static const int GROUND_HINT4 = 4;
        static const int GROUND_HINT5 = 5;
        static const int GROUND_HINT6 = 6;
        static const int GROUND_HINT7 = 7;
        static const int GROUND_HINT8 = 8;

        static const int MSG_DEFAULT = 0;
        static const int MSG_WIN = 1;
        static const int MSG_GAMEOVER = 2;

        int x_size;
        int y_size;
        int numOfMinesweeper;
        int numOfFlag;
        int playCount;
        std::vector<Position*> posOfMinesweeper;
        int** ground;
        int** view;
        double startTime;
        bool gameEnded;
        Position *pos;

    public:
        Game(int y_size, int x_size, int numOfMinesweeper);
        void createNewGround(int startY, int startX);
        void printGround(int y = -1, int x = -1);
        void printInfomationOfGame(int msgType);
        void keyDownEvent();
        void movePoint(int vKey);
        void willChangeGround();
        void didChangeGround();
        void setFlag();
        void openTile();
        void openVoidTile(int y, int x, std::vector<Position*> _check = {});
        void openAllTile(bool isWin);
        bool isGameEnded();
        void startGame();
        ~Game();
};

#endif