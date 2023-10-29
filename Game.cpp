#include "Game.h"
#include "Position.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <format>

using namespace std;

string rjust(string srcStr, string fillStr, int width) {
    return string("").append(fillStr, width - srcStr.length()).append(srcStr);
}

string ljust(string srcStr, string fillStr, int width) {
    return string("").append(srcStr).append(fillStr, width - srcStr.length());
}

Game::Game(int _y_size, int _x_size, int _numOfMinesweeper) {
    y_size = _y_size - 1;
    x_size = _x_size - 1;
    numOfMinesweeper = _numOfMinesweeper;

    numOfFlag = 0;
    playCount = 0;
    ground[y_size][x_size] = {0};
    view[y_size][x_size] = {0};
    startTime = time(NULL);
    gameEnded = false;
    pos = Position(y_size, x_size, y_size / 2, x_size / 2);
    posOfMinesweeper[numOfMinesweeper] = {};
}

void Game::startGame() {
    printGround(pos.getY() - 1, pos.getX() - 1);
    printInfomationOfGame(MSG_DEFAULT);

    while(!gameEnded) {
        keyDownEvent();
    }
}

void Game::createNewGround(int startY, int startX) {
    int count_mine = numOfMinesweeper;
    srand(time(NULL));
    
    while (count_mine > 0) {
        Position crrPos = Position(rand() % x_size, rand() % y_size);
        int y = crrPos.getY();
        int x = crrPos.getX();

        if (y == startY && x == startX) {
            continue;
        }

        if (ground[y][x] != -1) {
            Position recursionPos[9] = {
                Position(startY - 1, startX - 1), Position(startY - 1, startX), Position(startY - 1, startX + 1), 
                Position(startY,     startX - 1), Position(startY,     startX), Position(startY,     startX + 1), 
                Position(startY + 1, startX - 1), Position(startY + 1, startX), Position(startY + 1, startX + 1)
            };

            bool isCrrPosInSrrPos = false;

            for (Position srrPos : recursionPos) {
                if (srrPos == crrPos) {
                    isCrrPosInSrrPos = true;
                }
            }

            if (!isCrrPosInSrrPos) {
                ground[y][x] = -1;
                posOfMinesweeper[sizeof(posOfMinesweeper) / sizeof(*posOfMinesweeper)] = crrPos;

                for (int i = ((y > 0) ? y - 1 : 0); i < ((y < y_size - 1) ? y + 2 : y_size); i ++) { // y축
                    for (int j = ((x > 0) ? x - 1 : 0); j < ((x < x_size - 1) ? x + 2 : x_size); j ++) { // x축
                        if (ground[i][j] == -1 || (startX == j && startY == i)) {
                            continue;
                        }
                        ground[i][j] += 1;
                    }
                }
                count_mine -= 1;
            }
        }
    }
}

void Game::printGround(int y = -1, int x = -1) {
    system("cls");
    string yNum = "     ";

    for (int i = 0; i < x_size; i ++) {
        if (((i + 1) / 10) % 2 == 0) {
            yNum.append("\033[95m" + to_string((i + 1) / 10) + "\033[0m ");
        } else {
            yNum.append("\033[35m" + to_string((i + 1) / 10) + "\033[0m ");
        }
    }
    yNum += "\n     ";
    for (int i = 0; i < x_size; i ++) {
        if (((i + 1) / 10) % 2 == 0) {
            yNum.append("\033[95m" + to_string((i + 1) % 10) + "\033[0m ");
        } else {
            yNum.append("\033[35m" + to_string((i + 1) % 10) + "\033[0m ");
        }
    }
    yNum.append("\n     ").append("━", x_size * 2 - 1);
    cout << yNum << endl;
    for (int i = 0; i < y_size; i ++) {
        string result;

        if (((i + 1) / 10) % 2 == 0) {
            result = "\033[95m" + rjust(to_string(i + 1), "0", 2) + "\033[0m │ ";
        } else {
            result = "\033[35m" + rjust(to_string(i + 1), "0", 2) + "\033[0m │ ";
        }

        for (int j = 0; j < x_size; j ++) {
            if (x != -1 && y != -1 && x == j && y == i)  {
                result.append("\033[1m\033[7m");
            }
            switch (view[i][j]) {
                case VIEW_UNVISIBLE :
                    result.append("■");
                    break;
                case VIEW_VISIBLE :
                    if (ground[i][j] == 0) {
                        result.append("\033[90m□\033[0m");
                    } else {
                        if (ground[i][j] == -1) {
                            result.append("\033[31m●\033[0m");
                        } else {
                            switch (ground[i][j]) {
                                case GROUND_HINT1 : result.append("\033[96m"); break;
                                case GROUND_HINT2 : result.append("\033[94m"); break;
                                case GROUND_HINT3 : result.append("\033[92m"); break;
                                case GROUND_HINT4 : result.append("\033[93m"); break;
                                case GROUND_HINT5 : result.append("\033[91m"); break;
                                case GROUND_HINT6 : result.append("\033[95m"); break;
                                case GROUND_HINT7 : result.append("\033[35m"); break;
                                case GROUND_HINT8 : result.append("\033[97m"); break;
                            }
                            result.append(to_string(ground[i][j]) + "\033[0m");
                        }
                    }
                    break;
                case VIEW_FLAG :
                    result.append("\033[33m▶\033[0m");
                    break;
            }
            if (x != -1 && y != -1 && x == j && y == i) {
                result.append("\033[0m");
            }
            result.append(" ");
        }
        cout << result << endl;
    }
}

