/**************************************************************************
Pedro Lebron Guzman III, Nick Luckey, Tyler Stratford
02/23/2019
CS 471
Team Project: Checkers

Header File for Checkers game.


**** description of program

*************************************************************************/

#include "checkers.h"
#include <stdlib.h>


//constructor
checkers::checkers()
{
  w_pieces = 8;
  b_pieces = 8;

  for(int n=0;n<8;n++)
    {
      for(int m=2;m<10;m++)
        {
          Board[n][m-2] = empty;
        }
    }

}

// Destructor
checkers::~checkers() {}


void checkers::initialState()
{
  


  for(int n=0;n<3;n++)
    {
      for(int m=0;m<8;m++)
	{
	  if((n%2)!= (m%2))
	    Board[n][m] = w_piece;
	}
    }


  for(int n=5;n<8;n++)
    {
      for(int m=0;m<8;m++)
        {
          if((n%2)!= (m%2))
            Board[n][m] = b_piece;
        }
    }

}

// Purpose:
// Arguments:
void checkers::testing()
{
  for(int n=0;n<8;n++)
    {
      for(int m=0;m<8;m++)
	{
	  cout << " " << Board[n][m] << " " ;
	}
      cout << endl;
    }


}


int checkers::generateMove(int n, int m)
{
  spaceState p;
  
  p=Board[n][m];
  
  if(Board[n][m] == 0)
    return 0;
  
  else if(Board[n+1][m+1] = p)
    return 0;
  
  else if(Board[n][m]== (2 || 4))
     goto b_move;
    
  else
    {
      //If a piece is along left side of board
      if(m==0)
	{
	  //If piece can move to empty spot
	  if(Board[n+1][m+1]==0)
	    {
      	      Board[n+1][m+1] = p;
	      Board[n][m] = empty;
	      return 1;
	    }
	  else
	    {
	      //If white can capture black piece
	      if(Board[n+2][m+2] == 0)
		{
		  Board[n+1][m+1] = empty;
		  Board[n][m] = empty;
		  Board[n+2][m+2] = p;
		  return 2;
		}
	      // Otherwise the piece cannot move
	      else 
		return 0;
	    }
	}

    }
  
  
  
 b_move:
  return 2;
  
}





void checkers::terminal()
{
  if(b_pieces==0)
    {
      cout << "Player 2 has no pieces left... Player 1 wins!" << endl;
      exit(1);
    }
  else if(w_pieces==0)
    {
      cout << "Player 1 has no pieces left... Player 2 wins!" << endl;
      exit(1);
    }
  
  else
    return;
}
