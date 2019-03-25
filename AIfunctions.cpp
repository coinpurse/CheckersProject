
#include "AIfunctions.h"
//game state is the src 
//generateMoves  is target 

AIfunctions :: AIfunctions(){};

AIfunctions :: ~AIfunctions(){};

string AIfunctions:: int_to_string(int value)
  {
    string res="";
    while (value>0)
    {
      res += char(value%10 + 48);
      value /= 10;
    }
    for (int i=0;i<res.length()/2;i++)
    {
      swap(res[i],res[res.length()-i-1]);
    }
    return res;
  }

int AIfunctions :: Alpha_Beta(int alpha, int beta, int depth,bool Maximizing_Player,int Node_Index,int values[])
{
  
  //Terminating condition
  //leaf node is reached 
  cout<<"Checking if depth is set to MAX_DEPTH :"<< depth <<endl;
  if (depth == MAX_DEPTH )/*if node is a leaf return it's value*/
  {
    return values[Node_Index];
    //return *parent.value->Node_Index;
  }
  
  cout<<"Check_Point_1"<<endl;
  if (Maximizing_Player)
  {
  int bestVal = -MAX_DEPTH;
    
     cout<<"Check_Point_2 begining Pruning"<<endl;
    //Recur for left and right child/leaf
    for (int i = 0; i < MAX_DEPTH ;i++ )
    {
      int val = Alpha_Beta(alpha,beta,depth+1,false,Node_Index+1,values);
      bestVal = max(bestVal,val);
      alpha  = max(alpha,bestVal);
      
      //Alpha Beta Pruning
        if (beta <= alpha)
          break;
    }
    cout<<"Check_Point_4 breaking out returning value "<<endl;
    return bestVal;
  }
  
  else
  {
   int bestVal = MAX_DEPTH; 
    
    //Recur for left and right leaf/child
    cout<<"Check_Point_5 going into pruning "<<endl;
      for (int j =0; j<MAX_DEPTH ;j++)
      {
        int val = Alpha_Beta(alpha,beta,depth+1,true,Node_Index+1,values);
        bestVal = min(bestVal,val);
        beta = min(beta, bestVal);
        
        //Alpha Beta Pruning
        if (beta <= alpha)
          break;
      }
    cout<<"Check_Point_6:breaking out returning value "<<endl;
    return bestVal;
  }
}
 


bool AIfunctions :: DLS(int src, int target,int limit)
{
  /*
  if (src == target){return true;}
  
  //if reached the maximum depth, stop reaching 
  //stop recursing 
  if(limit <= 0){return false;}
  
  //Recur for all the verticies adjacent to source vertex 
  for (auto *i = adj[src].from; i != adj[src].to; ++i)
  {
    if (DLS(*i,target,limit - 1)==true)
      return true;
  }
  */
  return true;
  
}

//Iterative_Deepening_DFS to search if target is reachablefrom v.
//it uses recursive DFSUtil().
bool AIfunctions:: Iterative_Deepening_DFS(int src, int target,int max_depth)
{
  /*
//bool IDDFS(src, target, max_depth)
int maxdepth = -MAX_DEPTH; 
  for(int limit = 0 ; limit <= maxdepth ; limit++)
  {//foreach adjacent i or src 
    if (DLS(src,target, limit) == true)   
      //if DLS (i, target,limit?1)
        //return true;
        return true;
   }
   */
  return false;
  
}



