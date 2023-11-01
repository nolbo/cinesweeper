#define _CRTDBG_MAP_ALLOC

#include "Game.h"
#include "Position.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

using namespace std;

string repeat_str(string repeat, int num) {
    string str = repeat;

    for (int i = 0; i < num - 1; i++) {
        str.append(repeat);
    }

    return str;
}

string rjust(string srcStr, string fillStr, size_t width) {
    size_t fillStr_length = width - srcStr.length();
    return (fillStr_length > 0) ? string("").append(repeat_str(fillStr, fillStr_length)).append(srcStr) : srcStr;
}

string ljust(string srcStr, string fillStr, int width) {
    size_t fillStr_length = width - srcStr.length();
    return (fillStr_length > 0) ? string("").append(srcStr).append(repeat_str(fillStr, fillStr_length)) : srcStr;
}

Game::Game(int _x_size, int _y_size, int _numOfMinesweeper) {
    x_size = _x_size - 1;
    y_size = _y_size - 1;
    numOfMinesweeper = _numOfMinesweeper;

    numOfFlag = 0;
    playCount = 0;
    startTime = time(NULL);
    gameEnded = false;
    pos = Position((x_size + 1), (y_size + 1), (x_size + 1) / 2, (y_size + 1) / 2);
    posOfMinesweeper = {};

    ground = new int* [y_size + 1];
    view = new int* [y_size + 1];

    for (int y = 0; y < y_size + 1; y ++) {
        ground[y] = new int[x_size + 1];
        view[y] = new int[x_size + 1];
    }

    for (int i = 0; i < y_size + 1; i++) {
        for (int j = 0; j < x_size + 1; j++) {
            ground[i][j] = 0;
            view[i][j] = 0;
        }
    }
}

void Game::startGame() {
    printGround(pos.getY() - 1, pos.getX() - 1);
    printInfomationOfGame(MSG_DEFAULT);

    while (!gameEnded) {
        keyDownEvent();
    }
}

void Game::createNewGround(int startY, int startX) {
    Position startPos = Position(startX, startY);
    int count_mine = numOfMinesweeper;
    srand(time(NULL));

    while (count_mine > 0) {
        Position crrPos = Position(rand() % (x_size + 1), rand() % (y_size + 1));
        int y = crrPos.getY();
        int x = crrPos.getX();

        if (y == startY && x == startX) {
            continue;
        }

        if (ground[y][x] != -1) {
            Position srrStartPos[9] = {
                Position(startX - 1, startY - 1), Position(startX - 1, startY), Position(startX - 1, startY + 1),
                Position(startX,     startY - 1), startPos,                     Position(startX,     startY + 1),
                Position(startX + 1, startY - 1), Position(startX + 1, startY), Position(startX + 1, startY + 1)
            };

            bool isCrrPosInSrrPos = false;

            for (Position srrStart : srrStartPos) {
                if (srrStart == crrPos) {
                    isCrrPosInSrrPos = true;
                }
            }

            if (!isCrrPosInSrrPos) {
                ground[y][x] = GROUND_MINESWEEPER;
                posOfMinesweeper.push_back(crrPos);

                Position srrMnswprPos[8] = {
                    Position(x - 1, y - 1), Position(x - 1, y), Position(x - 1, y + 1),
                    Position(x,     y - 1),                     Position(x,     y + 1),
                    Position(x + 1, y - 1), Position(x + 1, y), Position(x + 1, y + 1)
                };

                for (Position srrMnswpr : srrMnswprPos) {
                    if ((srrMnswpr.getX() < 0 || srrMnswpr.getX() > x_size) || (srrMnswpr.getY() < 0 || srrMnswpr.getY() > y_size)) {
                        continue;
                    }
                    if (ground[srrMnswpr.getY()][srrMnswpr.getX()] == GROUND_MINESWEEPER || srrMnswpr == startPos) {
                        continue;
                    }
                    ground[srrMnswpr.getY()][srrMnswpr.getX()] += 1;
                }
                count_mine -= 1;
            }
        }
    }
}

