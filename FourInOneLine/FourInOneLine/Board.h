#pragma once
#include <bitset>

typedef uint64_t bitboard;

class Board
{

private:
	bitboard gameBoard = 0;
	bitboard playerBoard = 0;
	bitboard oppBoard = 0;

	char player_mark = 'X';
	char opp_mark = 'O';

public:
	Board();
	~Board();
	bool playerInsert(unsigned);
	bool oppInsert(unsigned);
	bitboard getGameBoard();
	bitboard getPlayerBoard();
	bitboard getOppBoard();
	bool canInsert(unsigned);
	//void swapPlayer_Opp();
	//bool canPlayerInsert(unsigned);
	//bool canOppInsert(unsigned);
	//bool checkWin();
	
	bool is_bit_set(bitboard, unsigned);
};

