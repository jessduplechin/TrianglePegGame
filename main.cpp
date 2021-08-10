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
  
  //default size
  int boardSize = 5;
  int startPegPos = 1;
  
  //Checking arguments for validity
  switch(argc){
  case 2:
    if(checkArguments(argv[1])){
      boardSize = std::stoi(argv[1]);
    }
    else{
      return -1;
    }
    break;
  case 3:
    {
      int totalSpaces = 0;
      for(int i = 1; i <= std::stoi(argv[1]); i++){
        totalSpaces += i;
      }
      if(checkArguments(argv[1]) && 
         checkArguments(argv[2]) && 
         std::stoi(argv[2]) <= totalSpaces){
        boardSize = std::stoi(argv[1]);
        startPegPos = std::stoi(argv[2]);
      }
      else{
        std::cout << "Error - Starting position exceeds size of board" << std::endl;
        return -1;
      }
    }
    break;
  default:
    if(argc > 3){
      std::cout << "Error - Too many arguments" << std::endl;
      return -1;
    }
    break;
  }
  
  //Creation
  std::cout << "Board size = " << boardSize << std::endl;
  std::cout << "Starting peg position = " << startPegPos << std::endl;
  std::cout << "Creating board..." << std::endl;
  
  Board *board = new Board(startPegPos, boardSize);
  board->createBoard();

  board->startSimulation();
  std::cout << board->displayBoard() << std::endl;
  board->resetBoard();
  std::cout << "----------------------------" << std::endl;
  board->startSimulation();
  std::cout << board->displayBoard() << std::endl;
  board->resetBoard();

  //TODO: ADD NEW FUNCTION TO DETERMINE WHICH SET OF MOVES IS THE BEST SOLUTION.
  //board->returnBestSolution();
  
  board->printInformation();
  
  //TODO: FIGURE OUT WHY THE SAME SOLUTIONS ARE BEING REPEATED..
  
  std::cout << "Exiting..." << std::endl;
}

bool checkArguments(const char *str){
  char *charPointer;
  int value = strtol(str, &charPointer, 10);
  bool result = false;

  //Make sure that the arguments fulfill all requirements  
  if(value > 0){
    result = true;
  }
  else{
    std::cout << "Error - Argument cannot be alphabetical, 0 or negative" << std::endl;
  }
  return result;
}
