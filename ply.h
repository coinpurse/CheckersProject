#include <iostream>
#include <vector>

using namespace std;

struct moves
{
  int from;
  int to;
  int value;
  int capture;
  vector<moves> multi;
};


class ply
{
 public:
  int Board[32];
  vector<moves> pMoves;
  
  ply();
  ~ply();
  //Utility Functions
  void getWmoves(const int[],vector<moves>&,int, bool);
  void getBmoves(const int[],vector<moves>&,int, bool);
  bool doubleJump(const int [], vector<moves>&, int, bool);  
  void updateBoard(int Board[], moves m);
  

    //Purpose: Given a state of current board, generate all a vector containing all legal moves for the player
    //Parameters: Board object containing current piece positions
    void generateMoves(const int[],vector<moves>&, bool,bool&);
    
    
    
};

  
