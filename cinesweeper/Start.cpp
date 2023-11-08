#include "Start.h"
#include "Position.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <cmath>

using namespace std;

Start::Start() {
    activeStartScrnKey = true;
    startEnded = false;
    numOfMinesweeper = 99;
    seed = time(NULL);
    selectedControl = Position(1, 4, 1, CONTROL_WIDTH);
    sizeOfMap = Position(70, 70, 30, 16);
}

void Start::start() {
    printStartScreen();

    while (!startEnded) {
        keyDownEvent();
    }
}

void Start::keyDownEvent() {
    if (_kbhit()) {
        int key = _getch();

        switch (key) {
        case 0x20: // Space
            if (!activeStartScrnKey) {
                activeStartScrnKey = true;
                printStartScreen();
            }
            break;
        case 0x1B: // Esc
            startEnded = true;
            break;
        case 0x0D: // Enter
            startGame();
            break;
        case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57: // Number (0~9)
            numberKeyInput(key - 48);
            printStartScreen();
            break;
        case 8: // Backspace
            backspaceInput();
            printStartScreen();
            break;
        case 224: // Arrow Key
            if (activeStartScrnKey) {
                switch (_getch()) {
                case 72: // Up
                    selectedControl.moveY(-1);
                    printStartScreen();
                    break;
                case 80: // Down
                    selectedControl.moveY(1);
                    printStartScreen();
                    break;
                case 75: // Left
                    switch (selectedControl.getY())
                    {
                    case CONTROL_WIDTH:
                        sizeOfMap.moveX(-1);
                        checkError();
                        break;
                    case CONTROL_HEIGHT:
                        sizeOfMap.moveY(-1);
                        checkError();
                        break;
                    case CONTROL_NUM_OF_MINESWEEPER:
                        setNumOfMinesweeper(numOfMinesweeper - 1);
                        break;
                    default:
                        break;
                    }
                    printStartScreen();
                    break;
                case 77: //Right
                    switch (selectedControl.getY())
                    {
                    case CONTROL_WIDTH:
                        sizeOfMap.moveX(1);
                        checkError();
                        break;
                    case CONTROL_HEIGHT:
                        sizeOfMap.moveY(1);
                        checkError();
                        break;
                    case CONTROL_NUM_OF_MINESWEEPER:
                        setNumOfMinesweeper(numOfMinesweeper + 1);
                        break;
                    default:
                        break;
                    }
                    printStartScreen();
                    break;
                }
            }
        }
    }
}

void Start::numberKeyInput(int num) {
    int value;

    switch (selectedControl.getY())
    {
    case CONTROL_WIDTH:
        value = sizeOfMap.getX() * 10 + num;
        if (value <= 70) {
            sizeOfMap.setX(value);
        }
        break;
    case CONTROL_HEIGHT:
        value = sizeOfMap.getY() * 10 + num;
        if (value <= 70) {
            sizeOfMap.setY(value);
        }
        break;
    case CONTROL_NUM_OF_MINESWEEPER:
        setNumOfMinesweeper(numOfMinesweeper * 10 + num);
        break;
    case CONTROL_SEED:
        seed = seed * 10 + num;
        break;
    default:
        break;
    }
}

void Start::backspaceInput() {
    int value;

    switch (selectedControl.getY())
    {
    case CONTROL_WIDTH:
        value = sizeOfMap.getX() / 10;
        if (value > -1) {
            sizeOfMap.setX(value);
        }
        break;
    case CONTROL_HEIGHT:
        value = sizeOfMap.getY() / 10;
        if (value > -1) {
            sizeOfMap.setY(value);
        }
        break;
    case CONTROL_NUM_OF_MINESWEEPER:
        setNumOfMinesweeper(numOfMinesweeper / 10);
        break;
    case CONTROL_SEED:
        seed = seed / 10;
        break;
    default:
        break;
    }
}

