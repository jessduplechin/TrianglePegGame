/*
  Name: Jessica Duplechin
  Date: 08/10/2021
  Description: This file declares the Solution class for the game.
 */
 
#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "move.h"
 
class Solution {
 public: 
  Solution(std::vector<Move*>, int numPegs);
  int getPegs();
  std::vector<Move*> getMoves();

 private:
  std::vector<Move*> moves;
  int remainingPegs;
};
  
#endif 
