/*
 * ChessBoard class implementation
 *
 * Copyright (c) 2018 Davide Molinelli.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the   hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ChessBoard.h"
#include "Config.h"

// Constructor
ChessBoard::ChessBoard() {
    // Turn controller inizialization (start the white player - WHITE --> 0)
    turn = false;
    solenoid = "A1";

    /*for(int i = 0; i < 8; i++){
        for(int j = 0; i < 8; i++){
            if(j == 0 || j == 1){
              if(j == 0){
                cbState[i][j] = new Cell(true,'W', 'P');    // cell busy by white pawns
              } else {
                if(i == 0 || i == 7){
                  cbState[i][j] = new Cell(true,'W', 'R');  // cell busy by white rooks
                } else if(i == 1 || i == 6){
                  cbState[i][j] = new Cell(true,'W', 'B');  // cell busy by white bishops
                } else if(i == 2 || i == 5){
                  cbState[i][j] = new Cell(true,'W', 'H');  // cell busy by white knights
                } else if(i == 3){
                  cbState[i][j] = new Cell(true,'W', 'Q');  // cell busy by white queen
                } else if(i == 4){
                  cbState[i][j] = new Cell(true,'W', 'K');  // cell busy by white king
                }
              }
            } else if(j == 7 || j == 8){
              if(j == 7){
                cbState[i][j] = new Cell(true,'B', 'P');    // cell busy by black pawns
              } else {
                if(i == 0 || i == 7){
                  cbState[i][j] = new Cell(true,'B', 'R');  // cell busy by black rooks
                } else if(i == 1 || i == 6){
                  cbState[i][j] = new Cell(true,'B', 'B');  // cell busy by black bishops
                } else if(i == 2 || i == 5){
                  cbState[i][j] = new Cell(true,'B', 'H');  // cell busy by black knights
                } else if(i == 3){
                  cbState[i][j] = new Cell(true,'B', 'Q');  // cell busy by black queen
                } else if(i == 4){
                  cbState[i][j] = new Cell(true,'B', 'K');  // cell busy by black king
                }
              } 
            } else{
                cbState[i][j] = new Cell(false,'E','E');    // empty cbState 
            }
            delay(1000);
            //Serial.println("init");
        }
    }*/

    
    /*cbState[0][0] = new Cell(true,'W', 'P');
    cbState[0][1] = new Cell(true,'W', 'P');
    cbState[0][2] = new Cell(true,'W', 'P');
    cbState[0][3] = new Cell(true,'W', 'P');
    cbState[0][4] = new Cell(true,'W', 'P');
    cbState[0][5] = new Cell(true,'W', 'P');
    cbState[0][6] = new Cell(true,'W', 'P');
    cbState[0][7] = new Cell(true,'W', 'P');
    cbState[1][0] = new Cell(true,'W', 'R');
    cbState[1][1] = new Cell(true,'W', 'B');
    cbState[1][2] = new Cell(true,'W', 'H');
    cbState[1][3] = new Cell(true,'W', 'Q');
    cbState[1][4] = new Cell(true,'W', 'K');
    cbState[1][5] = new Cell(true,'W', 'H');
    cbState[1][6] = new Cell(true,'W', 'B');
    cbState[1][7] = new Cell(true,'W', 'R');
    cbState[2][0] = new Cell(false,'E', 'E');
    cbState[2][1] = new Cell(false,'E', 'E');
    cbState[2][2] = new Cell(false,'E', 'E');
    cbState[2][3] = new Cell(false,'E', 'E');
    cbState[2][4] = new Cell(false,'E', 'E');
    cbState[2][5] = new Cell(false,'E', 'E');
    cbState[2][6] = new Cell(false,'E', 'E');
    cbState[2][7] = new Cell(false,'E', 'E');
    cbState[3][0] = new Cell(false,'E', 'E');
    cbState[3][1] = new Cell(false,'E', 'E');
    cbState[3][2] = new Cell(false,'E', 'E');
    cbState[3][3] = new Cell(false,'E', 'E');
    cbState[3][4] = new Cell(false,'E', 'E');
    cbState[3][5] = new Cell(false,'E', 'E');
    cbState[3][6] = new Cell(false,'E', 'E');
    cbState[3][7] = new Cell(false,'E', 'E');
    cbState[4][0] = new Cell(false,'E', 'E');
    cbState[4][1] = new Cell(false,'E', 'E');
    cbState[4][2] = new Cell(false,'E', 'E');
    cbState[4][3] = new Cell(false,'E', 'E');
    cbState[4][4] = new Cell(false,'E', 'E');
    cbState[4][5] = new Cell(false,'E', 'E');
    cbState[4][6] = new Cell(false,'E', 'E');
    cbState[4][7] = new Cell(false,'E', 'E');
    cbState[5][0] = new Cell(false,'E', 'E');
    cbState[5][1] = new Cell(false,'E', 'E');
    cbState[5][2] = new Cell(false,'E', 'E');
    cbState[5][3] = new Cell(false,'E', 'E');
    cbState[5][4] = new Cell(false,'E', 'E');
    cbState[5][5] = new Cell(false,'E', 'E');
    cbState[5][6] = new Cell(false,'E', 'E');
    cbState[5][7] = new Cell(false,'E', 'E');
    cbState[6][0] = new Cell(true,'B', 'P');
    cbState[6][1] = new Cell(true,'B', 'P');
    cbState[6][2] = new Cell(true,'B', 'P');
    cbState[6][3] = new Cell(true,'B', 'P');
    cbState[6][4] = new Cell(true,'B', 'P');
    cbState[6][5] = new Cell(true,'B', 'P');
    cbState[6][6] = new Cell(true,'B', 'P');
    cbState[6][7] = new Cell(true,'B', 'P');
    cbState[7][0] = new Cell(true,'B', 'R');
    cbState[7][1] = new Cell(true,'B', 'B');
    cbState[7][2] = new Cell(true,'B', 'H');
    cbState[7][3] = new Cell(true,'B', 'Q');
    cbState[7][4] = new Cell(true,'B', 'K');
    cbState[7][5] = new Cell(true,'B', 'H');
    cbState[7][6] = new Cell(true,'B', 'B');
    cbState[7][7] = new Cell(true,'B', 'R');*/
};

