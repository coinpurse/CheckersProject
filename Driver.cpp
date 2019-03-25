#include <iostream>
//#include "AIfunctions.h"
//#include "checkers.h"
#include "AdversaryAi.h"

using namespace std;

int main() { 
	checkers cboard;
	//AIfunctions ai;
	AI ai;
	string aimove;
	int value;
	int flag = 0;
	cboard.generateBoard();
	cboard.setPlayerTurn(1);
	while (true) {
		
		// AI Turn
		flag = 0;
		cboard.setPlayerTurn(1);

		cout << "AI Turn" << endl;

		while (flag == 0 || flag == 2) {
			if (flag == 2) {
				cout << "Enter Jump location" << endl;
			}
			else
				cout << "Enter new move" << endl;
			//value = ai.Alpha_Beta(-INFINITE, INFINITE, 0, true, 0, cboard.convertBoard(cboard.getBoard()));
			//aimove = ai.int_to_string(value);
			//cout << value << endl;
			//cout << aimove << endl;
			flag = cboard.parseMove(ai.getMove(cboard.getBoard(), flag));
		}
		cboard.printBoard();
		cout << "Black pieces left: " << cboard.getBP() << endl;
		cout << "White pieces left: " << cboard.getWP() << endl;
		if (cboard.getWP() == 0) {
			cout << "Black player wins!" << endl;
			break;
		}
		else if (cboard.getBP() == 0) {
			cout << "White player wins!" << endl;
			break;
		}
		
		
		// Player Turn
		cboard.setPlayerTurn(0);
		flag = 0;
		cout << "Player turn" << endl;
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
		
	}
		return 0;
}