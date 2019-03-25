#include "ply.h"
#include <vector>
#include <iomanip>
using namespace std;



ply::ply(){};
ply::~ply(){};

//apply a jump, update board with jump, and check if another jump is available
bool ply::doubleJump(const int B[], vector<moves>& pmoves, int i, bool max)
{
  //cout << " " << endl;
  
  int M[32];
  vector<moves> dj;
  int index=0;
  int k=0;
  int count=0;



  
  //create copy of the board
  for(int i=0;i<32;i++)
    {
      M[i]=B[i];
    }

 // cout << "here" << endl;
  //make copy of move that lead to a capture
  dj.push_back(pmoves[i]);
  //cout << "here 2" << endl;
  do{
    //apply first jump to check if next jump avail
    updateBoard(M, dj[index]);
    //index++;

    //dj[index].from=dj[index-1].to;
    
   //new position of piece that just jumped
    k=dj[index].to;
    //cout << "Board updated and new position is.... " << k << endl;
    count = dj.size();
   
    
    if(max)
      { 
	getWmoves(M,dj,k,max);
      if(M[k]==2)
	getBmoves(M,dj,k,max);
      }
    
    else
      {
	
	getBmoves(M,dj,k,max);
	if(M[k]==-2)
	  getWmoves(M,dj,k,max);
      }
    

        //erase empty moves in DJ and if there is still a new move left over then double jump is found
    for(int i=1;i<dj.size();i++)
      {
	if(dj[i].value==0)
	  dj.erase(dj.begin()+i);
	
      }

    //cout << "count before and count after get moves:  " << count << "   " << dj.size() << endl;

    
   // if no move found return false
    if(dj.size()<2)
      return false;
    //if move is not sequential jump then remove
    else if(dj.size()-count>=2)
      {
	dj.pop_back();
	
      }

    
    //cout << "last move is: " << dj[dj.size()-1].from << " " << dj[dj.size()-1].to << endl;
    //cout << "value is: " << dj[dj.size()-1].value << endl;
    
    
    //if new non capture moves exist, break and return true
    if(dj.size()==count )
      break;

  
  }while(true);
  
  for (int i = 0; i<dj.size(); i++)
  {
	  if (i>0 && dj[i].from != dj[i - 1].to)
	  {
		  dj.pop_back();
		  i--;
	  }

	  else
		  pmoves[i].multi.push_back(dj[i]);


  }

  for(int i=0;i<pmoves.size();i++)
    {

     // cout << "pmoves contains:   " << endl;
      //cout << "from and to " << pmoves[i].from << "   "  << pmoves[i].to << endl;
      //cout << " value        " << pmoves[i].value << endl;

      

    }
  
  return true;
  
  
  
}

//update board for double jumps  
void ply::updateBoard( int Board[],moves m)
{
  Board[m.to]=Board[m.from];
  
      
  if(Board[m.from]==1 && m.to>=28)
    Board[m.to]=2;
  
  else if(Board[m.from]==-1 && m.to <=3)
    Board[m.to]=-2;
  
  Board[m.from]=0;
  
  
  if(abs(m.from-m.to) <6)
  {
      return; 
    }
  else
    {
	  
      if(m.from-m.to == 7)
	{
	  if(m.from%8<4)
	    {
	      Board[m.from-3]=0;
	      Board[m.from]=0;
	   }
	  else
	    {
	      Board[m.from-4]=0;
	      Board[m.from]=0;
	    }
	  
	}
      else if(m.from-m.to == -7)
	{
	  if(m.from%8<4)
	    {
	      Board[m.from+4]=0;
	      Board[m.from]=0;
	    }
	  else
	    {
	      Board[m.from+3]=0;
	      Board[m.from]=0;
	    }
	  
        }
      else if(m.from-m.to == 9)
	
	{
	  if(m.from%8<4)
	    {
	      Board[m.from-4]=0;
	      Board[m.from]=0;
	    }
	  else
	    {
	      Board[m.from-5]=0;
	      Board[m.from]=0;
	    }
	}
      else
	{ 
	  if(m.from%8<4)
            {
              Board[m.from+5]=0;
              Board[m.from]=0;
            }
          else
            {
              Board[m.from+4]=0;
              Board[m.from]=0;
            }
        }

    }    
}



  




