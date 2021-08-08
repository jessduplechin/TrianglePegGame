/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: This file implements all of the board class routines 
               necessary for the game.
*/

#include "board.h"
#include <iostream>
#include <fstream>

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
    Space *space;
    if(i != this->startingSpace){
      space = new Space(false, i);
    }
    else{
      space = new Space(true, i);
    }
    
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
    //spaces.push_back(space);
    spaces[i] = space;
  }//for - end
}

int Board::findSpaces(){
  //TODO: FIGURE OUT ALGORITHM HERE
  return 0;
}

int Board::checkAdjacent(){

  //TODO: MOVE THIS SOMEWHERE ELSE. THIS IS TEMPORARY TO DEMO 
  // THE resetBoard FUNCTION.
  /*std::cout << "jumping peg from pos 4 to pos 1" << std::endl;
  updateSpaces(4, 4, 1);
  updateSpaces(4, 1, 4);
  updateSpaces(1, 4, 4);
  updateSpaces(4, 4, 4);
  //update spaces  
  updateSpaces(4, 2, 1);
  updateSpaces(9, 5, 2);
*/
  //add test moves to moves array
	moves.push_back(new Move(3, 4));
	moves.push_back(new Move(10, 2));
	moves.push_back(new Move(7, 6));
  return 0;
}

void Board::recordMoves(){
  //TODO: FILL IN 
}

std::string Board::displayBoard(){
  int k = 0;
  std::string output;

  //TODO: ADD WAY TO PRINT OUT SPACE POSITION TOO
  for(int i = 1; i <= this->boardSize; i++){
    //Add spaces for alignment
    for(int j = 0; j < (this->boardSize - i); j++){
      output.append("   ");
    }
    //Show peg placement using spaces vector
    for(int j = 0; j < i; j++){   
      if(!spaces[k + 1]->getEmpty()){
        output.append("[*]   ");
      }
      else{
        output.append("[ ]   ");
        }
      k++;
    }
    output.append("\n");
  }//for(i..) - end

  return output;
}

std::string Board::displaySpaces(){
  std::string output;
  for(int i = 1; i <= this->totalSpaces; i++){
    output.append("Space Position: " + std::to_string(i) + "\n");
    output.append("Space Empty: " + std::to_string(spaces[i]->getEmpty()) + "\n");
    output.append("Space Adjacent UL: " +
                  std::to_string(spaces[i]->getAdjacentSpace()[UL]) + "\n");
    output.append("Space Adjacent UR: " +
                  std::to_string(spaces[i]->getAdjacentSpace()[UR]) + "\n");
    output.append("Space Adjacent L: " +
                  std::to_string(spaces[i]->getAdjacentSpace()[L]) + "\n");
    output.append("Space Adjacent R: " +
                  std::to_string(spaces[i]->getAdjacentSpace()[R]) + "\n");
    output.append("Space Adjacent LL: " +
                  std::to_string(spaces[i]->getAdjacentSpace()[LL]) + "\n");
    output.append("Space Adjacent LR: " +
                  std::to_string(spaces[i]->getAdjacentSpace()[LR]) + "\n");
    output.append("\n");
  }//for - end
    
  return output;
}

std::string Board::displayMoves(){
  std::string output;
  
  for(std::vector<Move*>::iterator i = moves.begin(); 
      i != moves.end(); i++){
	  output.append(std::to_string((*i)->getOrigin()) + " -> " +
	                std::to_string((*i)->getDestination() + "\n"));
  }
  
  return output;
}

void Board::printInformation(){
  //Print everything onto text files
  std::ofstream outFile("information.txt");

  if(outFile.is_open()){
    outFile << displayBoard();
    outFile << "----------------------------------------\n";
    outFile << displaySpaces();
    outFile << "----------------------------------------\n";
    //TODO: ADD OTHER THINGS TO DISPLAY; MOVES, SOLUTIONS
    
    outFile.close();
  }
  else{
    std::cout << "Error - Couldn't open file" << std::endl;
  }
}

void Board::resetBoard(){
  //reset spaces vector to original state
  for(int i = 1; i <= this->totalSpaces; i++){ 
    if(i != this->startingSpace){
      spaces[i]->setEmpty(false);
    }
    else{
      spaces[i]->setEmpty(true);
    }
  }//for - end
}

void Board::updateSpaces(int origin, int between, int destination){
  if(origin == between || origin == destination || between == destination){
    std::cout << "Error - origin, between, or destination are same values" << std::endl;
    return;
  }
  
  spaces[origin]->setEmpty(true);
  spaces[between]->setEmpty(true);
  spaces[destination]->setEmpty(false);
}

