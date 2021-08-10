/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: This file declares the board class for the game.
  Notes: Positions start at 1 on the board and go from left to right,
         top to bottom sequentially. So board of size 3 has positions from
         1 to 6.
         One peg can occupy a space at a time.
*/

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "move.h"
#include "space.h"
#include "solution.h"
#include <string>

class Board {
 public:
  Board(int startingSpace = 1, int boardSize = 3);
  void createBoard();
  std::vector<int> findSpaces();
  std::vector<int> checkAdjacent(Space *space);
  void recordMoves();
  std::string displayBoard();
  std::string displaySpaces();
  std::string displayMoves(std::vector<Move*> m);
  std::string displaySolutions();
  void printInformation();
  void resetBoard();
  void updateSpaces(int origin, int between, int destination);
  Position getSpaceCorrelation(int orig, int dest);
  void startSimulation();

 private:
  int boardSize;
  int startingSpace;
  int totalSpaces;  
  std::vector<Move*> moves;
  std::map<int, Space*> spaces;
  std::vector<Solution*> solutions;
};

#endif 
