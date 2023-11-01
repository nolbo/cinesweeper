#ifndef START_H
#define START_H

#include "Position.h"
#include <string>

class Start {
private:
	static const int CONTROL_WIDTH = 0;
	static const int CONTROL_HEIGHT = 1;
	static const int CONTROL_NUM_OF_MINESWEEPER = 2;
	static const int CONTROL_START_GAME = 3;

	static constexpr float DIFFICULTY_EASY   = 0.10f;
	static constexpr float DIFFICULTY_NORMAL = 0.15f;
	static constexpr float DIFFICULTY_HARD   = 0.20f;
	static constexpr float DIFFICULTY_CRAZY = 0.25f;

	bool startEnded;
	int selectedControl;
	int numOfMinesweeper;
	Position sizeOfMap;

public:
	Start();
	void start();
	void keyDownEvent();
	void printStartScreen();
	~Start();
};

#endif