// Move function implementation
void ChessBoard::move(QueueArray <char *> wordsQueue){
    // Auxiliary variables
    bool promotion = false;
    bool errorFlag = false;
    char * promoType;
    char * from;
    char * destination;
    char * candidate;

    /*
     *  Command interpretation and move execution phase
     *  Analysis of the single words splitted in the previous phase.
     *  If the move is validated, it is performed.
     */
    char * piece = wordsQueue.dequeue();

    // If the piece is a pawn, verify if the move refers to a promoted pawn
    if(strcmp(piece,"PEDINA") == 0){
        if((wordsQueue.count() == 5 || wordsQueue.count() == 3) && wordsQueue.front() == "TORRE" ||
                wordsQueue.front() == "CAVALLO" || wordsQueue.front() == "ALFIERE" || wordsQueue.front() == "REGINA"){
            promoType = wordsQueue.dequeue();
            promotion = true;
        }
    }

    // Superfluous word (preposition)
    wordsQueue.dequeue();

    // Analyze the cases
    if (wordsQueue.count() == 3){       // ambiguous cases
        // prevents errors if the source is a non valid word
        if(strlen(wordsQueue.front()) == 2){
            from = wordsQueue.dequeue();
        } else {
            errorFlag = true;
        }
        // Superfluous word (preposition)
        wordsQueue.dequeue();
        // prevents errors if the destination is a non valid word
        if(strlen(wordsQueue.front()) == 2){
            destination = wordsQueue.dequeue();
        } else{
            errorFlag = true;
        }
    } else if(wordsQueue.count() == 1){ // ordinary cases
        from = NULL;
        // prevents errors if the destination is a non valid word
        if(strlen(wordsQueue.front()) == 2){
            destination = wordsQueue.dequeue();
        } else{
            errorFlag = true;
        }
    }

    // verify if there is a candidate for the move
    if(strcmp(piece,"PEDINA") == 0 && !errorFlag){
        if(promotion){
            candidate = pawnsManager.checkPromotedCandidates(cbState, turn, promoType, from);
            if(candidate != NULL){
                if(promoType == "TORRE"){
                    from = candidate;
                    candidate = rooksManager.checkCandidates(cbState,turn,from,destination);
                } else if(promoType == "ALFIERE"){
                    from = candidate;
                    candidate = bishopsManager.checkCandidates(cbState,turn,from,destination);
                } else if(promoType == "CAVALLO"){
                    from = candidate;
                    candidate = knightsManager.checkCandidates(cbState,turn,from,destination);
                } else if(promoType == "REGINA"){
                    from = candidate;
                    candidate = queensManager.checkCandidates(cbState,turn,from,destination);
                } else if(promoType == "RE"){
                    from = candidate;
                    candidate = kingsManager.checkCandidates(cbState,turn,from,destination);
                }
            }
        } else{
            candidate = pawnsManager.checkCandidates(cbState,turn,from,destination);
        }
    } else if(strcmp(piece,"TORRE") == 0 && !errorFlag){
        candidate = rooksManager.checkCandidates(cbState, turn,from,destination);
    } else if(strcmp(piece,"ALFIERE") == 0 && !errorFlag){
        candidate = bishopsManager.checkCandidates(cbState, turn,from,destination);
    } else if(strcmp(piece,"CAVALLO") == 0 && !errorFlag){
        candidate = knightsManager.checkCandidates(cbState, turn,from,destination);
    } else if(strcmp(piece,"REGINA") == 0 && !errorFlag){
        candidate = queensManager.checkCandidates(cbState, turn,from,destination);
    } else if(strcmp(piece,"RE") == 0 && !errorFlag){
        candidate = kingsManager.checkCandidates(cbState, turn,from,destination);
    }

    // if there is a candidate, perform the move
    if(candidate != NULL && strlen(candidate) == 2){
      // 'A' corresponds to 65 - 65 = 0, 'B' to 66 - 65 = 1, 'C' to 67 - 65 = 2, etc.
      int row = destination[0] - 65;
      // '1' corresponds to 49 - 49 = 0, '2' to 50 - 49 = 1, etc.
      int col = destination[1] - 49;
      // verify if a piece must be transported to the cemetery
      if(cbState[row][col]->getColor() == 'D'){
        // switch on alert led for 5s

        removeDead(destination, row, col);
      }

      // switch on alert led for 5s
      performMove(piece, candidate, destination);

      // Update state of the game
      updateState(candidate, destination);
    } else{
        //Serial.println("Invalid move! Try again!");
        //Serial.println();
    }

    //Serial.println();
    //Serial.println(piece);
    //Serial.print(" moved from ");
    //Serial.print(candidate);
    //Serial.print(" to ");
    //Serial.print(destination);
    //Serial.print(" succesfully executed.");
    //Serial.println();
    toString();
};

