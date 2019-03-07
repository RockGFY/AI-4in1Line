#include "pch.h"
#include "AI.h"

AI::AI()
{

}


AI::~AI()
{

}

// test
int AI::minimaxTest(Board board, int first, int time)
{
	Board newTestBoard(board); // 

	int depth = 5;

	if (first == 0) {
		start = clock();
		int v = getMinTest(board, newTestBoard, depth, -1000000, 1000000, 0, time);
		return minIndex;
	}
	else {
		start = clock();
		int v = getMaxTest(board, newTestBoard, depth, -1000000, 1000000, 0, time);
		return maxIndex;
	}
	//t = clock();
	//int v = getMinTest(board, newTestBoard, depth, -1000000, 1000000, 0);
	//t = clock() - t;
	//float timeinsecond = (float)t / CLOCKS_PER_SEC;
	//cout << "Time used: " << timeinsecond << endl;
	//return minIndex;
}

int AI::getMaxTest(Board board, Board newBoard, int depth, int alpha, int beta, int pos, int time)
{
	//if (depth == 0) {
	//	int h = getOff(board, pos) + getDef(newBoard, pos);
	//	return depth % 2 == 0 ? h : -h;
	//}
	if (depth == 0 || total >= time) {
		return getOff(board, pos) + getDef(newBoard, pos);
	}

	int v = -1000000;
	int h_arr[64];

	for (int i = 0; i < 64; i++) {
		if (board.canInsert(i))
		{
			// create new state
			Board newBoard(board);
			newBoard.playerInsert(i);

			Board newTestBoard(board);
			newTestBoard.oppInsert(i);

			int h = getMinTest(newBoard, newTestBoard, depth - 1, alpha, beta, i, time);

			h_arr[i] = h;

			if (v < h) {
				v = h;
				maxIndex = i;
			}
			alpha = max(alpha, v);
			if (alpha >= beta)
				break;
		}
		end = clock();
		timeinsecond += (end - start);
		total = (float)timeinsecond / CLOCKS_PER_SEC;
		if (total > time) {
			break;
		}
		else {
			start = clock();
		}		
	}
	//print_arr(h_arr);
	return v;
}
//todododododo timing
int AI::getMinTest(Board board, Board newBoard, int depth, int alpha, int beta, int pos, int time)
{
	//if (depth == 0 || t >= 25) {
	//	int h = getOff(newBoard, pos) + getDef(board, pos);
	//	return depth % 2 == 0 ? h : -h;
	//}
	if (depth == 0 || total >= time) {
		return getOff(newBoard, pos) + getDef(board, pos);
	}
	int v = 1000000;

	int h_arr[64];

	for (int i = 0; i < 64; i++) {
		if (board.canInsert(i))
		{
			// create new state
			Board newBoard(board);
			newBoard.oppInsert(i);

			Board newTestBoard(board);
			newTestBoard.playerInsert(i);
			//if (i == 10)
			//	cout << endl;
			int h = -getMaxTest(newBoard, newTestBoard, depth - 1, alpha, beta, i, time);
			h_arr[i] = h;

			if (v > h) {
				v = h;
				minIndex = i;
			}
			beta = min(beta, v);
			if (alpha >= beta)
				break;
		}
		end = clock();
		timeinsecond += (end - start);
		total = (float)timeinsecond / CLOCKS_PER_SEC;
		if (total > time) {
			break;
		}
		else {
			start = clock();
		}
	}
	//print_arr(h_arr);
	return v;
}

