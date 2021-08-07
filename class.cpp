/*
  Name: Jessica Duplechin
  Date: 05/08/2021
  Description: This file implements Peg and Move class for the game.
 */

#include "class.h"

Peg::Peg(int position){
  this->position = position;
}

void Peg::jump(int pos){
  this->position = pos;
  //TODO: REMOVE PEG THAT IT JUMPED OVER
}

int Peg::getPegPos(){
  return position;
}

void Peg::setPegPos(int position){
  this->position = position;
}

std::map<Position, int>& Peg::getAdjacentPegs(){
  return adjacentPegs;
}

void Peg::setAdjacentPegs(std::map<Position, int>& pegs){
  adjacentPegs = pegs;
}

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
