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
    spaces[i] = space;
  }//for - end
}

std::vector<int> Board::findSpaces(){  
  std::vector<int> emptySpaces;

  for(int i = 1; i <= this->totalSpaces; i++){
    if(spaces[i]->getEmpty()){
      emptySpaces.push_back(i);
    }
  }
  return emptySpaces;
}

std::vector<int> Board::checkAdjacent(Space *space){
  std::vector<int> temp;
  
  //Get all valid adjacent spaces that are not empty
  for(Position pos : {UL, UR, L, R, LL, LR}){  
    if(space->getAdjacentSpace()[pos] != 0 &&
	   !spaces[space->getAdjacentSpace()[pos]]->getEmpty()){
	  temp.push_back(space->getAdjacentSpace()[pos]);
    }
  }
  return temp;
}

void Board::recordMoves(){
  int remainingPegs = 0;
  
  //Add up all remaining number of pegs on board
  for(int i = 1; i <= this->totalSpaces; i++){
	  if(!spaces[i]->getEmpty()){
		  remainingPegs++;
	  }
  }
  
  solutions.push_back(new Solution(moves, remainingPegs));
}

std::string Board::displayBoard(){
  int k = 1;
  std::string output;

  //TODO: ADD WAY TO PRINT OUT SPACE POSITION TOO
  for(int i = 1; i <= this->boardSize; i++){
    //Add spaces for alignment
    for(int j = 0; j < (this->boardSize - i); j++){
      output.append("   ");
    }
    //Show peg placement using spaces vector
    for(int j = 0; j < i; j++){   
      if(!spaces[k]->getEmpty()){
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

std::string Board::displayMoves(std::vector<Move*> m){
  std::string output;

  if(!m.empty()){
    for(std::vector<Move*>::iterator i = m.begin(); 
        i != m.end(); i++){
      output.append(std::to_string((*i)->getOrigin()) + " -> " +
                    std::to_string((*i)->getDestination()) + "\n");
    }
  }
  else{
    std::cout << "Error - Moves vector is empty" << std::endl;
  }
  return output;
}

std::string Board::displaySolutions(){
  std::string output;
  
  for(int i = 0; i < solutions.size(); i++){
    output.append("Solution: " + std::to_string(i + 1) + "\n");
    output.append("Number of Pegs remaining: " +
                  std::to_string(solutions.at(i)->getPegs()) + "\n");
    output.append("Moves:\n");
    output.append(displayMoves(solutions.at(i)->getMoves()));
    output.append("==========================================\n");
  }
  return output;
}

void Board::printInformation(){
  //Print everything onto text files
  std::ofstream boardFile("board.txt");
  std::ofstream solutionFile("solutions.txt");
  
  if(boardFile.is_open() && solutionFile.is_open()){
    boardFile << displayBoard();
    boardFile << "----------------------------------------\n";
    boardFile << displaySpaces();
    boardFile << "----------------------------------------\n";
    
    solutionFile << displaySolutions();
    
    boardFile.close();
    solutionFile.close();
  }
  else{
    std::cout << "Error - Couldn't open files" << std::endl;
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
  
  //delete everything in moves vector
  moves.clear();
}

void Board::updateSpaces(int origin, int between, int destination){
  if(origin == between ||
     origin == destination ||
     between == destination){
    std::cout << "Error - origin, between, or destination are same values" << std::endl;
    return;
  }
  
  spaces[origin]->setEmpty(true);
  spaces[between]->setEmpty(true);
  spaces[destination]->setEmpty(false);
}

Position Board::getSpaceCorrelation(int orig, int dest){
  Position correlation;
  
  for(Position pos : {UL, UR, L, R, LL, LR}){
    if(spaces[orig]->getAdjacentSpace()[pos] == dest){
      correlation = pos;
      break;
    }
  }
  return correlation;
}

void Board::startSimulation(){
  int origPos;
  int betweenPos;
  int destPos;
  bool possibleMoves = true;
  std::vector<int> emptySpaces;

  srand(time(0));
      
  while(possibleMoves){
	  bool repeat = false;
	  emptySpaces = findSpaces();
	  
	  for(int i = 0; i < emptySpaces.size(); i++){
		Space *firstSpace;
		Space *adjacentSpace;
		std::vector<int> validAdjacentPos;
		Position position;
		int randomIndex;
			  
		destPos = emptySpaces.at(i);
		firstSpace = spaces[destPos];		
			
		//Get all valid adjacent spaces that are not empty   
		validAdjacentPos = checkAdjacent(firstSpace);
		
		//Loop until a valid, non-empty adjacent space is found
		while(validAdjacentPos.size() > 0){

		  //Get an adjacent space chosen at random
		  randomIndex = rand() % validAdjacentPos.size();
		  betweenPos = validAdjacentPos.at(randomIndex);
		  adjacentSpace = spaces[betweenPos];      

		  position = getSpaceCorrelation(destPos, betweenPos);

		  //Get valid secondary adjacent space using same position
		  //as first adjacent space
		  origPos = adjacentSpace->getAdjacentSpace()[position];
		  if(origPos != 0){
			if(!spaces[origPos]->getEmpty()){
			  //Move peg to new destination
			  updateSpaces(origPos, betweenPos, destPos);
			  
			  //Record the move and go to next empty space
			  moves.push_back(new Move(origPos, destPos));
			  repeat |= true;
			  break;
			}
			else{
			  //Remove from vector and try a different adjacent space
			  validAdjacentPos.erase(validAdjacentPos.begin() + randomIndex);
			  repeat |= false;
			}
		  }
		  else{
			//Remove from vector and try a different adjacent space
			validAdjacentPos.erase(validAdjacentPos.begin() + randomIndex);
			repeat |= false;
		  }

		}//while - end
	  }//for - end
	  
	  //Update
      possibleMoves = repeat;	  	  
  }//while(possibleMoves) - end
  
  recordMoves();
}