//int AI::getValue(Board board, Board newBoard, int pos) {
//	if (checkOppWin(board)) {
//		return 5000;
//	}
//	if (checkPlayerWin(newBoard)) {
//		return -5000;
//	}
//
//	int dead_threeOpp = 0;
//	int oneSide_threeOpp = 0;
//	int open_threeOpp = 0;
//
//	int dead_twoOpp = 0;
//	int oneSide_twoOpp = 0;
//	int open_twoOpp = 0;
//
//	// check offsence
//	// 255 = 11111111
//	int leftReminder = pos % 8;
//	bitboard tempOpp = (board.getOppBoard() >> (pos - leftReminder)) & 255;
//	bitboard tempGame = board.getGameBoard() >> (pos - leftReminder);
//
//	int dead_three = 0;
//	int oneSide_three = 0;
//	int open_three = 0;
//
//	int dead_two = 0;
//	int oneSide_two = 0;
//	int open_two = 0;
//	bitboard tempPlayer = (newBoard.getPlayerBoard() >> (pos - leftReminder)) & 255;
//
//	// 7 = |ooo-,  15 = |ooox
//	if (leftReminder == 0) {
//		if ((tempOpp & 15) == 7) {
//			if ((tempGame & 15) == 7) {
//				oneSide_threeOpp++;
//			}
//			else if ((tempGame & 15) == 15) {
//				dead_threeOpp++;
//			}
//		}
//		//TODO |oo-o----
//		// 3 = oo-, 7 = oox
//		else if ((tempOpp & 7) == 3) {
//			if ((tempGame & 7) == 3) {
//				oneSide_twoOpp++;
//			}
//			else if ((tempGame & 7) == 7) {
//				dead_twoOpp++;
//			}
//		}
//
//		if ((tempPlayer & 15) == 7) {
//			if ((tempGame & 15) == 7) {
//				oneSide_three++;
//			}
//			else if ((tempGame & 15) == 15) {
//				dead_three++;
//			}
//		}
//		//TODO |oo-o----
//		// 3 = xx-, 7 = xxo
//		else if ((tempPlayer & 7) == 3) {
//			if ((tempGame & 7) == 3) {
//				oneSide_two++;
//			}
//			else if ((tempGame & 7) == 7) {
//				dead_two++;
//			}
//		}
//	}
//	// -----ooo| = 224, ----xooo| = 240, 
//	else if (leftReminder == 7) {
//		if ((tempOpp & 240) == 224) {
//			if ((tempGame & 240) == 224) {
//				oneSide_threeOpp++;
//			}
//			else if ((tempGame & 240) == 240) {
//				dead_threeOpp++;
//			}
//		}
//		//TODO ----o-oo|
//
//		// ------oo| = 192, ----xoo| = 224, 
//		else if ((tempOpp & 224) == 192) {
//			if ((tempGame & 224) == 192) {
//				oneSide_twoOpp++;
//			}
//			else if ((tempGame & 224) == 224) {
//				dead_twoOpp++;
//			}
//		}
//
//		if ((tempPlayer & 240) == 224) {
//			if ((tempGame & 240) == 224) {
//				oneSide_three++;
//			}
//			else if ((tempGame & 240) == 240) {
//				dead_three++;
//			}
//		}
//		//TODO ----o-oo|
//
//		// ------oo| = 192, ----xoo| = 224, 
//		else if ((tempPlayer & 224) == 192) {
//			if ((tempGame & 224) == 192) {
//				oneSide_two++;
//			}
//			else if ((tempGame & 224) == 224) {
//				dead_two++;
//			}
//		}
//	}
//	else {
//		for (int i = 0; i < leftReminder; i++) {
//			// 14 = -ooo-, 15 = -ooox, 30 = xooo-, 31 = xooox
//			if (((tempOpp >> i) & 31) == 14) {
//				if ((tempGame >> i & 31) == 14) {
//					open_threeOpp++;
//				}
//				else if ((tempGame >> i & 31) == 15 || (tempGame >> i & 31) == 30) {
//					oneSide_threeOpp++;
//				}
//				else if ((tempGame >> i & 31) == 31) {
//					dead_threeOpp++;
//				}
//			}
//			//TODO oo-o or o-oo
//
//			// chech -oo-
//			// 6 = -oo-, gameBoard: 7 = -xxo, 14 = oxx-, 15 = oxxo
//			else if (((tempOpp >> i) & 15) == 6) {
//				if (((tempGame >> i) & 15) == 6) {
//					open_twoOpp++;
//				}
//				else if ((tempGame >> i & 15) == 7 || (tempGame >> i & 15) == 14) {
//					oneSide_twoOpp++;
//				}
//				else if ((tempGame >> i & 15) == 15) {
//					dead_twoOpp++;
//				}
//			}
//		}
//
//		for (int i = 0; i < leftReminder; i++) {
//			// 14 = -ooo-, 15 = -ooox, 30 = xooo-, 31 = xooox
//			if (((tempPlayer >> i) & 31) == 14) {
//				if ((tempGame >> i & 31) == 14) {
//					open_three++;
//				}
//				else if ((tempGame >> i & 31) == 15 || (tempGame >> i & 31) == 30) {
//					oneSide_three++;
//				}
//				else if ((tempGame >> i & 31) == 31) {
//					dead_three++;
//				}
//			}
//			//TODO oo-o or o-oo
//
//			// chech -oo-
//			// 6 = -oo-, gameBoard: 7 = -xxo, 14 = oxx-, 15 = oxxo
//			else if (((tempPlayer >> i) & 15) == 6) {
//				if (((tempGame >> i) & 15) == 6) {
//					open_two++;
//				}
//				else if ((tempGame >> i & 15) == 7 || (tempGame >> i & 15) == 14) {
//					oneSide_two++;
//				}
//				else if ((tempGame >> i & 15) == 15) {
//					dead_two++;
//				}
//			}
//		}
//
//	}
//
//	bitboard tempOppVer = board.getOppBoard() >> leftReminder;
//	bitboard tempGameVer = board.getGameBoard() >> leftReminder;
//	bitboard tempPlayerVer = board.getPlayerBoard() >> leftReminder;
//
//	int topReminder = pos / 8;
//	// |ooo----- = 65793, |ooox---- = 16843009
//	if (topReminder == 0) {
//		if ((tempOppVer & 16843009) == 65793) {
//			if ((tempGameVer & 16843009) == 65793) {
//				oneSide_threeOpp++;
//			}
//			else if ((tempGameVer & 16843009) == 16843009) {
//				dead_threeOpp++;
//			}
//		}
//		//todo |oo-o---- or |o-oo----
//
//		// |oo------ = 257, |oox----- = 65793
//		else if ((tempOppVer & 65793) == 257) {
//			if ((tempGameVer & 65793) == 257) {
//				oneSide_twoOpp++;
//			}
//			else if ((tempGameVer & 65793) == 65793) {
//				dead_twoOpp++;
//			}
//		}
//
//		if ((tempPlayerVer & 16843009) == 65793) {
//			if ((tempGameVer & 16843009) == 65793) {
//				oneSide_three++;
//			}
//			else if ((tempGameVer & 16843009) == 16843009) {
//				dead_three++;
//			}
//		}
//		//todo |oo-o---- or |o-oo----
//
//		// |oo------ = 257, |oox----- = 65793
//		else if ((tempPlayerVer & 65793) == 257) {
//			if ((tempGameVer & 65793) == 257) {
//				oneSide_two++;
//			}
//			else if ((tempGameVer & 65793) == 65793) {
//				dead_two++;
//			}
//		}
//	}
//	else if (topReminder == 7) {
//		// -----ooo| = 4295033088, ----xooo| = 4295033089, 
//		if ((tempOppVer >> 32 & 4295033089) == 4295033088) {
//			if ((tempGameVer >> 32 & 4295033089) == 4295033088) {
//				oneSide_threeOpp++;
//			}
//			else if ((tempGameVer >> 32 & 4295033089) == 4295033089) {
//				dead_threeOpp++;
//			}
//		}
//		//todo ----o-oo| , ----oo-o|
//
//		// ------oo| = 4295032832, -----xoo| = 4295033088
//		else if ((tempOppVer >> 32 & 4295033089) == 4295032832) {
//			if ((tempGameVer >> 32 & 4295033089) == 4295032832) {
//				oneSide_twoOpp++;
//			}
//			else if ((tempGameVer >> 32 & 4295033089) == 4295033088) {
//				dead_twoOpp++;
//			}
//		}
//		// -----ooo| = 4295033088, ----xooo| = 4295033089, 
//		if ((tempPlayerVer >> 32 & 4295033089) == 4295033088) {
//			if ((tempGameVer >> 32 & 4295033089) == 4295033088) {
//				oneSide_three++;
//			}
//			else if ((tempGameVer >> 32 & 4295033089) == 4295033089) {
//				dead_three++;
//			}
//		}
//		//todo ----o-oo| , ----oo-o|
//
//		// ------oo| = 4295032832, -----xoo| = 4295033088
//		else if ((tempPlayerVer >> 32 & 4295033089) == 4295032832) {
//			if ((tempGameVer >> 32 & 4295033089) == 4295032832) {
//				oneSide_two++;
//			}
//			else if ((tempGameVer >> 32 & 4295033089) == 4295033088) {
//				dead_two++;
//			}
//		}
//	}
//	else {
//		//check -
//		//		x
//		//		x
//		//		x
//		//		-
//		for (int i = 0; i < topReminder; i++) {
//			//  -xxx- = 16843008,  oxxx- = 4311810304, -xxxo = 16843009, oxxxo = 4311810305
//			if (((tempOppVer >> i * 8) & 4311810305) == 16843008) {
//				if (((tempGameVer >> i * 8) & 4311810305) == 16843008) {
//					open_threeOpp++;
//				}
//				else if (((tempGameVer >> i * 8) & 4311810305) == 4311810304 || ((tempGameVer >> i * 8) & 4311810305) == 16843009) {
//					oneSide_threeOpp++;
//				}
//				else if (((tempGameVer >> i * 8) & 4311810305) == 4311810305) {
//					dead_threeOpp++;
//				}
//			}
//			//check -
//			//		x
//			//		x
//			//		-
//			// playerBoard: 65792 = -xx-, gameBoard: 65793 = -xxo, 16843008 = oxx-, 16843009 = oxxo
//			else if (((tempOppVer >> i * 8) & 16843009) == 65792) {
//				if (((tempGameVer >> i * 8) & 16843009) == 65792) {
//					open_twoOpp++;
//				}
//				else if (((tempGameVer >> i * 8) & 16843009) == 65793 || ((tempGameVer >> i * 8) & 16843009) == 16843008) {
//					oneSide_twoOpp++;
//				}
//				else if (((tempGameVer >> i * 8) & 16843009) == 16843009) {
//					dead_twoOpp++;
//				}
//			}
//		}
//
//		for (int i = 0; i < topReminder; i++) {
//			//  -xxx- = 16843008,  oxxx- = 4311810304, -xxxo = 16843009, oxxxo = 4311810305
//			if (((tempPlayerVer >> i * 8) & 4311810305) == 16843008) {
//				if (((tempGameVer >> i * 8) & 4311810305) == 16843008) {
//					open_three++;
//				}
//				else if (((tempGameVer >> i * 8) & 4311810305) == 4311810304 || ((tempGameVer >> i * 8) & 4311810305) == 16843009) {
//					oneSide_three++;
//				}
//				else if (((tempGameVer >> i * 8) & 4311810305) == 4311810305) {
//					dead_three++;
//				}
//			}
//			//check -
//			//		x
//			//		x
//			//		-
//			// playerBoard: 65792 = -xx-, gameBoard: 65793 = -xxo, 16843008 = oxx-, 16843009 = oxxo
//			else if (((tempPlayerVer >> i * 8) & 16843009) == 65792) {
//				if (((tempGameVer >> i * 8) & 16843009) == 65792) {
//					open_two++;
//				}
//				else if (((tempGameVer >> i * 8) & 16843009) == 65793 || ((tempGameVer >> i * 8) & 16843009) == 16843008) {
//					oneSide_two++;
//				}
//				else if (((tempGameVer >> i * 8) & 16843009) == 16843009) {
//					dead_two++;
//				}
//			}
//		}
//	}
//
//
//	return 0;
//}