void ChessBoard::performMove(const char type, const  char * from, const char * to) {
  // transport the electromagnet in the cell where is positioned the piece that has to be moved
  direct("A1", from);

  // for all the pieces different from the knight
  if(type != 'H'){
        // transport the piece to the destination cell through the navigate function
    if (navigate(from, to) == true) {
        // report the electromagnet to the default position (A1)
        direct(to, "A1");
    } else {
        // executed only in case of error: bring back the electromagnet to the default position (A1)
        direct(from, "A1");
    }
  } else{       // in case of knight move
        //implement all the cases
  }
};

// Navigate funtion implementation
bool ChessBoard::navigate(const char * from, const char * to) {
  // power up the CNC board
  digitalWrite (POWER_CNC, HIGH);
  //power up the magnet
  digitalWrite (POWER_MAGNET, HIGH);

  // wait the board to power up
  delay(1000);

  // es: navigate from A1 to C3
  bool dirX = to[0] > from[0]; // es: C > A --> true
  bool dirY = to[1] < from[1]; // es: 3 > 1 --> true
  // es: navigate from A1 to C3
  int deltaX = abs(to[0] - from[0]);  // es: C - A = 2
  int deltaY = abs(to[1] - from[1]);  // es: 3 - 1 = 2

  if (deltaX == deltaY) {
    // diagonal
    for (int i = 0; i < deltaX * STEPS/5; i++) {
      stepperMovement(dirX, X_DIR, X_STP, 5);
      stepperMovement(dirY, Y_DIR, Y_STP, 5);
    }
  } else {
    if (deltaX * deltaX == 0) {     // horizontal or vertical move
      stepperMovement(dirX, X_DIR, X_STP, STEPS * deltaX);
      stepperMovement(dirY, Y_DIR, Y_STP, STEPS * deltaY);
    } else {      // move not valid
      // switch off the electromagnet
      digitalWrite (POWER_MAGNET, LOW);
      return false;
    }
  }

  // wait the CNC to finish
  delay(500);

  //power off the electromagnet
  digitalWrite (POWER_MAGNET, LOW);
  //power off the CNC board
  digitalWrite (POWER_CNC, LOW);

  return true;
};

