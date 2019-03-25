#include "checkers.h"
#include "ply.h"

using namespace std;

const int MAXDEPTH = 20;
const int INFINITE = 50000;

struct Node {
	Node* parent;
	ply Ply;
	int Hval = 0;
	int Zval = 0;
	bool maxi = true;
	vector<Node*> children;
};

class AI {
private:
	string AI::int_to_string(moves moveset);
	
	moves IterativeDeepSearch(int* board, int max_depth);
	Node DFS(Node root, int depth, int alpha, int beta, int optimizer);
public:
	AI();
	~AI();
	string getMove(spaceState** board, int flag);
	int* convertBoard(spaceState** board);
	string AI::double_to_string(moves moveset);
};
