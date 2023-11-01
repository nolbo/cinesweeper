#ifndef START_H
#define START_H

#include "Position.h"

class Start {
private:
	static const int CONTROL_WIDTH = 0;
	static const int CONTROL_HEIGHT = 1;
	static const int CONTROL_NUM_OF_MINESWEEPER = 2;
	static const int CONTROL_START_GAME = 3;

	bool startEnded;
	int selectedControl;
	int numOfMinesweeper;
	Position sizeOfGround;

public:
	Start();
	void start();
	void keyDownEvent();
	~Start();
};

#endif