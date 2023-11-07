#ifndef START_H
#define START_H

#include "Position.h"
#include <string>

class Start {
private:
	static const int CONTROL_WIDTH = 1;
	static const int CONTROL_HEIGHT = 2;
	static const int CONTROL_NUM_OF_MINESWEEPER = 3;
	static const int CONTROL_START_GAME = 4;

	static constexpr float DIFFICULTY_EASY   = 0.10f;
	static constexpr float DIFFICULTY_NORMAL = 0.15f;
	static constexpr float DIFFICULTY_HARD   = 0.20f;
	static constexpr float DIFFICULTY_CRAZY = 0.25f;

	bool activeStartScrnKey;
	bool startEnded;
	int numOfMinesweeper;
	std::string errMsg;
	Position selectedControl;
	Position sizeOfMap;

public:
	Start();
	void start();
	void keyDownEvent();
	void numberKeyInput(int num);
	void backspaceInput();
	void printStartScreen();
	void setNumOfMinesweeper(int num);
	void checkError();
	void startGame();
	float getMinesweeperRatio();
};

#endif