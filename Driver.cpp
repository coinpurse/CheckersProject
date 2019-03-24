#include <iostream>;
#include "checkers.h";

using namespace std;

int main() { 
	checkers cboard;
	int flag = 0;
	cboard.generateBoard();
	while (true) {
		while (flag == 0 || flag == 2) {
			if (flag == 2) {
				cout << "Enter Jump location" << endl;
			}
			else cout << "Enter new move" << endl;
			flag = cboard.parseMove(cboard.getMove());
		}
		cboard.printBoard();
		if (cboard.getWP() == 0) {
			cout << "Black player wins!" << endl;
			break;
		}
		else if (cboard.getBP() == 0) {
			cout << "White player wins!" << endl;
			break;
		}
		if (cboard.getPlayerTurn() == 0) {
			cboard.setPlayerTurn(1);
		}
		else cboard.setPlayerTurn(0);
		flag = 0;
	}
		return 0;
}