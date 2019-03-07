#include "pch.h"
#include "Board.h"
#include <iostream>
#include <bitset>
using namespace std;

Board::Board()
{

}

Board::~Board()
{

}

bool Board::playerInsert(unsigned move)
{
	if (canInsert(move))
	{
		gameBoard = gameBoard | (1LL << move);
		playerBoard = playerBoard | (1LL << move);
		return true;
	}
	return false;
}
bool Board::oppInsert(unsigned move)
{
	if (canInsert(move))
	{
		gameBoard = gameBoard | (1LL << move);
		oppBoard = oppBoard | (1LL << move);
		return true;
	}
	return false;
}

bitboard Board::getGameBoard() {
	return gameBoard;
}

bitboard Board::getPlayerBoard()
{
	return playerBoard;
}

bitboard Board::getOppBoard()
{
	return oppBoard;
}

// check
bool Board::canInsert(unsigned move)
{
	return !((gameBoard >> move) & 1);
}

bool Board::is_bit_set(bitboard m, unsigned pos)
{
	return m >> pos & 1;
}

//bool Board::checkWin()
//{
//	uint64_t m;
//	// horizontal
//	m = playerBoard >> 1 & playerBoard;
//	if ((m >> 2 & m) > 0) {
//		return true;
//	}
//
//	// vertical
//	m = playerBoard >> 8 & playerBoard;
//	if ((m >> 16 & m) > 0) {
//		return true;
//	}
//	return false;
//}
