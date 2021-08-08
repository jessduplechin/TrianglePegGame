/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: This file defines the space class for the game.
*/
#ifndef SPACE_H
#define SPACE_H

#include <map>
#include "move.h"

class Space {
 public:
  Space(bool empty = true, int position = -1);
  bool getEmpty();
  void setEmpty(bool e);
  std::map<Position, int>& getAdjacentSpace();
  void setAdjacentSpace(int boardSize, int totalSpaces);
  void removeSpace(Position pos);
  
 private:
  bool empty;

  //cannot be changed once set 
  std::map<Position, int> adjacentSpace;  
};

#endif
