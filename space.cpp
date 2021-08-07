/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: This file implements the space class routines for the game.
               -1 means that the position hasn't been determined.
               0  means that the position is invalid and doesn't physically exist.
               Any other number indicates the position of the space on the board.
*/

#include "space.h"
#include <vector>
#include <iostream>

Space::Space(bool empty, int position){
  this->empty = empty;
  this->position = position;
  
  //initialize adjacent space to -1 meaning not set
  adjacentSpace[UL] = -1;
  adjacentSpace[UR] = -1;
  adjacentSpace[L] = -1;
  adjacentSpace[R] = -1;
  adjacentSpace[LL] = -1;
  adjacentSpace[LR] = -1;
}

bool Space::getEmpty(){
  return this->empty;
}

void Space::setEmpty(bool e){
  this->empty = e;
}

std::map<Position, int>& Space::getAdjacentSpace(){
  return adjacentSpace;
}

int Space::getPosition(){
  return this->position;
}

void Space::setPosition(int position){
  //-1 means that it hasn't been set
  //Only update if position hasn't been set
  if(this->position == -1){
    this->position = position;
  }
}

void Space::setAdjacentSpace(int boardSize, int totalSpaces){
  std::vector<std::vector<int>> vec;
  int lower = 0;

  //separate spaces into rows to calculate UL, UR, LL, LR
  for(int i = boardSize; i > 0; i--){
    std::vector<int> row;  
    lower = totalSpaces - i;
    for(int j = totalSpaces; j > lower; j--){
      row.push_back(j);
    }//for - end
    totalSpaces -= i;
    vec.insert(vec.begin(), row);
  }//for - end
    
  //loop over all adjacent space to update adjacent space position
  //based on current position value
  for(Position pos : {UL, UR, L, R, LL, LR}){
    if(adjacentSpace[pos] == -1){
      int row = 0;
      for(int i = 0; i < vec.size(); i++){
        for(int j = 0; j < vec.at(i).size(); j++){
          if(vec.at(i).at(j) == this->position){
            row = i + 1;
            break;
          }
        }//for - end
      }//for - end

      switch (pos){
      case UL:
        adjacentSpace[pos] = this->position - row;
        break;
      case UR:
        adjacentSpace[pos] = (this->position - row) + 1;
        break;
      case L:
        adjacentSpace[pos] = this->position - 1;
        break;
      case R:
        adjacentSpace[pos] = this->position + 1;
        break;
      case LL:
        adjacentSpace[pos] = this->position + row;
        break;
      case LR:
        adjacentSpace[pos] = (this->position + row) + 1;
        break;
      default:
        adjacentSpace[pos] = 100;
        break;
      }
    }//if - end
  }//for - end 
}

void Space::removeSpace(Position pos){
  //0 means that the space is invalid
  if(adjacentSpace[pos] == -1){
    adjacentSpace[pos] = 0;
  }
}