int AI::getOff(Board board, int pos)
{
	if (checkOppWin(board)) {
		return 50000;
	}

	int dead_three = 0;
	int oneSide_three = 0;
	int open_three = 0;

	int dead_two = 0;
	int oneSide_two = 0;
	int open_two = 0;

	// check offsence
	// 255 = 11111111
	int leftReminder = pos % 8;
	bitboard tempOpp = (board.getOppBoard() >> (pos - leftReminder)) & 255;
	bitboard tempGame = board.getGameBoard() >> (pos - leftReminder);

	int topReminder = pos / 8;
	bitboard tempOppVer = board.getOppBoard() >> leftReminder;
	bitboard tempGameVer = board.getGameBoard() >> leftReminder;

	// horizontal 
	if (leftReminder == 0) {
		//if ((tempOpp & 15) == 15) {
		//	return 50000;
		//}
		// 7 = |ooo-,  15 = |ooox
		if ((tempOpp & 15) == 7) {
			if ((tempGame & 15) == 7) {
				oneSide_three++;
			}
			else if ((tempGame & 15) == 15) {
				dead_three++;
			}
		}
		//|-ooo = 14
		else if ((tempOpp & 15) == 14) {
			if ((tempGame & 15) == 14) {
				open_three++;
			}
			else if ((tempGame & 15) == 15) {
				oneSide_three++;
			}
		}
		//|-oo- = 6, |-oox
		else if ((tempOpp & 15) == 6) {
			if ((tempGame & 15) == 6) {
				open_two++;
			}
			else if ((tempGame & 15) == 14) {
				dead_three++;
			}
			else if ((tempGame & 15) == 7) {
				oneSide_two++;
			}
		}
		//TODO |oo-o---- = 11, |ooxo----- = 15
		else if ((tempOpp & 15) == 11) {
			if ((tempGame & 15) == 11) {
				oneSide_three++;
			}
			else if ((tempGame & 15) == 15) {
				dead_two++;
			}
		}

		//|o-oo----- = 13, |oxoo----- = 15
		else if ((tempOpp & 15) == 13) {
			if ((tempGame & 15) == 13) {
				oneSide_three++;
			}
			else if ((tempGame & 15) == 15) {
				oneSide_two++;
			}
		}
		// 3 = |oo-, 7 = |oox, 
		else if ((tempOpp & 7) == 3) {
			if ((tempGame & 7) == 3) {
				oneSide_two++;
			}
			else if ((tempGame & 7) == 7) {
				dead_two++;
			}
		}
		//|-oo = 6
		else if ((tempOpp & 7) == 6) {
			if ((tempGame & 7) == 6) {
				open_two++;
			}
			else if ((tempGame & 7) == 7) {
				oneSide_two++;
			}
		}
	}
	else if (leftReminder == 7) {
		//if ((tempOpp & 240) == 240) {
		//	return 50000;
		//}

		// -----ooo| = 224, ----xooo| = 240, 
		if ((tempOpp & 240) == 224) {
			if ((tempGame & 240) == 224) {
				oneSide_three++;
			}
			else if ((tempGame & 240) == 240) {
				dead_three++;
			}
		}
		// -ooo-| = 112,   ---xooo-| = 120,  ----ooox| = 240, 
		else if ((tempOpp & 240) == 112) {
			if ((tempGame & 240) == 112) {
				open_three++;
			}
			else if ((tempGame & 240) == 120 || (tempGame & 240) == 240) {
				oneSide_three++;
			}
		}
		//TODO ----o-oo| = 208,   ----oxoo| = 240
		else if ((tempOpp & 240) == 208) {
			if ((tempGame & 240) == 208) {
				oneSide_three++;
			}
			else if ((tempGame & 240) == 240) {
				dead_two++;
			}
		}
		// ----oo-o | = 176, ----ooxo| = 240
		else if ((tempOpp & 240) == 176) {
			if ((tempGame & 240) == 176) {
				oneSide_three++;
			}
			else if ((tempGame & 240) == 240) {
				oneSide_two++;
			}
		}

		// -----oo-| = 96, ----xoo-| = 112 -----oox| = 224
		else if ((tempOpp & 240) == 96) {
			if ((tempGame & 240) == 96) {
				open_two++;
			}
			else if ((tempGame & 240) == 112) {
				dead_three++;
			}
			else if ((tempGame & 240) == 224) {
				oneSide_two++;
			}
		}
		// ------oo| = 192, -----o-o| = 160, ----xoo| = 224, 
		else if ((tempOpp & 224) == 192 || (tempOpp & 224) == 160) {
			if ((tempGame & 224) == 192) {
				oneSide_two++;
			}
			else if ((tempGame & 224) == 160) {
				oneSide_two++;
			}
			else if ((tempGame & 224) == 224) {
				dead_two++;
			}
		}
		// ----oo--| = 48, ----oox-| = 112, ---xoox-| = 120, 
		else if ((tempOpp & 120) == 48) {
			if ((tempGame & 120) == 48) {
				open_two++;
			}
			else if ((tempGame & 120) == 112) {
				oneSide_two++;
			}
			else if ((tempGame & 120) == 120) {
				dead_two++;
			}
		}

	}
	else {
		for (int i = 0; i < leftReminder; i++) {
			// 30 = -oooo,  15 = oooo-,  
			//if ((tempOpp >> i & 31) == 30 || (tempOpp >> i & 31) == 15) {
			//	return 50000;
			//}
			// 14 = -ooo-,  15 = -ooox,  30 = xooo-, 31 = xooox
			if ((tempOpp >> i & 31) == 14) {
				if ((tempGame >> i & 31) == 14) {
					open_three++;
				}
				else if ((tempGame >> i & 31) == 15 || (tempGame >> i & 31) == 30) {
					oneSide_three++;
				}
				else if ((tempGame >> i & 31) == 31) {
					dead_three++;
				}
			}
			//TODO -oo1o = 22,  -ooxo = 30, 
			else if (((tempOpp >> i) & 31) == 22) {
				if ((tempGame >> i & 31) == 22) {
					oneSide_three++;
				}
				else if ((tempGame >> i & 31) == 30) {
					oneSide_two++;
				}
			}
			//// --oo- = 12; -xoo- = 14 £¬ --oox = 28  ,  -xoox = 30
			//else if (((tempOpp >> i) & 30) == 12) {
			//	if ((tempGame >> i & 30) == 12) {
			//		open_two++;
			//	}
			//	else if ((tempGame >> i & 30) == 14 || (tempGame >> i & 30) == 28) {
			//		oneSide_two++;
			//	}
			//	else if ((tempGame >> i & 30) == 30) {
			//		dead_two++;
			//	}
			//}

			//TODO ooxox = 31, oo1o- = 11, ooxo- = 15
			//else if (((tempOpp >> i) & 31) == 11) {
			//	if ((tempGame >> i & 31) == 11) {
			//		oneSide_three++;
			//	}
			//	else if ((tempGame >> i & 31) == 15) {
			//		dead_two++;
			//	}
			//}

			//TODO -o-o = 10, -o1o = 14, ooxo = 15
			else if (((tempOpp >> i) & 15) == 10) {
				if ((tempGame >> i & 15) == 10) {
					oneSide_two++;
				}
			}

			// chech -oo-
			// 6 = -oo-, gameBoard: 7 = -xxo, 14 = oxx-, 15 = oxxo
			else if (((tempOpp >> i) & 15) == 6) {
				if (((tempGame >> i) & 15) == 6) {
					open_two++;
				}
				else if ((tempGame >> i & 15) == 7 || (tempGame >> i & 15) == 14) {
					oneSide_two++;
				}
				else if ((tempGame >> i & 15) == 15) {
					dead_two++;
				}
			}
			// o-o = 5, oxo = 7
			else if ((tempOpp >> i & 7) == 5) {
				if (((tempGame >> i) & 7) == 5) {
					oneSide_two++;
				}
			}
		}

	}

	// vertical
	// |ooo----- = 65793, |ooox---- = 16843009
	if (topReminder == 0) {
		if ((tempOppVer & 16843009) == 65793) {
			if ((tempGameVer & 16843009) == 65793) {
				oneSide_three++;
			}
			else if ((tempGameVer & 16843009) == 4295033089) {
				dead_three++;
			}
		}
		//todo |oo-o---- = 16777473,  |ooxo----16843009 
		else if ((tempOppVer & 16843009) == 16777473) {
			if ((tempGameVer & 16843009) == 16777473) {
				oneSide_three++;
			}
			else if ((tempGameVer & 16843009) == 16843009) {
				dead_two++;
			}
		}
		// |-oo----- = 65792 , |xoo----- = 65793, |-oox---- = 16843008,
		else if ((tempOppVer & 16843009) == 65792) {
			if ((tempGameVer & 16843009) == 65792) {
				open_two++;
			}
			else if ((tempGameVer & 16843009) == 65793) {
				oneSide_two++;
			}
			else if ((tempGameVer & 16843009) == 16843008) {
				dead_three++;
			}
		}
		// |o-oo---- = 16842753
		else if ((tempOppVer & 16843009) == 16842753) {
			if ((tempGameVer & 16843009) == 16842753) {
				oneSide_three++;
			}
			else if ((tempGameVer & 16843009) == 16843009) {
				oneSide_two++;
			}
		}
		// |oo------ = 257, |oox----- = 65793
		else if ((tempOppVer & 65793) == 257) {
			if ((tempGameVer & 65793) == 257) {
				oneSide_two++;
			}
			else if ((tempGameVer & 65793) == 65793) {
				dead_two++;
			}
		}
		//|-oo---- = 65792, |-oox--- = 16843008
		else if ((tempOppVer & 16843008) == 65792) {
			if ((tempGameVer & 16843008) == 65792) {
				open_two++;
			}
			else if ((tempGameVer & 16843008) == 16843008) {
				dead_three++;
			}
		}
	}
	else if (topReminder == 7) {
		// -ooo| = 16843008, xooo| = 16843009, 
		if ((tempOppVer >> 32 & 16843009) == 16843008) {
			if ((tempGameVer >> 32 & 16843009) == 16843008) {
				oneSide_three++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 16843009) {
				dead_three++;
			}
		}
		//todo o-oo| = 16842753 , oxoo| = 16843009,   
		else if ((tempOppVer >> 32 & 16843009) == 16842753) {
			if ((tempGameVer >> 32 & 16843009) == 16842753) {
				oneSide_three++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 16843009) {
				dead_two++;
			}
		}
		// oo-o| = 16777473, 
		else if ((tempOppVer >> 32 & 16843009) == 16777473) {
			if ((tempGameVer >> 32 & 16843009) == 16777473) {
				oneSide_three++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 16843009) {
				oneSide_two++;
			}
		}
		//totototodododo
		// -oo-| = 65792, xoo-| = 65793,  -oox| = 65793, 
		else if ((tempOppVer >> 32 & 16843009) == 65792) {
			if ((tempGameVer >> 32 & 16843009) == 65792) {
				open_two++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 65793 || (tempGameVer >> 32 & 16843009) == 16843008) {
				dead_three++;
			}
		}
		// --oo| = 16842752, -xoo| = 16843008
		else if ((tempOppVer >> 32 & 16843009) == 16842752) {
			if ((tempGameVer >> 32 & 16843009) == 16842752) {
				oneSide_two++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 16843008) {
				dead_two++;
			}
		}
	}
	else {
		//check -
		//		x
		//		x
		//		x
		//		-
		for (int i = 0; i < topReminder; i++) {
			//  -xxx- = 16843008,  oxxx- = 4311810304, -xxxo = 16843009, oxxxo = 4311810305
			if (((tempOppVer >> i * 8) & 4311810305) == 16843008) {
				if (((tempGameVer >> i * 8) & 4311810305) == 16843008) {
					open_three++;
				}
				else if (((tempGameVer >> i * 8) & 4311810305) == 4311810304 || ((tempGameVer >> i * 8) & 4311810305) == 16843009) {
					oneSide_three++;
				}
				else if (((tempGameVer >> i * 8) & 4311810305) == 4311810305) {
					dead_three++;
				}
			}
			//  x-xx- = 16842753,  xoxx- = 16843009,  oxxxo = 4311810305
			else if (((tempOppVer >> i * 8) & 4311810305) == 16842753) {
				if (((tempGameVer >> i * 8) & 4311810305) == 16842753) {
					oneSide_three++;
				}
				else if (((tempGameVer >> i * 8) & 4311810305) == 16843009) {
					oneSide_two++;
				}
			}
			//  xx-x- = 16777473,  xxox- = 16843009,  oxxxo = 4311810305
			else if (((tempOppVer >> i * 8) & 4311810305) == 16777473) {
				if (((tempGameVer >> i * 8) & 4311810305) == 16777473) {
					oneSide_three++;
				}
				else if (((tempGameVer >> i * 8) & 4311810305) == 16843009) {
					dead_two++;
				}
			}

			//  xx--- = 257,  xxo- = 65793, 
			//else if (((tempOppVer >> i * 8) & 4311810305) == 257) {
			//	if (((tempGameVer >> i * 8) & 4311810305) == 257) {
			//		open_two++;
			//	}
			//	else if (((tempGameVer >> i * 8) & 4311810305) == 65793) {
			//		oneSide_two++;
			//	}
			//}

			//  --xx- = 16842752,  --xxo = 4311810048,  -oxx- = 16843008, -oxxo = 4311810304
			//else if (((tempOppVer >> i * 8) & 4311810305) == 16842752) {
			//	if (((tempGameVer >> i * 8) & 4311810305) == 16842752) {
			//		open_two++;
			//	}
			//	else if (((tempGameVer >> i * 8) & 4311810305) == 4311810048 || (((tempGameVer >> i * 8) & 4311810305) == 16843008)) {
			//		oneSide_two++;
			//	}
			//	else if (((tempGameVer >> i * 8) & 4311810305) == 4311810304) {
			//		dead_two++;
			//	}
			//}
			//check -
			//		x
			//		x
			//		-
			// playerBoard: 65792 = -xx-, 16843008 = -xxo, 65793 = oxx-, 16843009 = oxxo
			else if (((tempOppVer >> i * 8) & 16843009) == 65792) {
				if (((tempGameVer >> i * 8) & 16843009) == 65792) {
					open_two++;
				}
				else if (((tempGameVer >> i * 8) & 16843009) == 16843008 || ((tempGameVer >> i * 8) & 16843009) == 65793) {
					oneSide_two++;
				}
				else if (((tempGameVer >> i * 8) & 16843009) == 16843009) {
					dead_two++;
				}
			}
			// 257 = xx--, 65793 = xxo-, 16843009 = oxxo
			else if (((tempOppVer >> i * 8) & 16843009) == 65792) {
				if (((tempGameVer >> i * 8) & 16843009) == 65792) {
					oneSide_two++;
				}
				else if (((tempGameVer >> i * 8) & 16843009) == 65793) {
					dead_two++;
				}
			}
			// 16777472 = -x-x, 16843008 = -xox,
			else if (((tempOppVer >> i * 8) & 16843009) == 16777472) {
				if (((tempGameVer >> i * 8) & 16843009) == 16777472) {
					oneSide_two++;
				}
			}
			// 65537 = x-x-, 65793 = xox-,
			else if (((tempOppVer >> i * 8) & 16843009) == 65537) {
				if (((tempGameVer >> i * 8) & 16843009) == 65537) {
					oneSide_two++;
				}
			}
		}
	}


	if ((open_three > 0 && open_two > 0) || oneSide_three > 1 || (open_three > 0 && oneSide_three > 0)){
		return 1500;
	}
	if (open_three > 0 && oneSide_two > 0) {
		return 1400;
	}
	if (open_three > 0) {
		return 1300;
	}
	if ((oneSide_three > 0 && open_two > 0) || open_two > 1) {
		return 300;
	}
	if (oneSide_three > 0 && oneSide_two > 0) {
		return 100;
	}
	if (oneSide_three > 0) {
		return 90;
	}
	if (open_two > 0 && oneSide_two > 0) {
		return 80;
	}
	if (open_two > 0) {
		return 70;
	}
	if (oneSide_two > 0) {
		return 30;
	}
	if (dead_three > 0) {
		return -5;
	}
	if (dead_two > 0) {
		return -5;
	}

	return 0;
}

