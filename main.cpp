/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: The entry point for finding all of the solutions for the 
               triangular board game.
  Usage: ./pegGame <boardSize> <startingPegPos>
*/

#include "board.h"
#include <iostream>

bool checkArguments(const char *str);

int main(int argc, char *argv[]){
  char *charPointer;
  int boardSize = 5;
  int startPegPos = 1;
  
  //Checking arguments for validity
  if(argc == 2){
    if(checkArguments(argv[1])){
      boardSize = std::stoi(argv[1]);
    }
    else{
      return -1;
    }
  }
  else if(argc == 3){
    if(checkArguments(argv[1]) && checkArguments(argv[2])){
      boardSize = std::stoi(argv[1]);
      startPegPos = std::stoi(argv[2]);
    }
    else{
      return -1;
    }
  }
  else if(argc > 3){
    std::cout << "Error - Too many arguments" << std::endl;
    return -1;
  }

  std::cout << "Board size = " << boardSize << std::endl;
  std::cout << "Starting peg position = " << startPegPos << std::endl;
  std::cout << "Creating board..." << std::endl;
  
  Board *board = new Board(startPegPos, boardSize);
  board->createBoard();
  
  std::cout << "Creating pegs..." << std::endl;
  board->createPegs();

  board->printInformation();
  
  //TODO: start algorithm to find empty spaces and move pieces around
  std::cout << "Exiting..." << std::endl;
}

bool checkArguments(const char *str){
  char *charPointer;
  int value = strtol(str, &charPointer, 10);
  bool result = false;

  //Make sure that the arguments fulfill all requirements
  //TODO: ADD CHECK TO MAKE SURE THAT STARTING SPACE POSITION IS SMALLER
  //      THAN TOTAL NUMBER OF SPACES
  if(value > 0){
    result = true;
  }
  else{
    std::cout << "Error - Argument cannot be alphabetical, 0 or negative" << std::endl;
  }
  return result;
}
