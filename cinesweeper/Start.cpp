#include "Start.h"
#include "Position.h"
#include <conio.h>

using namespace std;

Start::Start() {
    startEnded = false;
    selectedControl = CONTROL_WIDTH;
    numOfMinesweeper = 99;
    sizeOfGround = Position(99, 99, 30, 16);
}

void Start::start() {
    while (!startEnded) {
        keyDownEvent();
    }
}

void Start::keyDownEvent() {
    if (_kbhit()) {
        int key = _getch();

        switch (key) {
        case 0x46: case 0x66: // F, f
            
            break;
        case 0x20: // Space
            
            break;
        case 0x1B: // Esc
            
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


/*

¡á¡à¡à¡à¡á¡à¡á¡á¡á¡à¡á¡à¡à¡á¡à¡á¡á¡á¡á¡à
¡á¡á¡à¡á¡á¡à¡à¡á¡à¡à¡á¡á¡à¡á¡à¡á¡à¡à¡à¡à
¡á¡á¡à¡á¡á¡à¡à¡á¡à¡à¡á¡á¡à¡á¡à¡á¡á¡á¡à¡à
¡á¡à¡á¡à¡á¡à¡à¡á¡à¡à¡á¡à¡á¡á¡à¡á¡à¡à¡à¡à
¡á¡à¡à¡à¡á¡à¡á¡á¡á¡à¡á¡à¡à¡á¡à¡á¡á¡á¡á¡à
*/
