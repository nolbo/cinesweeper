#include "Start.h"
#include "Position.h"
#include <iostream>
#include <conio.h>
#include <cmath>

using namespace std;

Start::Start() {
    startEnded = false;
    selectedControl = CONTROL_WIDTH;
    numOfMinesweeper = 99;
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
            
            break;
        case 0x1B: // Esc
            startEnded = true;
            break;
        case 0x0D: // Enter

            break;
        case 224: // Arrow Key
            switch (_getch()) {
            case 72: // Up
                
                break;
            case 80: // Down
                
                break;
            case 75: // Left
                
                break;
            case 77: //Right
                
                break;
            }
        }
    }
}

void Start::printStartScreen() {
    float x_size = sizeOfMap.getX();
    float y_size = sizeOfMap.getY();
    float ratio_of_mnswpr = numOfMinesweeper / (x_size * y_size);
    int minimap_x_size = (x_size > y_size) ? 21 : floor(11 / (y_size / x_size) + 0.5);
    int minimap_y_size = (y_size > x_size) ? 21 : floor(11 / (x_size / y_size) + 0.5);
    int num_of_mnswpr_in_minimap = floor((minimap_x_size * minimap_y_size) * ratio_of_mnswpr + 0.5);
    string difficulty_color =
        (ratio_of_mnswpr <= DIFFICULTY_EASY) ?   "\033[90m" :
        (ratio_of_mnswpr <= DIFFICULTY_NORMAL) ? "\033[96m" :
        (ratio_of_mnswpr <= DIFFICULTY_HARD) ?   "\033[92m" :
        (ratio_of_mnswpr <= DIFFICULTY_CRAZY) ?  "\033[91m" : "\033[95m";

    string scripts[3] = {
        string("\033[1m\033[94mMap Width\033[0m  ").append(" \033[90m|\033[0m \033[96m" + to_string(sizeOfMap.getX()) + "\033[0m\n"),
        string("\033[1m\033[94mMap Height\033[0m ").append(" \033[90m|\033[0m \033[96m" + to_string(sizeOfMap.getY()) + "\033[0m\n"),
        string("\033[1m\033[94mMinesweeper\033[0m").append(" \033[90m|\033[0m \033[96m" + to_string(numOfMinesweeper) + "\033[0m ")
    };

    cout << fixed;
    cout.precision(1);
    for (int i = 0; i < 3; i++) {
        cout << ((i == selectedControl) ? "\033[7m" : "");
        cout << scripts[i];
        cout << ((i == selectedControl) ? "\033[0m" : "");
    }
    cout << difficulty_color + "(" << ratio_of_mnswpr * 100 << "%)\033[0m" << endl;
    cout << string(21, '=') << endl;
    for (int i = 0; i < minimap_y_size; i++) {
        for (int j = 0; j < minimap_x_size; j++) {
            cout << ((num_of_mnswpr_in_minimap-- > 0) ? difficulty_color + "¡á" + "\033[0m" : "¡á");
        }
        cout << endl;
    }
}

Start::~Start() {

}


/*

¡á¡à¡à¡à¡á¡à¡á¡á¡á¡à¡á¡à¡à¡á¡à¡á¡á¡á¡á¡à¡à¡á¡á¡á¡à¡á¡à¡à¡à¡á¡à¡á¡á¡á¡á¡à¡á¡á¡á¡á¡à¡á¡á¡á¡à¡à¡á¡á¡á¡á¡à¡á¡á¡á¡à¡à
¡á¡á¡à¡á¡á¡à¡à¡á¡à¡à¡á¡á¡à¡á¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡á¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡á¡à¡á¡à¡à¡à¡à¡á¡à¡à¡á¡à
¡á¡à¡á¡à¡á¡à¡à¡á¡à¡à¡á¡à¡á¡á¡à¡á¡á¡á¡à¡à¡à¡á¡á¡à¡à¡á¡à¡á¡à¡á¡à¡á¡á¡á¡à¡à¡á¡á¡á¡à¡à¡á¡á¡á¡à¡à¡á¡á¡á¡à¡à¡á¡á¡á¡à¡à
¡á¡à¡à¡à¡á¡à¡à¡á¡à¡à¡á¡à¡à¡á¡à¡á¡à¡à¡à¡à¡à¡à¡à¡á¡à¡á¡á¡à¡á¡á¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡à¡à¡á¡à¡à¡á¡à
¡á¡à¡à¡à¡á¡à¡á¡á¡á¡à¡á¡à¡à¡á¡à¡á¡á¡á¡á¡à¡á¡á¡á¡à¡à¡á¡à¡à¡à¡á¡à¡á¡á¡á¡á¡à¡á¡á¡á¡á¡à¡á¡à¡à¡à¡à¡á¡á¡á¡á¡à¡á¡à¡à¡á¡à
*/
