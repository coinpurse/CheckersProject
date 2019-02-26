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



using namespace std;

//PCB is a 5 digit number "aabbc" such that aa = priority number, bb = Process ID, and c = Status
//typedef unsigned short proc;


enum spaceState
  {
    empty, // empty = 0
    w_piece, // white piece = 1
    b_piece, // black piece = 2
    w_king, // white king = 3
    b_king, // black king = 4
 };






class checkers
{

 private:
  enum spaceState Board[8][8] ;
  int w_pieces;
  int b_pieces;

  void terminal();
  int generateMove(int, int);
  void capture(spaceState&, int, int);

 public:
  checkers();
  ~checkers();

  void initialState();
  void testing();

};
