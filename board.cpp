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
  //TODO: FIGURE OUT ALGORITHM HERE
  return 0;
}

int Board::checkAdjacent(){

  //TODO: MOVE THIS SOMEWHERE ELSE. THIS IS TEMPORARY TO DEMO 
  // THE resetBoard FUNCTION.
  //reset pegs
  std::cout << "jumping peg from pos 4 to pos 1" << std::endl;
  updatePegs(pegs.begin(), pegs.begin() + 2, 1);
  //update spaces  
  updateSpaces(4, 2, 1);

  return 0;
}

void Board::createPegs(){
  for(std::vector<Space*>::iterator i = spaces.begin();
      i != spaces.end(); i++){
    if(((*i)->getEmpty()) && ((*i)->getPosition() != this->startingSpace)){
      Peg *peg = new Peg((*i)->getPosition());
      peg->setAdjacentPegs((*i)->getAdjacentSpace());
      pegs.push_back(peg);
      //set space as not empty now
      (*i)->setEmpty(false);
    }
  }//for - end
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
      if(!spaces.at(k)->getEmpty()){
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
  for(std::vector<Space*>::iterator i = spaces.begin();
      i != spaces.end(); i++){
    output.append("Space Position: " + std::to_string((*i)->getPosition())
                  + "\n");
    output.append("Space Empty: " + std::to_string((*i)->getEmpty()) + "\n");
    output.append("Space Adjacent UL: " +
                  std::to_string((*i)->getAdjacentSpace()[UL]) + "\n");
    output.append("Space Adjacent UR: " +
                  std::to_string((*i)->getAdjacentSpace()[UR]) + "\n");
    output.append("Space Adjacent L: " +
                  std::to_string((*i)->getAdjacentSpace()[L]) + "\n");
    output.append("Space Adjacent R: " +
                  std::to_string((*i)->getAdjacentSpace()[R]) + "\n");
    output.append("Space Adjacent LL: " +
                  std::to_string((*i)->getAdjacentSpace()[LL]) + "\n");
    output.append("Space Adjacent LR: " +
                  std::to_string((*i)->getAdjacentSpace()[LR]) + "\n");
    output.append("\n");
  }//for - end
    
  return output;
}

std::string Board::displayPegs(){
  std::string output;
  for(std::vector<Peg*>::iterator i = pegs.begin();
      i != pegs.end(); i++){
    output.append("Peg Position: " + std::to_string((*i)->getPegPos())
                  + "\n");
    output.append("Peg Adjacent UL: " +
                  std::to_string((*i)->getAdjacentPegs()[UL]) + "\n");
    output.append("Peg Adjacent UR: " +
                  std::to_string((*i)->getAdjacentPegs()[UR]) + "\n");
    output.append("Peg Adjacent L: " +
                  std::to_string((*i)->getAdjacentPegs()[L]) + "\n");
    output.append("Peg Adjacent R: " +
                  std::to_string((*i)->getAdjacentPegs()[R]) + "\n");
    output.append("Peg Adjacent LL: " +
                  std::to_string((*i)->getAdjacentPegs()[LL]) + "\n");
    output.append("Peg Adjacent LR: " +
                  std::to_string((*i)->getAdjacentPegs()[LR]) + "\n");
    output.append("\n");
  }//for - end
  
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
    outFile << displayPegs();
    //TODO: ADD OTHER THINGS TO DISPLAY; MOVES, SOLUTIONS
    
    outFile.close();
  }
  else{
    std::cout << "Error - Couldn't open file" << std::endl;
  }
}

void Board::resetBoard(){
  //reset spaces vector to original state
  for(std::vector<Space*>::iterator i = spaces.begin();
      i != spaces.end(); i++){
    (*i)->setEmpty(true);
  }//for - end
  
  //Remove all pegs and create new ones
  pegs.clear();
  createPegs();
}

void Board::updateSpaces(int origin, int between, int destination){
  for(std::vector<Space*>::iterator i = spaces.begin();
      i != spaces.end(); i++){
	if((*i)->getPosition() == origin ||
	   (*i)->getPosition() == between){
      (*i)->setEmpty(true);
	}
	else if((*i)->getPosition() == destination){
	  (*i)->setEmpty(false);
	}
  }//for - end
}

void Board::updatePegs(Peg *remove, Peg *moved, int destination){
  moved->setPegPos(destination);
  pegs.erase(removed);
  
  for(std::vector<Space*>::iterator i = spaces.begin();
      i != spaces.end(); i++){
    if(moved->getPegPos() == (*i)->getPosition()){
      moved->setAdjacentPegs((*i)->getAdjacentSpace());
	  break;
	}
  }//for - end
}