void ply::getWmoves(const int B[32], vector<moves>& movesList, int i, bool max)
{
  moves n;
  n.capture=0;
  int t; //var for King
  (B[i]==-2)? t=1: t=-1;
  
  //Even row and not empty space
  if(i%8>=4 && B[i]!=0 && B[i]!=-1 && i<28)
    {
      
	  if(i%8!=4)
	    {//Check for Down and Left moves
	      if(B[i+3]==0)//move to empty space
		{
		  n.from = i;
		  n.to = i+3;
		  n.value=0;
		  movesList.push_back(n);
		}
	      else if(i<24 && B[i+3]!=B[i] && B[i+3]!=(2*B[i]))//check if occupied space is opponent's piece
		{
		  if(B[i+7]==0)//if jump is available
		    {
		      n.from = i;
		      n.to = i+7;
		      (B[i+3]==(t*B[i]))? n.value=B[i+3]: n.value=B[i+3]*3;
		      n.value *=-1;
		      n.capture=i+3;
		      movesList.push_back(n);

		    }
		}
	      
	    }
	  
	  //Check for Down and Right moves
          if(B[i+4]==0 )//move to empty space
            {
              n.from = i;
              n.to = i+4;
              n.value=0;
              movesList.push_back(n);
            }
          else if(i<23 && (i%8!=7) &&  B[i+4]!=B[i] && B[i+4]!=(2*B[i]))//check if occupied space is opponent's piece
            {
	      
              if(B[i+9]==0)//if jump is available
                {
                  n.from = i;
                  n.to = i+9;
		  (B[i+4]==(t*B[i]))? n.value=B[i+4]: n.value=B[i+4]*3;
		  n.value *=-1;
                  n.capture=i+4;
		  movesList.push_back(n);

                }
            }
    }

  //Odd Row and not empty space
  else if(i%8<4 && B[i]!=0 && B[i]!=-1 && i<28)
        {
	  
          
	  //Check for Down and Left moves
	  if(B[i+4]==0 )//move to empty space
	    {
	      n.from = i;
	      n.to = i+4;
	      n.value=0;
	      movesList.push_back(n);
	    }
	  //If not left side of board and occupied space is opponents piece
	  else if(i<23 && (i%8!=0) &&  B[i+4]!=B[i] && B[i+4]!=(2*B[i])) 
	    {
	      if(B[i+7]==0)//if jump is available
		{
		  n.from = i;
		  n.to = i+7;
		  (B[i+4]==(t*B[i]))? n.value=B[i+4]: n.value=B[i+4]*3;
		  n.value *=-1;
		  n.capture=i+4;
		  movesList.push_back(n);

		}
	    }
	  
	  
	  //Check for Down and Right moves
	  if(i%8!=3)//exclude right side of Board
	    {    
	      if(B[i+5]==0)//move to empty space
		{
		  n.from = i;
		  n.to = i+5;
		  n.value=0;
		  movesList.push_back(n);
		}
	      else if( i<23 &&  B[i+5]!=B[i] && B[i+5]!=(2*B[i]))//check if occupied space is opponent's piece
		{
		  
		  if(B[i+9]==0)//if jump is available
		    {
		      n.from = i;
		      n.to = i+9;
		      (B[i+5]==(t*B[i]))? n.value=B[i+5]: n.value=B[i+5]*3;
		      n.value *=-1;
		      n.capture=i+5;
		      movesList.push_back(n);

		    }
		}
	    }
	}

 
  

}


