/*
  Name: Jessica Duplechin
  Date: 08/10/2021
  Description: This file declares the Solution class for the game.
 */
 
Solution::Solution(std::vector<Move*> moves, int numPegs){
  this->remainingPegs = numPegs;
  this->moves = moves;
}

int Solution::getPegs(){
  return this->remainingPegs;
}
   
std::vector<Move*> Solution::getMoves(){
  return this->moves;
}