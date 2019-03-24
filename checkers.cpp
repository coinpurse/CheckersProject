/**************************************************************************
Pedro Lebron Guzman III, Nick Luckey, Tyler Stratford
02/23/2019
CS 471
Team Project: Checkers

Header File for Checkers game.


**** description of program

*************************************************************************/

#include "checkers.h"

//constructor
checkers::checkers()
{
  w_pieces = 8;
  b_pieces = 8;
  playerturn = 0;
  for (int x = 0; x < BOARDSIZE; x++) {
	  for (int y = 0; y < BOARDSIZE; y++) {
		  Board[x][y] = blank;
	  }
  }
  return;
}

// Destructor
checkers::~checkers() {}


void checkers::generateBoard()
{
  
  for(int n=5;n<8;n++)
    {
      for(int m=0;m<8;m++)
		{
		  if ((n % 2 == 1) && (m % 2 == 1))
			  Board[m][n] = w_piece;
		  else if ((n % 2 == 0) && (m % 2 == 0))
			  Board[m][n] = w_piece;
		}
    }


  for(int n=0;n<3;n++)
    {
      for(int m=0;m<8;m++)
        {
		  if ((m % 2 == 0) && (n % 2 == 0))
			  Board[m][n] = b_piece;
		  else if ((m % 2 == 1) && (n % 2 == 1))
			  Board[m][n] = b_piece;
        }
    }

  printBoard();
  return;
}

void checkers::printBoard() {
	char num;
	cout << "  ";
	for (int x = 0, num = 'A'; x < (BOARDSIZE * 2 + 1); x++) {
		if (x % 2 == 1) {
			printf("%c", num);
			num++;
		}
		else
			cout << " ";
	}
	cout << endl << "  ";

	for (int x = 0; x < (BOARDSIZE*2 + 1); x++) {
		cout << "-";
	}
	cout << endl;

	for (int y = BOARDSIZE - 1; y >= 0; y--) {
		cout << y + 1 << " ";
		for (int x = 0; x < BOARDSIZE*2 + 1; x++) {
				if (x % 2 == 0) {
					cout << "|";
				}
				else {
					if (Board[x / 2][y] == blank) {
						cout << " ";
					}
					else if (Board[x / 2][y] == w_piece) {
						cout << "w";
					}
					else if (Board[x / 2][y] == b_piece) {
						cout << "b";
					}
					else if (Board[x / 2][y] == w_king) {
						cout << "$";
					}
					else if (Board[x / 2][y] == b_king) {
						cout << "#";
					}
				}
		}
		cout << endl;
	}
	cout << "  ";
	for (int x = 0; x < (BOARDSIZE * 2 + 1); x++) {
		cout << "-";
	}
	cout << endl;
	return;
}