void Start::printStartScreen() {
    system("cls");

    checkError();

    float x_size = sizeOfMap.getX();
    float y_size = sizeOfMap.getY();
    float ratio_of_mnswpr = getMinesweeperRatio();
    int minimap_x_size = 11;
    int minimap_y_size = ceil(minimap_x_size / (x_size / y_size));
    int num_of_mnswpr_in_minimap = ceil((minimap_x_size * minimap_y_size) * ratio_of_mnswpr);
    string difficulty_color = 
        (ratio_of_mnswpr < DIFFICULTY_EASY) ?   "\033[90m" :
        (ratio_of_mnswpr < DIFFICULTY_NORMAL) ? "\033[96m" :
        (ratio_of_mnswpr < DIFFICULTY_HARD) ?   "\033[92m" :
        (ratio_of_mnswpr < DIFFICULTY_CRAZY) ?  "\033[91m" : "\033[95m";
    string difficulty_text =
        (ratio_of_mnswpr < DIFFICULTY_EASY) ? "Too Easy" :
        (ratio_of_mnswpr < DIFFICULTY_NORMAL) ? "Easy" :
        (ratio_of_mnswpr < DIFFICULTY_HARD) ? "Normal" :
        (ratio_of_mnswpr < DIFFICULTY_CRAZY) ? "Hard" : "Crazy";

    string scripts[4] = {
        "\033[1m\033[94mMap Width\033[0m   \033[90m|\033[0m ",
        "\033[1m\033[94mMap Height\033[0m  \033[90m|\033[0m ",
        "\033[1m\033[94mMinesweeper\033[0m \033[90m|\033[0m ",
        "\033[1m\033[94mSeed\033[0m        \033[90m|\033[0m "
    };

    string values[4] = {
        string("\033[96m").append(to_string(sizeOfMap.getX()) + "\033[0m "),
        string("\033[96m").append(to_string(sizeOfMap.getY()) + "\033[0m "),
        string("\033[96m").append(to_string(numOfMinesweeper) + "\033[0m "),
        string("\033[96m").append(to_string(seed) + "\033[0m ")
    };

    std::cout << fixed;
    std::cout.precision(1);
    
    bool breakpoint = false;

    for (int i = 0; i < ((minimap_y_size < 8) ? 8 : minimap_y_size) && !breakpoint; i++) {
        if (i > 15 - 1 && i < minimap_y_size) {
            string plus = "+" + to_string(minimap_y_size - i);
            std::cout << plus << string(22 - plus.length(), ' ');
            breakpoint = true;
        }
        for (int j = 0; j < minimap_x_size && i < minimap_y_size && !breakpoint; j++) {
            std::cout << ((num_of_mnswpr_in_minimap-- > 0) ? difficulty_color + "¡á" + "\033[0m " : "¡á ");
        }
        if (i >= minimap_y_size && i < 8) {
            std::cout << string(22, ' ');
        }
        std::cout << " ¦¢ ";
        if (i < 4) {
            std::cout << scripts[i];
            std::cout << ((i + 1 == selectedControl.getY() && i + 1 < 4) ? "¢¸ " : "");
            std::cout << ((i + 1 == selectedControl.getY()) ? "\033[7m" : "");
            std::cout << values[i];
            std::cout << ((i + 1 == selectedControl.getY()) ? "\033[0m" : "");
            std::cout << ((i + 1 == selectedControl.getY() && i + 1 < 4) ? "¢º " : "");
        }
        if (i == 2) {
            std::cout << difficulty_color + "(" << ratio_of_mnswpr * 100 << "%)\033[0m";
        }
        if (i == 5) {
            std::cout << "Difficulty: " << difficulty_color + difficulty_text + "\033[0m";
        }
        if (i == 7) {
            std::cout << ((errMsg == "") ? "Press \033[7m\033[33m[Enter]\033[0m to Start" : "\033[7m\033[31m[!]\033[0m \033[90m" + errMsg + "\033[0m");
        }
        std::cout << endl;
    }
}

void Start::setNumOfMinesweeper(int num) {
    if (num > -1 && num < sizeOfMap.getX() * sizeOfMap.getY()) numOfMinesweeper = num;
}

void Start::checkError() {
    if (sizeOfMap.getX() < 10) {
        errMsg = "Width of map is too small.";
    }
    else if (sizeOfMap.getY() < 10) {
        errMsg = "Height of map is too small.";
    }
    else if (getMinesweeperRatio() < DIFFICULTY_EASY) {
        errMsg = "It is too Easy.";
    }
    else if (getMinesweeperRatio() > 0.5) {
        errMsg = "It is too Hard.";
    }
    else {
        errMsg = "";
    }
}

float Start::getMinesweeperRatio() {
    return numOfMinesweeper / (static_cast<float>(sizeOfMap.getX()) * sizeOfMap.getY());
}

void Start::startGame() {
    if (errMsg == "") {
        activeStartScrnKey = false;
        Game game = Game(sizeOfMap.getX(), sizeOfMap.getY(), numOfMinesweeper, seed);
        game.startGame();
    }
}



/*

¡á¡à¡à¡à¡á¡à¡á¡á¡á¡à¡á¡à¡à¡á¡à¡á¡á¡á¡á¡à¡à¡á¡á¡á¡à¡á¡à¡à¡à¡á¡à¡á¡á¡á¡á¡à¡á¡á¡á¡á¡à¡á¡á¡á¡à¡à¡á¡á¡á¡á¡à¡á¡á¡á¡à¡à
¡á¡á¡à¡á¡á¡à¡à¡á¡à¡à¡á¡á¡à¡á¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡á¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡á¡à¡á¡à¡à¡à¡à¡á¡à¡à¡á¡à
¡á¡à¡á¡à¡á¡à¡à¡á¡à¡à¡á¡à¡á¡á¡à¡á¡á¡á¡à¡à¡à¡á¡á¡à¡à¡á¡à¡á¡à¡á¡à¡á¡á¡á¡à¡à¡á¡á¡á¡à¡à¡á¡á¡á¡à¡à¡á¡á¡á¡à¡à¡á¡á¡á¡à¡à
¡á¡à¡à¡à¡á¡à¡à¡á¡à¡à¡á¡à¡à¡á¡à¡á¡à¡à¡à¡à¡à¡à¡à¡á¡à¡á¡á¡à¡á¡á¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡á¡à
¡á¡à¡à¡à¡á¡à¡á¡á¡á¡à¡á¡à¡à¡á¡à¡á¡á¡á¡á¡à¡á¡á¡á¡à¡à¡á¡à¡à¡à¡á¡à¡á¡á¡á¡á¡à¡á¡á¡á¡á¡à¡á¡à¡à¡à¡à¡á¡á¡á¡á¡à¡á¡à¡à¡á¡à
*/
