/**************************************************************************
Pedro Lebron Guzman III, Nick Luckey, Tyler Stratford
02/23/2019
CS 471
Team Project: Checkers

Header File for Checkers game.


**** description of program

*************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>



using namespace std;


const int BOARDSIZE = 8;

enum spaceState
  {
    blank, // empty = 0
    w_piece, // white piece = 1
    b_piece, // black piece = 2
    w_king, // white king = 3
    b_king, // black king = 4
 };






class checkers
{

 private:
  enum spaceState Board[BOARDSIZE][BOARDSIZE];
  int w_pieces;
  int b_pieces;
  int playerturn;

  int Move(string initial, string dest);
  int convertMove(string move, int &y, int &x);
 public:
  checkers();
  ~checkers();


  string getMove();
  int parseMove(string move);
  void printBoard();

  void setPlayerTurn(int pt);
  int getPlayerTurn();

  int getBP();
  int getWP();

  spaceState** getBoard();
  int* convertBoard(spaceState** board);

  void generateBoard();

};
