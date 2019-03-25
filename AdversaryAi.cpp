#include "AdversaryAi.h"

AI::AI() {
}

AI::~AI() {}

string AI::getMove(spaceState** board,int flag) {
	string move;
	int* newboard = new int[32];
	newboard = convertBoard(board);

	moves moveset = IterativeDeepSearch(newboard, 3);

	if (flag == 0) {
		move = int_to_string(moveset);
	}
	else if (flag == 2) {
		move = double_to_string(moveset);
	}
	cout << "Move " << move << endl;
	return move;
}

string AI::int_to_string(moves moveset)
{
	string res = "";
	char temp;
	int ix, dx, iy, dy;
	iy = (moveset.from / 4)*-1 + 7;
	dy = (moveset.to / 4)*-1 + 7;

	if (iy % 2 == 1) {
		ix = ((moveset.from)% 4) * 2 + 1;
	}
	else {
		ix = ((moveset.from) % 4) * 2;
	}

	if (dy % 2 == 1) {
		dx = ((moveset.to) % 4) * 2 + 1;
	}
	else {
		dx = ((moveset.to) % 4) * 2;
	}

	temp = ix + 65;
	res = res + temp;
	temp = iy + 49;
	res = res + temp;
	res = res + " ";
	temp = dx + 65;
	res = res + temp;
	temp = dy + 49;
	res = res + temp;
	return res;
}

string AI::double_to_string(moves moveset) {
	string newstring;
	if (moveset.multi.size() > 0) {
		 newstring = int_to_string(moveset.multi[0]);
		moveset.multi.erase(moveset.multi.begin());
	}
	return newstring.substr(newstring.find(" ") + 1, newstring.length() - 1);
}

moves AI::IterativeDeepSearch(int* board, int max_depth) {
	Node root;
	Node mainroot;
	root.parent = NULL;
	for (int i = 0; i < 32; i++) {
		root.Ply.Board[i] = board[i];
	}
		// Generate the plays available to a given root node
	mainroot = root;
	for (int i = 0; i <= max_depth; i++) {
		mainroot = DFS(root, i, -INFINITE, INFINITE, 0);
		cout << mainroot.children.size() << endl;
		if (mainroot.Hval > 10)
			break;
	}
	cout << "iterative search" << endl;
	for (int i = 0; i < mainroot.children.size(); i++) {
		cout << mainroot.Hval << " " << mainroot.children.at(i)->Hval << endl;
		if (mainroot.children.at(i)->Hval == mainroot.Hval) {
			cout << "Score of " << mainroot.Hval << endl;
			return mainroot.Ply.pMoves.at(i);
		}
	}
	cout << "fucked up" << endl;
}

Node AI::DFS(Node root, int depth, int alpha, int beta, int optimizer) {
	int value;
	int rootvalue;
	bool b = false;
	root.Ply.generateMoves(root.Ply.Board, root.Ply.pMoves, true, b);
	if (depth == 0) {
		root.Hval = root.Zval;
		return root;
	}
	if (root.parent == NULL) {
		cout << root.Ply.pMoves.size() << endl;
		value = -INFINITE;
	}
	else if (root.parent->maxi) {
		value = INFINITE;
		root.maxi = false;
	}
	else {
		value = -INFINITE;
		root.maxi = true;
	}

	// New Searches
	for (int y = 0; y < root.Ply.pMoves.size(); y++) {						// Add created children to the parent
		root.children.push_back(new Node);
		for (int i = 0; i < 32; i++) {
			root.children.at(y)->Ply.Board[i] = root.Ply.Board[i];
		}
		root.children.at(y)->Ply.updateBoard(root.children.at(y)->Ply.Board, root.Ply.pMoves.at(y));
		root.children.at(y)->parent = &root;
		root.children.at(y)->Zval = root.Zval + root.Ply.pMoves.at(y).value;
		rootvalue = DFS(*root.children.at(y), depth - 1, alpha, beta, 0).Hval;
		root.children.at(y)->Hval = rootvalue;
		if (root.maxi && rootvalue > value) {
			value = rootvalue;
			root.Hval = value;
			if (value <= beta) {
				alpha = value;
				y++;
				while (y < root.Ply.pMoves.size()) {
					root.children.push_back(new Node);
					for (int i = 0; i < 32; i++) {
						root.children.at(y)->Ply.Board[i] = root.Ply.Board[i];
					}
					root.children.at(y)->Ply.updateBoard(root.children.at(y)->Ply.Board, root.Ply.pMoves.at(y));
					root.children.at(y)->parent = &root;
					root.children.at(y)->Zval = root.Zval + root.Ply.pMoves.at(y).value;
					rootvalue = DFS(*root.children.at(y), depth - 1, alpha, beta, 0).Hval;
					root.children.at(y)->Hval = rootvalue;
					y++;
					if (rootvalue > value) {
						value = rootvalue;
						root.Hval = value;
					}
					if (value > beta) {		// Cut stuff
						cout << "pruned max" << endl;
						y = root.Ply.pMoves.size();
						break;
					}
				}
				
			}
			for (int i = 0; i < root.children.size(); i++) {
				cout << root.Hval << " " << root.children.at(i)->Hval << endl;
			}
				return root;
		}
		else if (!root.maxi && rootvalue < value) {
			value = rootvalue;
			root.Hval = value;
			if (value >= alpha) {
				beta = value;
				y++;
				while (y < root.Ply.pMoves.size()) {
					root.children.push_back(new Node);
					for (int i = 0; i < 32; i++) {
						root.children.at(y)->Ply.Board[i] = root.Ply.Board[i];
					}
					root.children.at(y)->Ply.updateBoard(root.children.at(y)->Ply.Board, root.Ply.pMoves.at(y));
					root.children.at(y)->parent = &root;
					root.children.at(y)->Zval = root.Zval + root.Ply.pMoves.at(y).value;
					rootvalue = DFS(*root.children.at(y), depth - 1, alpha, beta, 0).Hval;
					root.children.at(y)->Hval = rootvalue;
					y++;
					if (rootvalue < value) {
						value = rootvalue;
						root.Hval = value;
					}
					if (value < alpha) {		// Cut stuff
						cout << "pruned min" << endl;
						y = root.Ply.pMoves.size();
						break;
					}
				}

			}
			for (int i = 0; i < root.children.size(); i++) {
				cout << root.Hval << " " << root.children.at(i)->Hval << endl;
			}
			return root;
		}
	}


}

int* AI::convertBoard(spaceState** board) {
	int* newboard = new int[32];
	int temp;

	int w = 0;
	for (int y = 7; y >= 0; y--) {
		for (int x = 0; x < 8; x++) {
			if (x % 2 == 1 && y%2 == 1) {
				temp = (int)board[x][y];
				if (temp == 2) {
					temp = temp - 3;
				}
				else if (temp == 3) {
					temp = temp - 1;
				}
				else if (temp == 4) {
					temp = temp - 6;
				}
				newboard[w] = temp;
				w++;
			}
			else if (x % 2 == 0 && y % 2 == 0) {
				temp = (int)board[x][y];
				if (temp == 2) {
					temp = temp - 3;
				}
				else if (temp == 3) {
					temp = temp - 1;
				}
				else if (temp == 4) {
					temp = temp - 6;
				}
				newboard[w] = temp;
				w++;
			}
		}
	}

	/*for (int i = 0; i < 32; i++) {
		cout << newboard[i] << endl;
	}*/
	return newboard;
}