void Game::printGround(int y, int x) {
    system("cls");
    string yNum = "     ";

    for (int i = 0; i < x_size + 1; i++) {
        if (((i + 1) / 10) % 2 == 0) {
            yNum.append("\033[95m" + to_string((i + 1) / 10) + "\033[0m ");
        }
        else {
            yNum.append("\033[35m" + to_string((i + 1) / 10) + "\033[0m ");
        }
    }
    yNum += "\n     ";
    for (int i = 0; i < x_size + 1; i++) {
        if (((i + 1) / 10) % 2 == 0) {
            yNum.append("\033[95m" + to_string((i + 1) % 10) + "\033[0m ");
        }
        else {
            yNum.append("\033[35m" + to_string((i + 1) % 10) + "\033[0m ");
        }
    }

    yNum.append("\n     ").append(repeat_str("¦¬", (x_size + 1) * 2 - 1));
    cout << yNum << endl;

    for (int i = 0; i < y_size + 1; i ++) {
        string result;

        if (((i + 1) / 10) % 2 == 0) {
            result = "\033[95m" + rjust(to_string(i + 1), "0", 2) + "\033[0m ¦¢ ";
        }
        else {
            result = "\033[35m" + rjust(to_string(i + 1), "0", 2) + "\033[0m ¦¢ ";
        }

        for (int j = 0; j < x_size + 1; j++) {
            if (x != -1 && y != -1 && x == j && y == i) {
                result.append("\033[1m\033[7m"); // Replace forground color with background color
            }
            switch (view[i][j]) {
                case VIEW_UNVISIBLE :
                    result.append("¡á");
                    break;
                case VIEW_VISIBLE :
                    if (ground[i][j] == GROUND_VOID) {
                        result.append("\033[90m¡à\033[0m"); // Bright Black
                    }
                    else {
                        if (ground[i][j] == GROUND_MINESWEEPER) {
                            result.append("\033[31m¡Ü\033[0m"); // Red
                        }
                        else {
                            switch (ground[i][j]) {
                            case GROUND_HINT1: result.append("\033[96m"); break; // Bright Cyan
                            case GROUND_HINT2: result.append("\033[94m"); break; // Bright Blue
                            case GROUND_HINT3: result.append("\033[92m"); break; // Bright Green
                            case GROUND_HINT4: result.append("\033[93m"); break; // Bright Yellow
                            case GROUND_HINT5: result.append("\033[91m"); break; // Bright Red
                            case GROUND_HINT6: result.append("\033[95m"); break; // Bright Magenta
                            case GROUND_HINT7: result.append("\033[35m"); break; // Magenta
                            case GROUND_HINT8: result.append("\033[97m"); break; // Bright White
                            }
                            result.append(to_string(ground[i][j]) + "\033[0m");
                        }
                    }
                    break;
                case VIEW_FLAG :
                    result.append("\033[33m¢º\033[0m"); // Yellow
                    break;
                case VIEW_QUESTION :
                    result.append("\033[95m?\033[0m"); // Light Magenta
                    break;
                default :
                    result.append("?");
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
    const size_t DEFAULT_LENGTH_OF_LINE = 23 + (x_size * 2 - 1);

    double crrTime = time(NULL);
    int playTime = crrTime - startTime;
    string countMsg = "Count(s): \033[33m" + to_string(playCount) + "\033[0m";
    string timeMsg = "Playtime: \033[35m" + rjust(to_string(playTime / 3600), "0", 2) + ":" + rjust(to_string(playTime % 3600 / 60), "0", 2) + ":" + rjust(to_string(playTime % 3600 % 60), "0", 2) + "\033[0m";

    switch (msgType) {
    case MSG_DEFAULT:
        cout << string(DEFAULT_LENGTH_OF_LINE - 16, '=') << endl;
        break;
    case MSG_WIN:
        cout << string(x_size, '=') << " \033[94mWIN!\033[0m " << string(x_size, '=') << endl;
        break;
    case MSG_GAMEOVER:
        cout << string(x_size - 2, '=') << " \033[90mGameOver\033[0m " << string(x_size - 2, '=') << endl;
        break;
    }

    cout << countMsg << rjust(timeMsg, " ", DEFAULT_LENGTH_OF_LINE - countMsg.length() + 2) << endl;
    cout << "Point: \033[1m\033[36m(" + rjust(to_string(pos.getX()), "0", 2) + ", " + rjust(to_string(pos.getY()), "0", 2) + ")\033[0m" << endl;

    if (playCount == 0) {
        cout << string(DEFAULT_LENGTH_OF_LINE - 16, '=') << endl;
        cout << "Move      " << rjust("\033[44m[¡ç]\033[0m \033[44m[¡æ]\033[0m \033[44m[¡è]\033[0m \033[44m[¡é]\033[0m", " ", DEFAULT_LENGTH_OF_LINE + 14) << endl;
        cout << "Open Tile " << rjust("\033[42m\033[30m[SpaceBar]\033[0m", " ", DEFAULT_LENGTH_OF_LINE - 12) << endl;
        cout << "Flag      " << rjust("\033[43m\033[30m[F]\033[0m", " ", DEFAULT_LENGTH_OF_LINE - 12) << endl;
        cout << "Exit Game " << rjust("\033[101m\033[30m[Esc]\033[0m", " ", DEFAULT_LENGTH_OF_LINE - 11) << endl;
    }
}

void Game::movePoint(int vKey) {
    switch (vKey) {
    case VK_LEFT:
        pos.moveX(-1);
        break;
    case VK_RIGHT:
        pos.moveX(1);
        break;
    case VK_UP:
        pos.moveY(-1);
        break;
    case VK_DOWN:
        pos.moveY(1);
        break;
    }
    didChangeGround();
}

void Game::keyDownEvent() {
    if (_kbhit()) {
        int key = _getch();

        switch (key) {
        case 0x46 : case 0x66 : // F, f
            setFin();
            break;
        case 0x20 : // Space
            openTile();
            break;
        case 0x1B : // Esc
            gameEnded = true;
            break;
        case 224 : // Arrow Key
            switch (_getch()) {
            case 72 : // Up
                movePoint(VK_UP);
                break;
            case 80 : // Down
                movePoint(VK_DOWN);
                break;
            case 75 : // Left
                movePoint(VK_LEFT);
                break;
            case 77 : //Right
                movePoint(VK_RIGHT);
                break;
            }
        }
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
    }
    else {
        printGround(pos.getY() - 1, pos.getX() - 1);
        printInfomationOfGame(MSG_DEFAULT);
    }
}

void Game::setFin() {
    willChangeGround();

    switch (view[pos.getY() - 1][pos.getX() - 1]) {
    case VIEW_UNVISIBLE :
        view[pos.getY() - 1][pos.getX() - 1] = VIEW_FLAG;
        break;
    case VIEW_FLAG :
        view[pos.getY() - 1][pos.getX() - 1] = VIEW_QUESTION;
        break;
    case VIEW_QUESTION :
        view[pos.getY() - 1][pos.getX() - 1] = VIEW_UNVISIBLE;
        break;
    default:
        break;
    }

    didChangeGround();
}

void Game::openTile() {
    willChangeGround();

    if (view[pos.getY() - 1][pos.getX() - 1] != VIEW_VISIBLE) {
        if (view[pos.getY() - 1][pos.getX() - 1] == VIEW_FLAG || view[pos.getY() - 1][pos.getX() - 1] == VIEW_QUESTION) {
            view[pos.getY() - 1][pos.getX() - 1] = VIEW_UNVISIBLE;
        }
        else {
            switch (ground[pos.getY() - 1][pos.getX() - 1]) {
            case GROUND_MINESWEEPER :
                openAllTile(false);
                printGround();
                printInfomationOfGame(MSG_GAMEOVER);
                gameEnded = true;
                return;
            case GROUND_VOID :
                openVoidTile(pos.getY() - 1, pos.getX() - 1);
                break;
            default :
                view[pos.getY() - 1][pos.getX() - 1] = VIEW_VISIBLE;
                if (view[pos.getY() - 1][pos.getX() - 1] == VIEW_FLAG) {
                    view[pos.getY() - 1][pos.getX() - 1] = VIEW_UNVISIBLE;
                }
            }
        }
    }

    didChangeGround();
}

void Game::openVoidTile(int y, int x) {
    view[y][x] = VIEW_VISIBLE;

    if (ground[y][x] != GROUND_VOID) {
        return;
    }

    Position recursionPos[8] = {
        Position(x - 1, y - 1), Position(x - 1, y), Position(x - 1, y + 1),
        Position(x,     y - 1),                     Position(x,     y + 1),
        Position(x + 1, y - 1), Position(x + 1, y), Position(x + 1, y + 1)
    };

    for (Position srrPos : recursionPos) {
        if ((srrPos.getY() > y_size || srrPos.getY() < 0) || (srrPos.getX() > x_size || srrPos.getX() < 0)) {
            continue;
        }
        if (view[srrPos.getY()][srrPos.getX()] == VIEW_VISIBLE || ground[srrPos.getY()][srrPos.getX()] == GROUND_MINESWEEPER) {
            continue;
        }

        openVoidTile(srrPos.getY(), srrPos.getX());
    }
}

void Game::openAllTile(bool isWin) {
    for (int i = 0; i < y_size + 1; i++) {
        for (int j = 0; j < x_size + 1; j++) {
            view[i][j] = VIEW_VISIBLE;
        }
    }

    for (Position mnswpr : posOfMinesweeper) {
        view[mnswpr.getY()][mnswpr.getX()] = (isWin) ? VIEW_FLAG : VIEW_VISIBLE;
    }
}

bool Game::isGameEnded() {
    for (int i = 0; i < y_size + 1; i++) {
        for (int j = 0; j < x_size + 1; j++) {
            switch (view[i][j]) {
            case VIEW_UNVISIBLE: case VIEW_FLAG:
                if (ground[i][j] != GROUND_MINESWEEPER) {
                    return false;
                }
                break;
            }
        }
    }
    gameEnded = true;
    return true;
}

Game::~Game() {
    for (int y = 0; y < y_size + 1; y++) {
        delete[] ground[y];
        delete[] view[y];
    }
    delete[] ground;
    delete[] view;
}