int AI::getDef(Board board, int pos)
{
	if (checkPlayerWin(board)) {
		return 50000;
	}
	int dead_three = 0;
	int oneSide_three = 0;
	int open_three = 0;

	int dead_two = 0;
	int oneSide_two = 0;
	int open_two = 0;

	// check offsence
	int leftReminder = pos % 8;
	bitboard tempPlayer = (board.getPlayerBoard() >> (pos - leftReminder)) & 255;
	bitboard tempGame = board.getGameBoard() >> (pos - leftReminder);

	int topReminder = pos / 8;
	bitboard tempPlayerVer = board.getPlayerBoard() >> leftReminder;
	bitboard tempGameVer = board.getGameBoard() >> leftReminder;

	// horizontal 
	if (leftReminder == 0) {
		//if ((tempOpp & 15) == 15) {
		//	return 50000;
		//}
		// 7 = |ooo-,  15 = |ooox
		if ((tempPlayer & 15) == 7) {
			if ((tempGame & 15) == 7) {
				oneSide_three++;
			}
			else if ((tempGame & 15) == 15) {
				dead_three++;
			}
		}
		//|-ooo = 14
		else if ((tempPlayer & 15) == 14) {
			if ((tempGame & 15) == 14) {
				open_three++;
			}
			else if ((tempGame & 15) == 15) {
				oneSide_three++;
			}
		}
		//|-oo- = 6, |-oox
		else if ((tempPlayer & 15) == 6) {
			if ((tempGame & 15) == 6) {
				open_two++;
			}
			else if ((tempGame & 15) == 14) {
				dead_three++;
			}
			else if ((tempGame & 15) == 7) {
				oneSide_two++;
			}
		}
		//TODO |oo-o---- = 11, |ooxo----- = 15
		else if ((tempPlayer & 15) == 11) {
			if ((tempGame & 15) == 11) {
				oneSide_three++;
			}
			else if ((tempGame & 15) == 15) {
				dead_two++;
			}
		}

		//|o-oo----- = 13, |oxoo----- = 15
		else if ((tempPlayer & 15) == 13) {
			if ((tempGame & 15) == 13) {
				oneSide_three++;
			}
			else if ((tempGame & 15) == 15) {
				oneSide_two++;
			}
		}
		// 3 = |oo-, 7 = |oox, 
		else if ((tempPlayer & 7) == 3) {
			if ((tempGame & 7) == 3) {
				oneSide_two++;
			}
			else if ((tempGame & 7) == 7) {
				dead_two++;
			}
		}
		//|-oo = 6
		else if ((tempPlayer & 7) == 6) {
			if ((tempGame & 7) == 6) {
				open_two++;
			}
			else if ((tempGame & 7) == 7) {
				oneSide_two++;
			}
		}
	}
	else if (leftReminder == 7) {
		//if ((tempOpp & 240) == 240) {
		//	return 50000;
		//}

		// -----ooo| = 224, ----xooo| = 240, 
		if ((tempPlayer & 240) == 224) {
			if ((tempGame & 240) == 224) {
				oneSide_three++;
			}
			else if ((tempGame & 240) == 240) {
				dead_three++;
			}
		}
		// -ooo-| = 112,   ---xooo-| = 120,  ----ooox| = 240, 
		else if ((tempPlayer & 240) == 112) {
			if ((tempGame & 240) == 112) {
				open_three++;
			}
			else if ((tempGame & 240) == 120 || (tempGame & 240) == 240) {
				oneSide_three++;
			}
		}
		//TODO ----o-oo| = 208,   ----oxoo| = 240
		else if ((tempPlayer & 240) == 208) {
			if ((tempGame & 240) == 208) {
				oneSide_three++;
			}
			else if ((tempGame & 240) == 240) {
				dead_two++;
			}
		}
		// ----oo-o | = 176, ----ooxo| = 240
		else if ((tempPlayer & 240) == 176) {
			if ((tempGame & 240) == 176) {
				oneSide_three++;
			}
			else if ((tempGame & 240) == 240) {
				oneSide_two++;
			}
		}

		// -----oo-| = 96, ----xoo-| = 112 -----oox| = 224
		else if ((tempPlayer & 240) == 96) {
			if ((tempGame & 240) == 96) {
				open_two++;
			}
			else if ((tempGame & 240) == 112) {
				dead_three++;
			}
			else if ((tempGame & 240) == 224) {
				oneSide_two++;
			}
		}
		// ------oo| = 192, -----o-o| = 160, ----xoo| = 224, 
		else if ((tempPlayer & 224) == 192 || (tempPlayer & 224) == 160) {
			if ((tempGame & 224) == 192) {
				oneSide_two++;
			}
			else if ((tempGame & 224) == 160) {
				oneSide_two++;
			}
			else if ((tempGame & 224) == 224) {
				dead_two++;
			}
		}
		// ----oo--| = 48, ----oox-| = 112, ---xoox-| = 120, 
		else if ((tempPlayer & 120) == 48) {
			if ((tempGame & 120) == 48) {
				open_two++;
			}
			else if ((tempGame & 120) == 112) {
				oneSide_two++;
			}
			else if ((tempGame & 120) == 120) {
				dead_two++;
			}
		}

	}
	else {
		for (int i = 0; i < leftReminder; i++) {
			// 30 = -oooo,  15 = oooo-,  
			//if ((tempOpp >> i & 31) == 30 || (tempOpp >> i & 31) == 15) {
			//	return 50000;
			//}
			// 14 = -ooo-,  15 = -ooox,  30 = xooo-, 31 = xooox
			if ((tempPlayer >> i & 31) == 14) {
				if ((tempGame >> i & 31) == 14) {
					open_three++;
				}
				else if ((tempGame >> i & 31) == 15 || (tempGame >> i & 31) == 30) {
					oneSide_three++;
				}
				else if ((tempGame >> i & 31) == 31) {
					dead_three++;
				}
			}
			//TODO -oo1o = 22,  -ooxo = 30, oo1o-
			else if (((tempPlayer >> i) & 31) == 22) {
				if ((tempGame >> i & 31) == 22) {
					oneSide_three++;
				}
				else if ((tempGame >> i & 31) == 30) {
					oneSide_two++;
				}
			}

			//TODO -o-o = 10, -o1o = 14, ooxo = 15
			else if (((tempPlayer >> i) & 15) == 10) {
				if ((tempGame >> i & 15) == 10) {
					oneSide_two++;
				}
			}

			// chech -oo-
			// 6 = -oo-, gameBoard: 7 = -xxo, 14 = oxx-, 15 = oxxo
			else if (((tempPlayer >> i) & 15) == 6) {
				if (((tempGame >> i) & 15) == 6) {
					open_two++;
				}
				else if ((tempGame >> i & 15) == 7 || (tempGame >> i & 15) == 14) {
					oneSide_two++;
				}
				else if ((tempGame >> i & 15) == 15) {
					dead_two++;
				}
			}
			// o-o = 5, oxo = 7
			else if ((tempPlayer >> i & 7) == 5) {
				if (((tempGame >> i) & 7) == 5) {
					oneSide_two++;
				}
			}
		}

	}

	// vertical
	// |ooo----- = 65793, |ooox---- = 16843009
	if (topReminder == 0) {
		if ((tempPlayerVer & 16843009) == 65793) {
			if ((tempGameVer & 16843009) == 65793) {
				oneSide_three++;
			}
			else if ((tempGameVer & 16843009) == 4295033089) {
				dead_three++;
			}
		}
		//todo |oo-o---- = 16777473,  |ooxo----16843009 
		else if ((tempPlayerVer & 16843009) == 16777473) {
			if ((tempGameVer & 16843009) == 16777473) {
				oneSide_three++;
			}
			else if ((tempGameVer & 16843009) == 16843009) {
				dead_two++;
			}
		}
		// |-oo----- = 65792 , |xoo----- = 65793, |-oox---- = 16843008,
		else if ((tempPlayerVer & 16843009) == 65792) {
			if ((tempGameVer & 16843009) == 65792) {
				open_two++;
			}
			else if ((tempGameVer & 16843009) == 65793) {
				oneSide_two++;
			}
			else if ((tempGameVer & 16843009) == 16843008) {
				dead_three++;
			}
		}
		// |o-oo---- = 16842753
		else if ((tempPlayerVer & 16843009) == 16842753) {
			if ((tempGameVer & 16843009) == 16842753) {
				oneSide_three++;
			}
			else if ((tempGameVer & 16843009) == 16843009) {
				oneSide_two++;
			}
		}
		// |oo------ = 257, |oox----- = 65793
		else if ((tempPlayerVer & 65793) == 257) {
			if ((tempGameVer & 65793) == 257) {
				oneSide_two++;
			}
			else if ((tempGameVer & 65793) == 65793) {
				dead_two++;
			}
		}
		//|-oo---- = 65792, |-oox--- = 16843008
		else if ((tempPlayerVer & 16843008) == 65792) {
			if ((tempGameVer & 16843008) == 65792) {
				open_two++;
			}
			else if ((tempGameVer & 16843008) == 16843008) {
				dead_three++;
			}
		}
	}
	else if (topReminder == 7) {
		// -ooo| = 16843008, xooo| = 16843009, 
		if ((tempPlayerVer >> 32 & 16843009) == 16843008) {
			if ((tempGameVer >> 32 & 16843009) == 16843008) {
				oneSide_three++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 16843009) {
				dead_three++;
			}
		}
		//todo o-oo| = 16842753 , oxoo| = 16843009,   
		else if ((tempPlayerVer >> 32 & 16843009) == 16842753) {
			if ((tempGameVer >> 32 & 16843009) == 16842753) {
				oneSide_three++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 16843009) {
				dead_two++;
			}
		}
		// oo-o| = 16777473, 
		else if ((tempPlayerVer >> 32 & 16843009) == 16777473) {
			if ((tempGameVer >> 32 & 16843009) == 16777473) {
				oneSide_three++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 16843009) {
				oneSide_two++;
			}
		}
		//totototodododo
		// -oo-| = 65792, xoo-| = 65793,  -oox| = 65793, 
		else if ((tempPlayerVer >> 32 & 16843009) == 65792) {
			if ((tempGameVer >> 32 & 16843009) == 65792) {
				open_two++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 65793 || (tempGameVer >> 32 & 16843009) == 16843008) {
				dead_three++;
			}
		}
		// --oo| = 16842752, -xoo| = 16843008
		else if ((tempPlayerVer >> 32 & 16843009) == 16842752) {
			if ((tempGameVer >> 32 & 16843009) == 16842752) {
				oneSide_two++;
			}
			else if ((tempGameVer >> 32 & 16843009) == 16843008) {
				dead_two++;
			}
		}
	}
	else {
		//check -
		//		x
		//		x
		//		x
		//		-
		for (int i = 0; i < topReminder; i++) {
			//  -xxx- = 16843008,  oxxx- = 4311810304, -xxxo = 16843009, oxxxo = 4311810305
			if (((tempPlayerVer >> i * 8) & 4311810305) == 16843008) {
				if (((tempGameVer >> i * 8) & 4311810305) == 16843008) {
					open_three++;
				}
				else if (((tempGameVer >> i * 8) & 4311810305) == 4311810304 || ((tempGameVer >> i * 8) & 4311810305) == 16843009) {
					oneSide_three++;
				}
				else if (((tempGameVer >> i * 8) & 4311810305) == 4311810305) {
					dead_three++;
				}
			}
			//  x-xx- = 16842753,  xoxx- = 16843009,  oxxxo = 4311810305
			else if (((tempPlayerVer >> i * 8) & 4311810305) == 16842753) {
				if (((tempGameVer >> i * 8) & 4311810305) == 16842753) {
					oneSide_three++;
				}
				else if (((tempGameVer >> i * 8) & 4311810305) == 16843009) {
					oneSide_two++;
				}
			}
			//  xx-x- = 16777473,  xxox- = 16843009,  oxxxo = 4311810305
			else if (((tempPlayerVer >> i * 8) & 4311810305) == 16777473) {
				if (((tempGameVer >> i * 8) & 4311810305) == 16777473) {
					oneSide_three++;
				}
				else if (((tempGameVer >> i * 8) & 4311810305) == 16843009) {
					dead_two++;
				}
			}

			//  xx--- = 257,  xxo- = 65793, 
			//else if (((tempPlayerVer >> i * 8) & 4311810305) == 257) {
			//	if (((tempGameVer >> i * 8) & 4311810305) == 257) {
			//		open_two++;
			//	}
			//	else if (((tempGameVer >> i * 8) & 4311810305) == 65793) {
			//		oneSide_two++;
			//	}
			//}

			////  --xx- = 16842752,  --xxo = 4311810048,  -oxx- = 16843008, -oxxo = 4311810304
			//else if (((tempPlayerVer >> i * 8) & 4311810305) == 16842752) {
			//	if (((tempGameVer >> i * 8) & 4311810305) == 16842752) {
			//		open_two++;
			//	}
			//	else if (((tempGameVer >> i * 8) & 4311810305) == 4311810048 || (((tempGameVer >> i * 8) & 4311810305) == 16843008)) {
			//		oneSide_two++;
			//	}
			//	else if (((tempGameVer >> i * 8) & 4311810305) == 4311810304) {
			//		dead_two++;
			//	}
			//}
			//check -
			//		x
			//		x
			//		-
			// playerBoard: 65792 = -xx-, 16843008 = -xxo, 65793 = oxx-, 16843009 = oxxo
			else if (((tempPlayerVer >> i * 8) & 16843009) == 65792) {
				if (((tempGameVer >> i * 8) & 16843009) == 65792) {
					open_two++;
				}
				else if (((tempGameVer >> i * 8) & 16843009) == 16843008 || ((tempGameVer >> i * 8) & 16843009) == 65793) {
					oneSide_two++;
				}
				else if (((tempGameVer >> i * 8) & 16843009) == 16843009) {
					dead_two++;
				}
			}
			// 257 = xx--, 65793 = xxo-, 16843009 = oxxo
			else if (((tempPlayerVer >> i * 8) & 16843009) == 65792) {
				if (((tempGameVer >> i * 8) & 16843009) == 65792) {
					oneSide_two++;
				}
				else if (((tempGameVer >> i * 8) & 16843009) == 65793) {
					dead_two++;
				}
			}
			// 16777472 = -x-x, 16843008 = -xox,
			else if (((tempPlayerVer >> i * 8) & 16843009) == 16777472) {
				if (((tempGameVer >> i * 8) & 16843009) == 16777472) {
					oneSide_two++;
				}
			}
			// 65537 = x-x-, 65793 = xox-,
			else if (((tempPlayerVer >> i * 8) & 16843009) == 65537) {
				if (((tempGameVer >> i * 8) & 16843009) == 65537) {
					oneSide_two++;
				}
			}
		}
	}


	if ((open_three > 0 && open_two > 0) || oneSide_three > 1 || (open_three > 0 && oneSide_three > 0)) {
		return 1500;
	}
	if (open_three > 0 && oneSide_two > 0) {
		return 1400;
	}
	if (open_three > 0) {
		return 1300;
	}
	if ((oneSide_three > 0 && open_two > 0) || open_two > 1) {
		return 300;
	}
	if (oneSide_three > 0 && oneSide_two > 0) {
		return 100;
	}
	if (oneSide_three > 0) {
		return 90;
	}
	if (open_two > 0 && oneSide_two > 0) {
		return 80;
	}
	if (open_two > 0) {
		return 70;
	}
	if (oneSide_two > 0) {
		return 30;
	}
	if (dead_three > 0) {
		return -5;
	}
	if (dead_two > 0) {
		return -5;
	}
	return 0;
}

