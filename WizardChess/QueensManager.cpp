/*
 * QueensManager class implementation
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

// Constructor
QueensManager::QueensManager(): Manager() {
  queens[WHITE_QUEEN][0] = Queen("D1");
  queens[BLACK_QUEEN][0] = Queen("D8");
};

// checkCandidates implementation
char * QueensManager::checkCandidates(Cell * cbState[][8], bool turn, const char * from, const char * destination){
  /// auxiliary variables
  // 'A' corresponds to 65 - 65 = 0, 'B' to 66 - 65 = 1, 'C' to 67 - 65 = 2, etc.
  int row = destination[0] - 65;
  // '1' corresponds to 49 - 49 = 0, '2' to 50 - 49 = 1, etc.
  int col = destination[1] - 49;

  // consider the parameters from and destination as points (from = (xf,yf), destination = (xd,yd))
  if(from == NULL){     // ordinary cases without ambiguity --> from = NULL
    // calculate the vertical difference yd - yf
    vDiff = destination[1] - queens[turn][0].getPosition()[1];
    // calculate the horizontal difference xd - xf
    hDiff = destination[0] - queens[turn][0].getPosition()[0];
  } else{               // ambiguous cases --> from ≠ NULL
    // control if actually a queen of the player occupy the position expressed by the variable from
    if(checkSource(cbState, turn, from, 'Q')){
      return NULL;
    }
    // calculate the vertical difference yd - yf
    vDiff = destination[1] - from[1];
    // calculate the horizontal difference xd - xf
    hDiff = destination[0] - from[0];
  }

  // it is legal to look for candidates only if the destination cell is not already occupied by a piece of the same color
  if((turn && cbState[row][col].getColor() != 'B') || (!turn && cbState[row][col].getColor() != 'W')){
    // the queen is unique for any player so the case from = NULL and from ≠ NULL is manageable
    // in a single case (considering from = NULL in any case)

    // check the queen is alive
    if(queens[turn][0].getAlive()){
      // check if path is licit
      if(checkPathIsFree(cbState, vDiff, hDiff, row, col)){
        if(cbState[row][col].getBusy()){
          // set a memo to remember that the opponent piece in the destination cell must be removed
          cbState[row][col].setColor('D');
        }
        strcpy(candidate, queens[turn][indexCandidate]);
        queens[turn][indexCandidate].setPosition(destination);
        return candidate;
      }
    }
  }
  // move not valid
  return NULL;
};

virtual bool QueensManager::checkPathIsFree(Cell * cbState[][8], int vDiff, int hDiff, int row, int col){
  // horizontal or vertical movement
  if(abs(vDiff) != abs(hDiff)){
    if(abs(vDiff) > 0 && hDiff == 0){           // vertical movement
      for(int i = 1; i < abs(vDiff); i++){
        if(vDiff > 0){
          // cell busy
          if(cbState[row][col + i].getBusy()){
            return false;
          }
        } else {
          // cell busy
          if(cbState[row][col - i].getBusy()){
            return false;
          }
        }
      }
    } else if(vDiff == 0 && abs(hDiff) > 0){    //horizontal movement
      for(int i = 1; i < abs(hDiff); i++){
        if(hDiff > 0){
          // cell busy
          if(cbState[row + i][col].getBusy()){
            return false;
          }
        } else {
          // cell busy
          if(cbState[row - i][col].getBusy()){
            return false;
          }
        }
      }
    }
  } else {    // diagonal movement
    // move along the diagonal to search for busy cells (remember that abs(vDiff) == abs(hDiff))
    for(int i = 1; i < abs(vDiff); i++){
      if(vDiff > 0 && hDiff > 0){         // up - right real chessboard (from white player point of view)
        // cell busy
        if(cbState[row + i][col + i].getBusy()){
          return false;
        }
      } else if(vDiff > 0 && hDiff < 0){  // up - left real chessboard (from white player point of view)
        // cell busy
        if(cbState[row + i][col - i].getBusy()){
          return false;
        }
      } else if(vDiff < 0 && hDiff > 0){  // down - right real chessboard (from white player point of view)
        // cell busy
        if(cbState[row - i][col + i].getBusy()){
          return false;
        }
      } else if(vDiff < 0 && hDiff < 0){  // down - left real chessboard (from white player point of view)
        // cell busy
        if(cbState[row - i][col - i].getBusy()){
          return false;
        }
      }
    }
  }
  // all constraints, overcome
  return true;
};

void QueensManager::toString(){
  Serial.println("--- Queen ---");
  Serial.println();

  for(int i = 0; i < 2; i ++){
    if(i == 0){
      Serial.println("Black: ");
      Serial.println();
    } else{
      Serial.println("White: ");
      Serial.println();
    }
    
    Serial.println(bishops[i][j].toString());
  }
}

void QueensManager::setNewPosition(bool turn, const char * from, const char * destination){
};

void QueensManager::findAndRemove(bool turn, const char * destination){
  if(strcmp(queens[turn][0].getPosition(),destination){
      queens[turn][0].setAlive();
      queens[turn][0].setPosition("Z9");
  }
};