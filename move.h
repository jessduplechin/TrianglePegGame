/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: This file defines all the classes and enums necessary 
               for the game.
 */

#ifndef MOVE_H
#define MOVE_H

//These defines the adjacent positions to the peg/space
//U is for upper, L is for lower
//R is for right, L is for left
enum Position { UL, UR, L, R, LL, LR };

class Move {
 public:
  Move(int origin = 0, int destination = 0);
  void setOrigin(int origin);
  void setDestination(int destination);

 private:
  int origin;
  int destination;
};

#endif