bool AI::checkPlayerWin(Board board)
{
	uint64_t player;
	// horizontal
	bitboard temp = board.getPlayerBoard();
	player = board.getPlayerBoard() >> 1 & board.getPlayerBoard();
	if (bitboard lowest = (player & player >> 2))
	{
		int pos = 0;
		bitboard m = 1LL;
		while (!(lowest & (m << ++pos)));

		int index = pos % 8;

		if (index < 5)
			return true;

		int iter_size = 8 - index;
		for (int i = 0; i < iter_size; ++i)
			temp = temp & ~(1LL << (pos + i));

		bitboard t = temp & temp >> 1;
		if (t & t >> 2)
			return true;
	}

	player = board.getPlayerBoard() >> 8 & board.getPlayerBoard();
	if ((player >> 16 & player) > 0) {
		return true;
	}
	return false;
}
bool AI::checkOppWin(Board board)
{
	uint64_t opp;
	bitboard temp = board.getOppBoard();
	// horizontal
	opp = board.getOppBoard() >> 1 & board.getOppBoard();

	if (bitboard lowest = (opp & opp >> 2))
	{
		int pos = 0;
		bitboard m = 1LL;
		while (!(lowest & (m << ++pos)));

		int index = pos % 8;

		if (index < 5)
			return true;

		int iter_size = 8 - index;
		for (int i = 0; i < iter_size; ++i)
			temp = temp & ~(1LL << (pos + i));

		bitboard t = temp & temp >> 1;
		if (t & t >> 2)
			return true;
	}
	// vertical
	opp = board.getOppBoard() >> 8 & board.getOppBoard();
	if ((opp >> 16 & opp) > 0) {
		return true;
	}
	return false;
}

//for checking h
void AI::print_arr(int arr[])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			string val_str = "x";
			int value = arr[i * 8 + j];
			if (value > -100000 && value < 100000)
				val_str = to_string(value);
			printf("%7s", val_str.c_str());
		}
		cout << endl;
	}
	cout << endl;
}



