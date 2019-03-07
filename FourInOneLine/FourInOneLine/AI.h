#pragma once
#include <bitset>
#include "Board.h"
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

class AI
{
private:
	int maxIndex = 0;
	int minIndex = 0;
	clock_t start;
	clock_t end;
	clock_t timeinsecond;
	float total = 0;
public:

	AI();
	~AI();
	
	int minimaxTest(Board, int, int);
	int getMaxTest(Board board, Board, int depth, int alpha, int beta, int pos, int);
	int getMinTest(Board board, Board, int depth, int alpha, int beta, int pos, int);
	int getDef(Board, int);
	int getOff(Board, int);

	//int getValue(Board board, Board newboard, int pos);
	//int getDistance(Board);

	bool checkPlayerWin(Board);
	bool checkOppWin(Board);
	void print_arr(int arr[]);
};