void Game::printInfomationOfGame(int msgType) {
    const int DEFAULT_LENGTH_OF_LINE = 23 + (x_size * 2 - 1);

    double crrTime  = time(NULL);
    int playTime    = crrTime - startTime;
    string countMsg = "Count(s): \033[33m" + to_string(playCount) + "\033[0m";
    string timeMsg  = "Playtime: \033[35m" + rjust(to_string(playTime / 3600), "0", 2) + ":" + rjust(to_string(playTime % 3600 / 60), "0", 2) + ":" + rjust(to_string(playTime % 3600 % 60), "0", 2) + "\033[0m";
    
    switch (msgType) {
        case MSG_DEFAULT :
            cout << string(DEFAULT_LENGTH_OF_LINE - 18, '=') << endl;
            break;
        case MSG_WIN :
            cout << string(x_size, '=') << "\033[94mWIN!\033[0m" << string(x_size, '=') << endl;
            break;
        case MSG_GAMEOVER :
            cout << string(x_size - 2, '=') << "\033[90mGameOver\033[0m" << string(x_size - 2, '=') << endl;
            break;
    }

    cout << countMsg << rjust(timeMsg, " ", DEFAULT_LENGTH_OF_LINE - countMsg.length()) << endl;
    cout << "Point: \033[1m\033[36m(" + rjust(to_string(pos.getX()), "0", 2) + ", " + rjust(to_string(pos.getY()), "0", 2) + ")\033[0m";
    
    if (playCount == 0) {
        cout << string(DEFAULT_LENGTH_OF_LINE - 18, '=') << endl;
        cout << "Move      " << rjust("\033[44m[←]\033[0m \033[44m[→]\033[0m \033[44m[↑]\033[0m \033[44m[↓]\033[0m", " ", DEFAULT_LENGTH_OF_LINE + 8) << endl;
        cout << "Open Tile " << rjust("\033[42m\033[30m[SpaceBar]\033[0m", " ", DEFAULT_LENGTH_OF_LINE - 14) << endl;
        cout << "Flag      " << rjust("\033[43m\033[30m[F]\033[0m", " ", DEFAULT_LENGTH_OF_LINE - 14) << endl;
        cout << "Exit Game " << rjust("\033[101m\033[30m[Esc]\033[0m", " ", DEFAULT_LENGTH_OF_LINE - 13) << endl;
    }
}

void Game::movePoint(int vKey) {
    switch (vKey) {
        case VK_LEFT :
            pos.moveX(-1);
            break;
        case VK_RIGHT :
            pos.moveX(1);
            break;
        case VK_UP :
            pos.moveY(-1);
            break;
        case VK_DOWN :
            pos.moveY(1);
            break;
    }
    didChangeGround();
}

void Game::keyDownEvent() {
    if (GetAsyncKeyState(VK_LEFT)) {
        movePoint(VK_LEFT);
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        movePoint(VK_RIGHT);
    }
    if (GetAsyncKeyState(VK_UP)) {
        movePoint(VK_UP);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        movePoint(VK_DOWN);
    }
    if (GetAsyncKeyState(0x46)) { // F
        setFlag();
    }
    if (GetAsyncKeyState(VK_SPACE)) {
        openTile();
    }
    if (GetAsyncKeyState(VK_ESCAPE)) {
        gameEnded = true;
    }
}

void Game::willChangeGround() {
    playCount += 1;
    if (playCount == 1) {
        createNewGround(pos.getY() - 1, pos.getX() - 1);
    }
}

void Game::didChangeGround() {
    if (isGameEnded()) {
        openAllTile(true);
        printGround(pos.getY() - 1, pos.getX() - 1);
        printInfomationOfGame(MSG_WIN);
    } else {
        printGround(pos.getY() - 1, pos.getX() - 1);
        printInfomationOfGame(MSG_DEFAULT);
    }
}

void Game::setFlag() {
    
}

void Game::openTile() {

}

void Game::openAllTile(bool isWin) {
    fill(view[0], view[y_size], 1); // view배열의 값을 1로 초기화

    for (int i = 0; i < numOfMinesweeper; i ++) {
        view[posOfMinesweeper[i].getY()][posOfMinesweeper[i].getX()] = (isWin) ? 2 : 1;
    }
}

bool Game::isGameEnded() {
    for (int i = 0; i < y_size; i ++) {
        for (int j = 0; j < x_size; j ++) {
            switch (view[i][j]) {
                case 0 :
                    if (ground[i][j] != -1) {
                        return false;
                    }
                    break;
                case 2 :
                    if (ground[i][j] != -1) {
                        return false;
                    }
                    break;
            }
        }
    }
    gameEnded = true;
    return true;
}
