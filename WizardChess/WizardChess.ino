/*
 * WizardChess
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

#include <SoftwareSerial.h>
#include "ChessBoard.h"

// Bluetooth: define software serial
SoftwareSerial BT(BT_RX, BT_TX);

ChessBoard chessBoard;

// Auxiliary functions declaration
boolean recognizePromotion(char *);

void setup() {

  // Serial setup
  Serial.begin(9600);

  // Software serial setup
  BT.begin(9600);

  // NEMA 17 pins setup
  pinMode (X_DIR, OUTPUT);
  pinMode (X_STP, OUTPUT);
  pinMode (Y_DIR, OUTPUT);
  pinMode (Y_STP, OUTPUT);
  pinMode (EN, OUTPUT);
  digitalWrite (EN, LOW);

  // RELAY pins setup
  pinMode(RELAY, OUTPUT);

  chessBoard = ChessBoard();

  delay(1000);
}

void loop(){

  // Speech to text auxiliary variables
  boolean command = true;
  boolean promotion = false;
  int index = 0;
  char voice[256] = "";
  QueueArray <char *> queue;

  /*
   *  Speech recognition and speech-to-text translation phase
   *  Reading of the characters coming from the speech source and received
   *  via bluetooth communication.
   *  The carachters are stored in the voice variable (String type).
  */

  // Speech recognition phase
  while(command){

    // Check if there is an available byte to read
    // Cycle waiting for a communication with the speech source
    while (BT.available()){
      // Delay added to make thing stable
      delay(10);

      // Conduct a serial read
      char c = toupper(BT.read());

      // Add the character read to the speech-to-text string
      voice[index] = c;

      // Set command to false in order to exit from the external cycle
      // (communication with the speech source completed)
      command = false;

      index++;
    }

    /* Split phase: if the string obtained from the previous recognition phase
    * is not a empty string, it is splitted in order to analyze the words contained in it
    * and perform the player move.
    * Each word of the string is stored inside a queue of words.
    */
    if (strlen(voice) > 0){
      char * temp = strtok(voice, " ");
      queue.enqueue(temp);

      while(temp != NULL){
        temp = strtok(NULL," ");

        if(temp != NULL){
          queue.enqueue(temp);
        }
      }
    }
  }

  /*
   *  Command interpretation and move execution phase
   *  Analysis of the single words splitted in the previous phase.
   *  If the move is validated, it is performed.
   */
   char * piece = queue.dequeue();

   if(strcmp(piece,"PEDINA") == 0 && queue.count() == 5){
       char * promotion = queue.dequeue();
       promotion = true;
    }

    queue.dequeue();

    if (queue.count() == 3){
      char * from = queue.dequeue();
      queue.dequeue();
      char * destination = queue.dequeue();
    } else if(queue.count() == 1){
      char * from = NULL;
      char * destination = queue.dequeue();
    }

    if(strcmp(piece,"PEDINA") == 0){
      if(promotion){
          chessBoard.pawnsManager.checkCandidates(chessBoard.getTurnPlayer(),from,destination);
      } else{
        chessBoard.pawnsManager.checkPromotedCandidates(chessBoard.getTurnPlayer(),promotion,from,destination);
      }
    } else if(strcmp(piece,"TORRE") == 0){
        chessBoard.rooksManager.checkCandidates(chessBoard.getTurnPlayer(),from,destination);
    } else if(strcmp(piece,"ALFIERE") == 0){
        chessBoard.bishopsManager.checkCandidates(chessBoard.getTurnPlayer(),from,destination);
    } else if(strcmp(piece,"CAVALLO") == 0){
        chessBoard.knightsManager.checkCandidates(chessBoard.getTurnPlayer(),from,destination);
    } else if(strcmp(piece,"REGINA") == 0){
        chessBoard.queensManager.checkCandidates(chessBoard.getTurnPlayer(),from,destination);
    } else if(strcmp(piece,"RE") == 0){
        chessBoard.kingsManager.checkCandidates(chessBoard.getTurnPlayer(),from,destination);
    } else {
      Serial.println("Unrecognized command. Please, try again!");
    }
   }
}
