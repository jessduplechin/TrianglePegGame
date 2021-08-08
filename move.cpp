/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: This file implements Move class for the game.
 */

#include "move.h"

Move::Move(int origin, int destination){
  this->origin = origin;
  this->destination = destination;
}

void Move::setOrigin(int origin){
  this->origin = origin;
}

void Move::setDestination(int destination){
  this->destination = destination;
}