void ply::getBmoves(const int B[32], vector<moves>& movesList, int i, bool max)
{
  moves n;
  int t;

  (B[i]==2)? t=1: t=-1;
  
  //Even row and not empty space
  if(i%8>=4 && B[i]!=0 && B[i]!=1 && i>3)
    {

      if(i%8!=4)
	{//Check for Up and Left moves
	  if(B[i-5]==0)//move to empty space
	    {
	      n.from = i;
	      n.to = i-5;
	      n.value=0;
	      movesList.push_back(n);
	    }
	  else if(i>=12 && B[i-5]!=B[i] && B[i-5]!=(2*B[i]))//check if occupied space is opponent's piece
	    {
	      if(B[i-9]==0)//if jump is available
		{
		  n.from = i;
		  n.to = i-9;
		  (B[i-5]==(t*B[i]))? n.value=B[i-5]: n.value=B[i-5]*3;
		  n.value *=-1;
		  n.capture=i-5;
		  movesList.push_back(n);

		}
	    }
	}
      
      //Check for Up and Right moves
      if(B[i-4]==0)//move to empty space
	{
	  n.from = i;
	  n.to = i-4;
	  n.value=0;
	  movesList.push_back(n);
	}
      else if((i>=12) && (i%8!=7) && B[i-4]!=B[i] && B[i-4]!=(2* B[i]))//check if occupied space is opponent's piece
	{

	  if(B[i-7]==0)//if jump is available
	    {
	      n.from = i;
	      n.to = i-7;
	      (B[i-4]==(t*B[i]))? n.value=B[i-4]: n.value=B[i-4]*3;
	      n.value *=-1;
	      n.capture=i-4;
	      movesList.push_back(n);

	    }
	}
    }
  
  //Odd Row and not empty space
  if(i%8<4 && B[i]!=0 && B[i]!=1 && i>3)
    {
      //Check for Up and Left moves
      if(B[i-4]==0)//move to empty space
	{
	  n.from = i;
	  n.to = i-4;
	  n.value=0;
	  movesList.push_back(n);
	}
      //If not left side of board and occupied space is opponents piece
      else if((i>=8)&& (i%8!=0) && B[i-4]!=B[i] && B[i-4]!=(2*B[i]))
	{
	  if(B[i-9]==0)//if jump is available
	    {
	      n.from = i;
	      n.to = i-9;
	      (B[i-4]==(t*B[i]))? n.value=B[i-4]: n.value=B[i-4]*3;
	      n.value *=-1;
	      n.capture=-4;
	      movesList.push_back(n);

	    }
	}
      
      
      //Check for Up and Right moves
      if(i%8!=3)//exclude right side of Board
	{
	  if(B[i-3]==0)//move to empty space
	    {
	      n.from = i;
	      n.to = i-3;
	      n.value=0;
	      movesList.push_back(n);
	    }
	  else if((i>=8) &&  B[i-3]!=B[i] && B[i-3]!=(2*B[i]))//check if occupied space is opponent's piece
	    {
	      
	      if(B[i-7]==0)//if jump is available
		{
		  n.from = i;
		  n.to = i-7;
		  (B[i-3]==(t*B[i]))? n.value=B[i-3]: n.value=B[i-3]*3;
		  n.value *=-1;
		  n.capture=i-3;
		  movesList.push_back(n);

		}
	    }
	}
    }
}







  //Purpose: Given a state of current board, generate all a vector containing all legal moves for the player
  //Parameters: Board object containing current piece positions
void ply::generateMoves(const int M[], vector<moves>& pMoves, bool max,bool& dbl)
{
  //int M[32];//copy of board
  int k=0;//size
  int temp=0;
  int trimIndex=0;
  dbl=false;


  //int Bd[8][8];
  
  //clear vector array
  pMoves.erase(pMoves.begin(),pMoves.end());

  int i=0;



      if(max)
	{
	  for(int i=0; i<32;i++)
	    {
	      if(M[i]>=1)
		{
		  getWmoves(M,pMoves,i,max);
		  if(M[i]==2)
		    getBmoves(M,pMoves,i,max);
		}
	    }
	}
      else
	{
	  for(int i=0;i<32;i++)
	    {
	      
	      if(M[i]<=-1)
		{
		  getBmoves(M,pMoves,i,max);
		      if(M[i]==-2)
			getWmoves(M,pMoves,i,max);
		}
	    }
	  
	}
      
  
      //Sort vector before finishing
      for(int i=0;i<pMoves.size();i++)
	{
	  for(int j=1; j<pMoves.size(); j++)
	    {
	      k=pMoves.size()-j;
	      temp=pMoves[k].value;
	      
	      
	      if(pMoves[k-1].value > temp)
		{
		  
		  pMoves[k].value=pMoves[k-1].value;
		  pMoves[k-1].value=temp;
		  temp=pMoves[k].from;
		  pMoves[k].from=pMoves[k-1].from;
		  pMoves[k-1].from=temp;
		  temp=pMoves[k].to;
		  pMoves[k].to=pMoves[k-1].to;
		  pMoves[k-1].to=temp;
		}
	    }
	}
    
      k=pMoves.size()-1;
      //if captures exist in pMoves, remove non-capture moves
      
      //      int i=0;

	  if(max && pMoves[k].value>0)
	    {
	      while(pMoves[k].value>0 && k>0)
		k--;

	      pMoves.erase(pMoves.begin(), pMoves.begin()+k+1);

	      i=pMoves.size()-1;
	      while(i>=0 && pMoves[i].value>0)
		{
		  dbl=doubleJump(M,pMoves,i,max);
		  i--;
		  if(dbl)
		    return;
		}
	    }
	  else if(!max && pMoves[0].value<0)
	    {
	      while(pMoves[k--].value>pMoves[0].value)
		pMoves.pop_back();

	      k=pMoves.size();
	      while(i<k && pMoves[i].value<0)
		{
		  dbl=doubleJump(M,pMoves,i,max);
		  i++;

		  if(dbl)
		    return;
		}
	    }




	  
}      
     
    
  

	




