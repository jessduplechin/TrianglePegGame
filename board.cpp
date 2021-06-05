/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: This file implements all of the board class routines 
               necessary for the game.
*/

#include "board.h"
#include <iostream>

Board::Board(int startingSpace, int boardSize){
  //default starting position of space is at 1  
  this->startingSpace = startingSpace;
  //minimum board size is 3
  this->boardSize = boardSize;
  this->totalSpaces = 0;
}

void Board::createBoard(){
  //Find totalSpaces by finding summation from 1 to boardSize
  for(int i = 1; i <= this->boardSize; i++){
    this->totalSpaces += i; 
  }

  int leftSide = 1;
  int leftIncrement = 1;
  int rightSide = 1;
  int rightIncrement = 2;  
  
  //Create all the spaces for the board
  for(int i = 1; i <= this->totalSpaces; i++){
    Space *space = new Space(true, i);
    if(leftSide == i){
      leftSide += leftIncrement;
      leftIncrement++;
      space->removeSpace(L);
      space->removeSpace(UL);
    }
    if(rightSide == i){
      rightSide += rightIncrement;
      rightIncrement++;
      space->removeSpace(R);
      space->removeSpace(UR);
    }
    if((i <= this->totalSpaces) &&
       (i > this->totalSpaces - this->boardSize)){
      //bottom side
      space->removeSpace(LL);
      space->removeSpace(LR);
    }
    space->setAdjacentSpace(this->boardSize, this->totalSpaces);
    spaces.push_back(space);
  }//for - end
}

int Board::findSpaces(){
  return 0;
}

int Board::checkAdjacent(){
  return 0;
}

void Board::createPegs(){
  for(std::vector<Space*>::iterator i = spaces.begin();
      i != spaces.end(); i++){
    if(((*i)->getEmpty()) && ((*i)->getPosition() != this->startingSpace)){
      Peg *peg = new Peg((*i)->getPosition());
      peg->setAdjacentPegs((*i)->getAdjacentSpace());
      pegs.push_back(peg);
    }
  }//for - end
}

void Board::recordMoves(){

}

void Board::displayBoard(){
  int rowLength = 1;
  for(int i = 0; i < boardSize; i++){
    //    if(rowLength
    std::cout << "[]" << std::endl;
  }
}

void Board::displayPegs(){

}
