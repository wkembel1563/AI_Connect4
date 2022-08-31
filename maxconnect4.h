#ifndef __MAXCONNECT4_H
#define __MAXCONNECT4_H
#include <stdio.h>
#include <iostream> 
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string> 
#include <limits> 
#include <algorithm> 
#include <chrono>
#include <thread> 


/*************
 * CONSTANTS *
 *************/ 
#define RED 1		// player 1
#define GREEN 2		// player 2
#define COMPNEXT 3
#define HUMANNEXT 0
#define HUMAN -1
#define COMP -2

/*********************
 * CLASS DECLARATIONS *
 *********************/ 
class gameStatus 	
{ 
public: 
  long * gameData;
  int pos_inf; 
  int neg_inf; 
  long * gameBoard[6];
  long currentTurn;
  int player1Score;
  int player2Score;
  int pieceCount;
  int depth;
  int currentDepth; 
  bool computerIsRed; 
  FILE *gameFile;

  gameStatus()
  {
    pos_inf = std::numeric_limits<int>::max(); 
    neg_inf = std::numeric_limits<int>::lowest(); 
    gameData = new long[42];
    gameBoard[0] = &(gameData[0]);
    gameBoard[1] = &(gameData[7]);
    gameBoard[2] = &(gameData[14]);
    gameBoard[3] = &(gameData[21]);
    gameBoard[4] = &(gameData[28]);
    gameBoard[5] = &(gameData[35]);

    int i;
    for (i = 0; i < 42; i++)
    {
      gameData[i] = 0;
    }

    currentTurn = RED;
    player1Score = 0;
    player2Score = 0;
    pieceCount = 0;
    gameFile = 0;
  }

  gameStatus(const gameStatus &game); 

  int minimax(); 
  bool colFull(int idx); 
  int maxVal(gameStatus &vgame, int alpha, int beta, int &val); 
  int minVal(gameStatus &vgame, int alpha, int beta, int &val); 
  int isCutOff(); 
  int eval(); 
  int scorePotential(int type, int who); 


  ~gameStatus()
  {
    /* delete [] gameData; */
  }
};


/********************
 * HELPER FUNCTIONS *
 ********************/ 
void printGameBoard(gameStatus &currentGame); 
void printGameBoardToFile(gameStatus &currentGame); 
int playPiece(int column, gameStatus &currentGame); 
void aiPlay(gameStatus &currentGame); 
void countScore(gameStatus &currentGame); 
void validate(int argc, char** argv); 
void playInteractive(char** command_line); 
void playOneMove(char ** command_line); 
void humanPlay(gameStatus &currentGame); 
void saveGame(gameStatus &currentGame, char output[30]);

#endif 
