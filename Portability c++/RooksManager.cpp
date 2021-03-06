/*
 * RooksManager class implementation
 *
 * Copyright (c) 2018 Davide Molinelli.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Manager.h"
#include "Managers.h"
#include "Pieces.h"
#include "Config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Constructor
RooksManager::RooksManager(): Manager() {
  rooks[WHITE][0] = Rook::Rook("A1");
  rooks[WHITE][1] = Rook::Rook("H1");
  rooks[BLACK][0] = Rook::Rook("A8");
  rooks[BLACK][1] = Rook::Rook("H8");
};

// checkCandidates implementation
char * RooksManager::checkCandidates(Cell * cbState[][8], bool turn, const char * from, const char * destination){
  char * candidate;
  // 'A' corresponds to 65 - 65 = 0, 'B' to 66 - 65 = 1, 'C' to 67 - 65 = 2, etc.
  int row = destination[0] - 65;
  // '1' corresponds to 49 - 49 = 0, '2' to 50 - 49 = 1, etc.
  int col = destination[1] - 49;
  int vDiff;
  int hDiff;

  // row or column out of chessboard limits
  if(row < 0 || col < 0 || row > 7 || col > 7){
      return NULL;
  }

  // it is legal to look for candidates only if the destination cell is not already occupied by a piece of the same color
  if((turn && cbState[row][col]->getColor() != 'B') || (!turn && cbState[row][col]->getColor() != 'W')){
    // auxiliary variables
    int numCandidates = 0;
    int indexCandidate;

    // control the position of any rook of the player in order to find a possible candidate
    for(int i = 0; i < 2; i++){
      // consider the parameters from and destination as points (from = (xf,yf), destination = (xd,yd))
      if(from == NULL){     // ordinary cases without ambiguity --> from = NULL
        // calculate the vertical difference yd - yf
        vDiff = destination[1] - rooks[turn][i].getPosition()[1];
        // calculate the horizontal difference xd - xf
        hDiff = destination[0] - rooks[turn][i].getPosition()[0];
      } else{               // ambiguous cases --> from ≠ NULL
        // control if actually a rook of the player occupy the position expressed by the variable from
        if(checkSource(cbState, turn, from, 'R')){
          return NULL;
        }
        // calculate the vertical difference yd - yf
        vDiff = destination[1] - from[1];
        // calculate the horizontal difference xd - xf
        hDiff = destination[0] - from[0];
      }
      // check the queen is alive
      if(rooks[turn][i].getAlive()){
        // vertical or horizontal move
        if((hDiff == 0 && abs(vDiff) > 0) || (abs(hDiff) > 0 && vDiff == 0)){
          // check path is licit
          if(checkPathIsFree(cbState, vDiff, hDiff, row, col)){
            if(from == NULL){
              numCandidates++;
              indexCandidate = i;
            } else{
              if(cbState[row][col]->getBusy()){
                // set a memo to remember that the opponent piece in the destination cell must be removed
                cbState[row][col]->setColor('D');
              }

              setNewPosition(turn, from, destination);
              candidate = new char[3];
              for(int i = 0; i<strlen(from);i++){
                  candidate[i] = from[i];
              }
              return candidate;
            }
          }
        }
      }
    }
    // in case from = NULL verify that the search of candidates return only one candidate
    if(numCandidates == 1){
      if(cbState[row][col]->getBusy()){
        // set a memo to remember that the opponent piece in the destination cell must be removed
        cbState[row][col]->setColor('D');
      }
      candidate = rooks[turn][indexCandidate].getPosition();
      rooks[turn][indexCandidate].setPosition(destination);
      return candidate;
    }
  }
  // move not valid
  return NULL;
};

// checkPathIsFree implementation
bool RooksManager::checkPathIsFree(Cell * cbState[][8], int vDiff, int hDiff, int row, int col){
  // consider the parameters from and destination as points ( from = (xf,yf), destination = (xd,yd))

  if(abs(vDiff) > 0 && hDiff == 0){           // vertical movement
    for(int i = 1; i < abs(vDiff); i++){
      if(vDiff > 0){
        // cell busy
        if(cbState[row][col + i]->getBusy()){
          return false;
        }
      } else {
        // cell busy
        if(cbState[row][col - i]->getBusy()){
          return false;
        }
      }
    }
  } else if(vDiff == 0 && abs(hDiff) > 0){    //horizontal movement
    for(int i = 1; i < abs(hDiff); i++){
      if(hDiff > 0){
        // cell busy
        if(cbState[row + i][col]->getBusy()){
          return false;
        }
      } else {
        // cell busy
        if(cbState[row - i][col]->getBusy()){
          return false;
        }
      }
    }
  }
  // all constraints, overcome
  return true;
};

void RooksManager::toString(){
  //Serial.println("--- Rooks ---");
  //Serial.println();
  printf("\n\n--- Rooks ---\n\n");

  for(int i = 0; i < 2; i ++){
    if(i == 0){
      printf("White: \n");
      //Serial.println("Black: ");
      //Serial.println();
    } else{
      printf("\nBlack: \n");
      //Serial.println("White: ");
      //Serial.println();
    }

    for(int j = 0; j < 2; j ++){
      rooks[i][j].toString();
    }
  }
}

void RooksManager::setNewPosition(bool turn, const char * from, const char * destination){
  for(int i = 0; i < 2; i++){
    if(strcmp(rooks[turn][i].getPosition(),from) == 0){
      rooks[turn][i].setPosition(destination);
    }
  }
};

void RooksManager::findAndRemove(bool turn, const char * destination){
  for(int i = 0; i < 2; i++){
    if(strcmp(rooks[turn][i].getPosition(),destination) == 0){
      rooks[turn][i].setAlive();
      rooks[turn][i].setPosition("Z9");

      return;
    }
  }
};