// Direct function implementation
void ChessBoard::direct(const char * from, const char * to) {
  // power up the CNC board
  digitalWrite (POWER_CNC, HIGH);

  // wait the board to power up
  delay(1000);

  // es: navigate from A1 to C3
  bool dirX = to[0] > from[0]; // es: C > A --> true
  bool dirY = to[1] < from[1]; // es: 3 > 1 --> true
  // es: navigate from A1 to C3
  int deltaX = abs(to[0] - from[0]);  // es: C - A = 2
  int deltaY = abs(to[1] - from[1]);  // es: 3 - 1 = 2

  stepperMovement(dirX, X_DIR, X_STP, STEPS * deltaY);
  stepperMovement(dirY, Y_DIR, Y_STP, STEPS * deltaY);

  // wait the CNC to finish
  delay(500);

  //power off the CNC board
  digitalWrite (POWER_CNC, LOW);
};

// Stepper movement function implementation
void ChessBoard::stepperMovement (bool dir, byte dirPin, byte stepperPin, int steps){
    digitalWrite (dirPin, dir);
    delay (50);

    for (int i = 0; i < steps; i++) {
        digitalWrite (stepperPin, HIGH);
        delayMicroseconds (800);
        digitalWrite (stepperPin, LOW);
        delayMicroseconds (800);
    }
};

// Remove dead implementation
void ChessBoard::removeDead(const char * destination, int row, int col){
    if(cbState[row][col]->getPiece() == 'P'){
      pawnsManager.findAndRemove(turn, destination);
    } else if(cbState[row][col]->getPiece() == 'R'){
      rooksManager.findAndRemove(turn, destination);
    } else if(cbState[row][col]->getPiece() == 'B'){
      bishopsManager.findAndRemove(turn, destination);
    } else if(cbState[row][col]->getPiece() == 'H'){
      knightsManager.findAndRemove(turn, destination);
    } else if(cbState[row][col]->getPiece() == 'Q'){
      queensManager.findAndRemove(turn, destination);
    } else if(cbState[row][col]->getPiece() == 'K'){
      kingsManager.findAndRemove(turn, destination);
    }

    cbState[row][col]->setBusy();
    cbState[row][col]->setColor('E');
    cbState[row][col]->setPiece('E');

    // implementation of the algorithm to remove the piece

    // led signal to indicate the removal of the piece

};

// Update State function implementation
void ChessBoard::updateState(const char * oldPosition, const char * newPosition) {
  // update position of the piece on the ChessBoard
  // 'A' corresponds to 65 - 65 = 0, 'B' to 66 - 65 = 1, 'C' to 67 - 65 = 2, etc.
  int rowOld = oldPosition[0] - 65;
  // '1' corresponds to 49 - 49 = 0, '2' to 50 - 49 = 1, etc.
  int colOld = oldPosition[1] - 49;
  // 'A' corresponds to 65 - 65 = 0, 'B' to 66 - 65 = 1, 'C' to 67 - 65 = 2, etc.
  int rowNew = newPosition[0] - 65;
  // '1' corresponds to 49 - 49 = 0, '2' to 50 - 49 = 1, etc.
  int colNew = newPosition[1] - 49;

  // set the old position to empty
  cbState[rowOld][colOld]->setBusy();
  // set the new position to busy
  cbState[rowNew][colNew]->setBusy();

  // change the turn of the player
  setTurnPlayer();
};

// SetTurnPlayer function implementation
void ChessBoard::setTurnPlayer(){
    turn = !turn;
};

void ChessBoard::toString(){
    //Serial.println();
    //Serial.println("--- Game State ---");
    //Serial.println();
    //Serial.print("Turn : ");
    //Serial.println(turn);
    //Serial.println();
    //Serial.println("Chessboard : ");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //Serial.print("Cell  : ");
            //Serial.print(char(i + 65));
            //Serial.println(char(j + 48));
            cbState[i][j]->toString();
        }
    }
    //Serial.println();

    pawnsManager.toString();
};