int checkers::parseMove(string move) {
	static string initial;
	static int flag;
	static string dest;
	
	if(flag == 2){
		initial = dest;
		dest = move;
	}
	else {
		initial = move.substr(0, move.find(" "));
		dest = move.substr(move.find(" ") + 1, move.length() - 1);
	}
	flag = Move(initial, dest);
	return flag;
}
int checkers::Move(string initial, string dest) {
	int ix, iy, dx, dy;
	int flag = 1;
	spaceState piece;

	if (convertMove(initial, iy, ix) == 0){
		return 0;
	}
	if (convertMove(dest, dy, dx) == 0) {
		return 0;
	}

	if (Board[ix][iy] != blank && Board[dx][dy] == blank) { // Check to see if there is a valid piece on the initial coord
		piece = Board[ix][iy];								// and a blank space on the destination coord
		if (ix == dx) {
			cout << "Invalid Move" << endl;
			return 0;
		}
		if (playerturn == 0 && (piece == b_piece || piece == b_king)) {
			if (piece == b_piece) {
				if (dy - iy == 1 && (dx - ix == 1 || dx - ix == -1)) {
					Board[dx][dy] = Board[ix][iy];
					Board[ix][iy] = blank;
					cout << Board[ix][iy] << endl;
				}
				else if (dy - iy == 2 && (dx - ix == 2 || dx - ix == -2)) {
					if (dx > ix) {
						if (Board[dx - 1][dy - 1] == w_piece || Board[dx - 1][dy - 1] == w_king) {
							Board[dx - 1][dy - 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							w_pieces--;
						}
						else {
							cout << "Invalid Move" << endl;
							return 0;
						}
					}
					else if (dx < ix) {
						if (Board[ix - 1][dy - 1] == w_piece || Board[ix - 1][dy - 1] == w_king) {
							Board[ix - 1][dy - 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							w_pieces--;
						}
						else {
							cout << "Invalid Move" << endl;
							return 0;
						}
					}
					else {
						cout << "Invalid move" << endl;
						return 0;
					}
					if((Board[dx + 2][dy + 2] == blank && (Board[dx + 1][dy + 1] == w_piece || Board[dx + 1][dy + 1] == w_king))&&
					dy+2 >= 0 && dy+2 <= 7 && dx+2 >= 0 && dx+2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
					else if ((Board[dx - 2][dy + 2] == blank && (Board[dx - 1][dy + 1] == w_piece || Board[dx - 1][dy + 1] == w_king)) &&
						dy + 2 >= 0 && dy + 2 <= 7 && dx - 2 >= 0 && dx - 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
				}
				else{
					cout << "Invalid Move" << endl;
					return 0;
				}
				if(dy == 7) Board[dx][dy] = b_king;
			}
			else if (piece == b_king) {
				if ((dy - iy == -1 && (dx - ix == 1 || dx - ix == -1)) || (dy - iy == 1 && (dx - ix == 1 || dx - ix == -1))) {
					Board[dx][dy] = Board[ix][iy];
					Board[ix][iy] = blank;
				}
				else if ((dy - iy == 2 && (dx - ix == 2 || dx - ix == -2)) || (dy - iy == -2 && (dx - ix == 2 || dx - ix == -2))) {
					if (dx > ix) {
						if (Board[dx - 1][dy - 1] == w_piece || Board[dx - 1][dy - 1] == w_king) {
							Board[dx - 1][dy - 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							w_pieces--;
						}
						else if (Board[dx - 1][dy + 1] == w_piece || Board[dx - 1][dy + 1] == w_king) {
							Board[dx - 1][dy + 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							w_pieces--;
						}
						else {
							cout << "Invalid Move" << endl;
							return 0;
						}
					}
					else if (dx < ix) {
						if (Board[ix - 1][dy - 1] == w_piece || Board[ix - 1][dy - 1] == w_king) {
							Board[ix - 1][dy - 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							w_pieces--;
						}
						else if (Board[ix - 1][dy + 1] == w_piece || Board[ix - 1][dy + 1] == w_king) {
							Board[ix - 1][dy + 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							w_pieces--;
						}
						else {
							cout << "Invalid Move" << endl;
							return 0;
						}
					}
					if ((Board[dx + 2][dy + 2] == blank && (Board[dx + 1][dy + 1] == w_piece || Board[dx + 1][dy + 1] == w_king)) &&
						dy + 2 >= 0 && dy + 2 <= 7 && dx + 2 >= 0 && dx + 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
					else if ((Board[dx - 2][dy + 2] == blank && (Board[dx - 1][dy + 1] == w_piece || Board[dx - 1][dy + 1] == w_king)) &&
						dy + 2 >= 0 && dy + 2 <= 7 && dx - 2 >= 0 && dx - 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
					else if ((Board[dx + 2][dy - 2] == blank && (Board[dx + 1][dy - 1] == w_piece || Board[dx + 1][dy - 1] == w_king)) &&
						dy - 2 >= 0 && dy - 2 <= 7 && dx + 2 >= 0 && dx + 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
					else if ((Board[dx - 2][dy - 2] == blank && (Board[dx - 1][dy - 1] == w_piece || Board[dx - 1][dy - 1] == w_king)) &&
						dy - 2 >= 0 && dy - 2 <= 7 && dx - 2 >= 0 && dx - 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
				}
				else {
					cout << "Invalid Move" << endl;
					return 0;
				}
			}
		}
		else if (playerturn == 1 && (piece == w_piece || piece == w_king)) {
			if (piece == w_piece) {
				if (dy - iy == -1 && (dx - ix == 1 || dx - ix == -1)) {
					Board[dx][dy] = Board[ix][iy];
					Board[ix][iy] = blank;
				}
				else if (dy - iy == -2 && (dx - ix == 2 || dx - ix == -2)) {
					if (dx > ix) {
						if (Board[dx - 1][dy + 1] == b_piece || Board[dx - 1][dy + 1] == b_king) {
							Board[dx - 1][dy + 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							b_pieces--;
						}
						else {
							cout << "Invalid Move" << endl;
							return 0;
						}
					}
					else if (dx < ix) {
						if (Board[ix - 1][dy + 1] == b_piece || Board[ix - 1][dy + 1] == b_king) {
							Board[ix - 1][dy + 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							b_pieces--;
						}
						else {
							cout << "Invalid Move" << endl;
							return 0;
						}
					}
					else {
						cout << "Invalid move" << endl;
						return 0;
					}
					cout << "I am here" << endl << Board[dx + 2][dy - 2] << endl << Board[dx + 1][dy-1] << endl;
					if ((Board[dx + 2][dy - 2] == blank && (Board[dx + 1][dy - 1] == b_piece || Board[dx + 1][dy - 1] == b_king)) &&
						dy - 2 >= 0 && dy - 2 <= 7 && dx + 2 >= 0 && dx + 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
					else if ((Board[dx - 2][dy - 2] == blank && (Board[dx - 1][dy - 1] == b_piece || Board[dx - 1][dy - 1] == b_king)) &&
						dy - 2 >= 0 && dy - 2 <= 7 && dx - 2 >= 0 && dx - 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
				}
				else {
					cout << "Invalid Move" << endl;
					return 0;
				}
				if (dy == 0) Board[dx][dy] = w_king;
			}
			else if (piece == w_king) {
				if ((dy - iy == -1 && (dx - ix == 1 || dx - ix == -1)) || (dy - iy == 1 && (dx - ix == 1 || dx - ix == -1))) {
					Board[dx][dy] = Board[ix][iy];
					Board[ix][iy] = blank;
				}
				else if ((dy - iy == 2 && (dx - ix == 2 || dx - ix == -2)) || (dy - iy == -2 && (dx - ix == 2 || dx - ix == -2))) {
					if (dx > ix) {
						if (Board[dx - 1][dy - 1] == b_piece || Board[dx - 1][dy - 1] == b_king) {
							Board[dx - 1][dy - 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							b_pieces--;
						}
						else if (Board[dx - 1][dy + 1] == b_piece || Board[dx - 1][dy + 1] == b_king) {
							Board[dx - 1][dy + 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							b_pieces--;
						}
						else {
							cout << "Invalid Move" << endl;
							return 0;
						}
					}
					else if (dx < ix) {
						if (Board[ix - 1][dy - 1] == b_piece || Board[ix - 1][dy - 1] == b_king) {
							Board[ix - 1][dy - 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							b_pieces--;
						}
						else if (Board[ix - 1][dy + 1] == b_piece || Board[ix - 1][dy + 1] == b_king) {
							Board[ix - 1][dy + 1] = blank;
							Board[dx][dy] = Board[ix][iy];
							Board[ix][iy] = blank;
							b_pieces--;
						}
						else {
							cout << "Invalid Move" << endl;
							return 0;
						}
					}
					if ((Board[dx + 2][dy + 2] == blank && (Board[dx + 1][dy + 1] == b_piece || Board[dx + 1][dy + 1] == b_king)) &&
						dy + 2 >= 0 && dy + 2 <= 7 && dx + 2 >= 0 && dx + 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
					else if ((Board[dx - 2][dy + 2] == blank && (Board[dx - 1][dy + 1] == b_piece || Board[dx - 1][dy + 1] == b_king)) &&
						dy + 2 >= 0 && dy + 2 <= 7 && dx - 2 >= 0 && dx - 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
					else if ((Board[dx + 2][dy - 2] == blank && (Board[dx + 1][dy - 1] == b_piece || Board[dx + 1][dy - 1] == b_king)) &&
						dy - 2 >= 0 && dy - 2 <= 7 && dx + 2 >= 0 && dx + 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
					else if ((Board[dx - 2][dy - 2] == blank && (Board[dx - 1][dy - 1] == b_piece || Board[dx - 1][dy - 1] == b_king)) &&
						dy - 2 >= 0 && dy - 2 <= 7 && dx - 2 >= 0 && dx - 2 <= 7) {
						cout << "Possible jump detected" << endl;
						flag = 2;
					}
				}
				else {
					cout << "Invalid Move" << endl;
					return 0;
				}
			}
		}
		else {
			cout << "Invalid Move: The piece selected is not yours" << endl;
			return 0;
		}
	}
	else {
		cout << "Invalid Move: Either there is no piece where you selected or there is already a piece in the spot youre trying to go" << endl;
		return 0;
	}
	return flag;
}

void checkers::setPlayerTurn(int pt) {
	playerturn = pt;
	return;
}
int checkers::getPlayerTurn() {
	return playerturn;
}

int checkers::getBP() {
	return b_pieces;
}
int checkers::getWP() {
	return w_pieces;
}

int checkers::convertMove(string move, int &y, int &x) {
	if (move.length() != 2) {
		cout << "Invalid Format: Move must be in the form of {letter}{number}. ex. A4" << endl;
		return 0;
	}
	if (move[0] < 'A' || move[0] > 'H') {
		cout << "Invalid Input: The letter must be in the range of A-H" << endl;
		return 0;
	}
	if (move[1] < '1' || move[1] > '8') {
		cout << "Invalid Input: The number must be in the range of 1-8" << endl;
		return 0;
	}
	x = move[0] - 65;
	y = move[1] - 49;
	return 1;
}

string checkers::getMove() {
	string move;
	getline(cin, move);
	return move;
}