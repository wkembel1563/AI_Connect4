#include "maxconnect4.h"

// Output current game status to console
void printGameBoard(gameStatus &currentGame)
{
  int i = 0;
  int j = 0;
  printf(" -----------------\n");
  for(i = 0; i < 6; i++)
  {	
    printf(" | ");
    for(j = 0; j < 7; j++)
    {
      printf("%li ", currentGame.gameBoard[i][j]);
    }
    printf("| \n");
  }
  printf(" -----------------\n");
}


// check if a column is full
bool gameStatus::colFull(int idx) 
{ 
	if(*gameBoard[idx] == 1 || *gameBoard[idx] == 2)
		return true; 

	return false;

}

// Game Object Copy Constructor
gameStatus::gameStatus(const gameStatus &game) 
{

  pos_inf = std::numeric_limits<int>::max(); 
  neg_inf = std::numeric_limits<int>::lowest(); 
  gameData = new long[42]; 
  for(int i = 0; i < 42; i++)
  {
	  gameData[i] = game.gameData[i]; 
  }
  gameBoard[0] = &(gameData[0]);
  gameBoard[1] = &(gameData[7]);
  gameBoard[2] = &(gameData[14]);
  gameBoard[3] = &(gameData[21]);
  gameBoard[4] = &(gameData[28]);
  gameBoard[5] = &(gameData[35]);
  currentTurn = game.currentTurn;
  player1Score = game.player1Score;
  player2Score = game.player2Score;
  pieceCount = game.pieceCount;
  computerIsRed = game.computerIsRed; 
  depth = game.depth;
  currentDepth = game.currentDepth; 
  gameFile = NULL;

}

int gameStatus::scorePotential(int type, int who) 
{
	
  int i, j;
  int score1 = 0;
  int score2 = 0;
  switch(type)
  {
	  case 2:
		  for(i = 0; i < 6; i++)
		  {
				//check horizontally
				//check player 1
				if(this->gameBoard[i][0] == 1 
					&& this->gameBoard[i][1] == 1) 
					{score1++;}
				if(this->gameBoard[i][1] == 1 
					&& this->gameBoard[i][2] == 1) 
					{score1++;}
				if(this->gameBoard[i][2] == 1 
					&& this->gameBoard[i][3] == 1) 
					{score1++;}
				if(this->gameBoard[i][3] == 1 
					&& this->gameBoard[i][4] == 1) 
					{score1++;}
				if(this->gameBoard[i][4] == 1 
					&& this->gameBoard[i][5] == 1) 
					{score1++;}
				if(this->gameBoard[i][5] == 1 
					&& this->gameBoard[i][6] == 1) 
					{score1++;}
				//check player 2
				if(this->gameBoard[i][0] == 2 
					&& this->gameBoard[i][1] == 2) 
					{score2++;}
				if(this->gameBoard[i][1] == 2 
					&& this->gameBoard[i][2] == 2) 
					{score2++;}
				if(this->gameBoard[i][2] == 2 
					&& this->gameBoard[i][3] == 2) 
					{score2++;}
				if(this->gameBoard[i][3] == 2 
					&& this->gameBoard[i][4] == 2) 
					{score2++;}
				if(this->gameBoard[i][4] == 2 
					&& this->gameBoard[i][5] == 2) 
					{score2++;}
				if(this->gameBoard[i][5] == 2 
					&& this->gameBoard[i][6] == 2) 
					{score2++;}
			}

			//check vertically
			for(j = 0; j < 7; j++)
			{
				//check player 1
				if(this->gameBoard[0][j] == 1 
					&& this->gameBoard[1][j] == 1) 
					{score1++;}
				if(this->gameBoard[1][j] == 1 
					&& this->gameBoard[2][j] == 1) 
					{score1++;}
				if(this->gameBoard[2][j] == 1 
					&& this->gameBoard[3][j] == 1) 
					{score1++;}
				if(this->gameBoard[3][j] == 1 
					&& this->gameBoard[4][j] == 1) 
					{score1++;}
				if(this->gameBoard[4][j] == 1 
					&& this->gameBoard[5][j] == 1) 
					{score1++;}
				//check player 2
				if(this->gameBoard[0][j] == 2 
					&& this->gameBoard[1][j] == 2) 
					{score2++;}
				if(this->gameBoard[1][j] == 2 
					&& this->gameBoard[2][j] == 2) 
					{score2++;}
				if(this->gameBoard[2][j] == 2 
					&& this->gameBoard[3][j] == 2) 
					{score2++;}
				if(this->gameBoard[3][j] == 2 
					&& this->gameBoard[4][j] == 2) 
					{score2++;}
				if(this->gameBoard[4][j] == 2 
					&& this->gameBoard[5][j] == 2) 
					{score2++;}
			}

			//check diagonally
			
			//check player 1
			if(this->gameBoard[2][0] == 1 
				&& this->gameBoard[3][1] == 1) 
					{score1++;}
			if(this->gameBoard[3][1] == 1 
				&& this->gameBoard[4][2] == 1) 
					{score1++;}
			if(this->gameBoard[4][2] == 1 
				&& this->gameBoard[5][3] == 1) 
					{score1++;}

			if(this->gameBoard[1][0] == 1 
				&& this->gameBoard[2][1] == 1) 
					{score1++;}
			if(this->gameBoard[2][1] == 1 
				&& this->gameBoard[3][2] == 1) 
					{score1++;}
			if(this->gameBoard[3][2] == 1 
				&& this->gameBoard[4][3] == 1) 
					{score1++;}
			if(this->gameBoard[4][3] == 1 
				&& this->gameBoard[5][4] == 1) 
					{score1++;}

			if(this->gameBoard[0][0] == 1 
				&& this->gameBoard[1][1] == 1) 
					{score1++;}
			if(this->gameBoard[1][1] == 1 
				&& this->gameBoard[2][2] == 1) 
					{score1++;}
			if(this->gameBoard[2][2] == 1 
				&& this->gameBoard[3][3] == 1) 
					{score1++;}
			if(this->gameBoard[3][3] == 1 
				&& this->gameBoard[4][4] == 1) 
					{score1++;}
			if(this->gameBoard[4][4] == 1 
				&& this->gameBoard[5][5] == 1) 
					{score1++;}

			if(this->gameBoard[0][1] == 1 
				&& this->gameBoard[1][2] == 1) 
					{score1++;}
			if(this->gameBoard[1][2] == 1 
				&& this->gameBoard[2][3] == 1) 
					{score1++;}
			if(this->gameBoard[2][3] == 1 
				&& this->gameBoard[3][4] == 1) 
					{score1++;}
			if(this->gameBoard[3][4] == 1 
				&& this->gameBoard[4][5] == 1) 
					{score1++;}
			if(this->gameBoard[4][5] == 1 
				&& this->gameBoard[5][6] == 1) 
					{score1++;}

			if(this->gameBoard[0][2] == 1 
				&& this->gameBoard[1][3] == 1) 
					{score1++;}
			if(this->gameBoard[1][3] == 1 
				&& this->gameBoard[2][4] == 1) 
					{score1++;}
			if(this->gameBoard[2][4] == 1 
				&& this->gameBoard[3][5] == 1) 
					{score1++;}
			if(this->gameBoard[3][5] == 1 
				&& this->gameBoard[4][6] == 1) 
					{score1++;}

			if(this->gameBoard[0][3] == 1 
				&& this->gameBoard[1][4] == 1) 
					{score1++;}
			if(this->gameBoard[1][4] == 1 
				&& this->gameBoard[2][5] == 1) 
					{score1++;}
			if(this->gameBoard[2][5] == 1 
				&& this->gameBoard[3][6] == 1) 
					{score1++;}

			if(this->gameBoard[0][3] == 1 
				&& this->gameBoard[1][2] == 1) 
					{score1++;}
			if(this->gameBoard[1][2] == 1 
				&& this->gameBoard[2][1] == 1) 
					{score1++;}
			if(this->gameBoard[2][1] == 1 
				&& this->gameBoard[3][0] == 1) 
					{score1++;}

			if(this->gameBoard[0][4] == 1 
				&& this->gameBoard[1][3] == 1) 
					{score1++;}
			if(this->gameBoard[1][3] == 1 
				&& this->gameBoard[2][2] == 1) 
					{score1++;}
			if(this->gameBoard[2][2] == 1 
				&& this->gameBoard[3][1] == 1) 
					{score1++;}
			if(this->gameBoard[3][1] == 1 
				&& this->gameBoard[4][0] == 1) 
					{score1++;}

			if(this->gameBoard[0][5] == 1 
				&& this->gameBoard[1][4] == 1) 
					{score1++;}
			if(this->gameBoard[1][4] == 1 
				&& this->gameBoard[2][3] == 1) 
					{score1++;}
			if(this->gameBoard[2][3] == 1 
				&& this->gameBoard[3][2] == 1) 
					{score1++;}
			if(this->gameBoard[3][2] == 1 
				&& this->gameBoard[4][1] == 1) 
					{score1++;}
			if(this->gameBoard[4][1] == 1 
				&& this->gameBoard[5][0] == 1) 
					{score1++;}

			if(this->gameBoard[0][6] == 1 
				&& this->gameBoard[1][5] == 1) 
					{score1++;}
			if(this->gameBoard[1][5] == 1 
				&& this->gameBoard[2][4] == 1) 
					{score1++;}
			if(this->gameBoard[2][4] == 1 
				&& this->gameBoard[3][3] == 1) 
					{score1++;}
			if(this->gameBoard[3][3] == 1 
				&& this->gameBoard[4][2] == 1) 
					{score1++;}
			if(this->gameBoard[4][2] == 1 
				&& this->gameBoard[5][1] == 1) 
					{score1++;}

			if(this->gameBoard[1][6] == 1 
				&& this->gameBoard[2][5] == 1) 
					{score1++;}
			if(this->gameBoard[2][5] == 1 
				&& this->gameBoard[3][4] == 1) 
					{score1++;}
			if(this->gameBoard[3][4] == 1 
				&& this->gameBoard[4][3] == 1) 
					{score1++;}
			if(this->gameBoard[4][3] == 1 
				&& this->gameBoard[5][2] == 1) 
					{score1++;}

			if(this->gameBoard[2][6] == 1 
				&& this->gameBoard[3][5] == 1) 
					{score1++;}
			if(this->gameBoard[3][5] == 1 
				&& this->gameBoard[4][4] == 1) 
					{score1++;}
			if(this->gameBoard[4][4] == 1 
				&& this->gameBoard[5][3] == 1) 
					{score1++;}
				
			//check player 2
			if(this->gameBoard[2][0] == 2 
				&& this->gameBoard[3][1] == 2) 
					{score2++;}
			if(this->gameBoard[3][1] == 2 
				&& this->gameBoard[4][2] == 2) 
					{score2++;}
			if(this->gameBoard[4][2] == 2 
				&& this->gameBoard[5][3] == 2) 
					{score2++;}

			if(this->gameBoard[1][0] == 2 
				&& this->gameBoard[2][1] == 2) 
					{score2++;}
			if(this->gameBoard[2][1] == 2 
				&& this->gameBoard[3][2] == 2) 
					{score2++;}
			if(this->gameBoard[3][2] == 2 
				&& this->gameBoard[4][3] == 2) 
					{score2++;}
			if(this->gameBoard[4][3] == 2 
				&& this->gameBoard[5][4] == 2) 
					{score2++;}

			if(this->gameBoard[0][0] == 2 
				&& this->gameBoard[1][1] == 2) 
					{score2++;}
			if(this->gameBoard[1][1] == 2 
				&& this->gameBoard[2][2] == 2) 
					{score2++;}
			if(this->gameBoard[2][2] == 2 
				&& this->gameBoard[3][3] == 2) 
					{score2++;}
			if(this->gameBoard[3][3] == 2 
				&& this->gameBoard[4][4] == 2) 
					{score2++;}
			if(this->gameBoard[4][4] == 2 
				&& this->gameBoard[5][5] == 2) 
					{score2++;}

			if(this->gameBoard[0][1] == 2 
				&& this->gameBoard[1][2] == 2) 
					{score2++;}
			if(this->gameBoard[1][2] == 2 
				&& this->gameBoard[2][3] == 2) 
					{score2++;}
			if(this->gameBoard[2][3] == 2 
				&& this->gameBoard[3][4] == 2) 
					{score2++;}
			if(this->gameBoard[3][4] == 2 
				&& this->gameBoard[4][5] == 2) 
					{score2++;}
			if(this->gameBoard[4][5] == 2 
				&& this->gameBoard[5][6] == 2) 
					{score2++;}

			if(this->gameBoard[0][2] == 2 
				&& this->gameBoard[1][3] == 2) 
					{score2++;}
			if(this->gameBoard[1][3] == 2 
				&& this->gameBoard[2][4] == 2) 
					{score2++;}
			if(this->gameBoard[2][4] == 2 
				&& this->gameBoard[3][5] == 2) 
					{score2++;}
			if(this->gameBoard[3][5] == 2 
				&& this->gameBoard[4][6] == 2) 
					{score2++;}

			if(this->gameBoard[0][3] == 2 
				&& this->gameBoard[1][4] == 2) 
					{score2++;}
			if(this->gameBoard[1][4] == 2 
				&& this->gameBoard[2][5] == 2) 
					{score2++;}
			if(this->gameBoard[2][5] == 2 
				&& this->gameBoard[3][6] == 2) 
					{score2++;}

			if(this->gameBoard[0][3] == 2 
				&& this->gameBoard[1][2] == 2) 
					{score2++;}
			if(this->gameBoard[1][2] == 2 
				&& this->gameBoard[2][1] == 2) 
					{score2++;}
			if(this->gameBoard[2][1] == 2 
				&& this->gameBoard[3][0] == 2) 
					{score2++;}

			if(this->gameBoard[0][4] == 2 
				&& this->gameBoard[1][3] == 2) 
					{score2++;}
			if(this->gameBoard[1][3] == 2 
				&& this->gameBoard[2][2] == 2) 
					{score2++;}
			if(this->gameBoard[2][2] == 2 
				&& this->gameBoard[3][1] == 2) 
					{score2++;}
			if(this->gameBoard[3][1] == 2 
				&& this->gameBoard[4][0] == 2) 
					{score2++;}

			if(this->gameBoard[0][5] == 2 
				&& this->gameBoard[1][4] == 2) 
					{score2++;}
			if(this->gameBoard[1][4] == 2 
				&& this->gameBoard[2][3] == 2) 
					{score2++;}
			if(this->gameBoard[2][3] == 2 
				&& this->gameBoard[3][2] == 2) 
					{score2++;}
			if(this->gameBoard[3][2] == 2 
				&& this->gameBoard[4][1] == 2) 
					{score2++;}
			if(this->gameBoard[4][1] == 2 
				&& this->gameBoard[5][0] == 2) 
					{score2++;}

			if(this->gameBoard[0][6] == 2 
				&& this->gameBoard[1][5] == 2) 
					{score2++;}
			if(this->gameBoard[1][5] == 2 
				&& this->gameBoard[2][4] == 2) 
					{score2++;}
			if(this->gameBoard[2][4] == 2 
				&& this->gameBoard[3][3] == 2) 
					{score2++;}
			if(this->gameBoard[3][3] == 2 
				&& this->gameBoard[4][2] == 2) 
					{score2++;}
			if(this->gameBoard[4][2] == 2 
				&& this->gameBoard[5][1] == 2) 
					{score2++;}

			if(this->gameBoard[1][6] == 2 
				&& this->gameBoard[2][5] == 2) 
					{score2++;}
			if(this->gameBoard[2][5] == 2 
				&& this->gameBoard[3][4] == 2) 
					{score2++;}
			if(this->gameBoard[3][4] == 2 
				&& this->gameBoard[4][3] == 2) 
					{score2++;}
			if(this->gameBoard[4][3] == 2 
				&& this->gameBoard[5][2] == 2) 
					{score2++;}

			if(this->gameBoard[2][6] == 2 
				&& this->gameBoard[3][5] == 2) 
					{score2++;}
			if(this->gameBoard[3][5] == 2 
				&& this->gameBoard[4][4] == 2) 
					{score2++;}
			if(this->gameBoard[4][4] == 2 
				&& this->gameBoard[5][3] == 2) 
					{score2++;}
		  break; 
	
	  case 3: 
		  
		  for(i = 0; i < 6; i++)
		  {
				//check horizontally
				//check player 1
				if(this->gameBoard[i][0] == 1 
					&& this->gameBoard[i][1] == 1 
					&& this->gameBoard[i][2] == 1)
					{score1++;}
				if(this->gameBoard[i][1] == 1 
					&& this->gameBoard[i][2] == 1 
					&& this->gameBoard[i][3] == 1)
					{score1++;}
				if(this->gameBoard[i][2] == 1 
					&& this->gameBoard[i][3] == 1 
					&& this->gameBoard[i][4] == 1)
					{score1++;}
				if(this->gameBoard[i][3] == 1 
					&& this->gameBoard[i][4] == 1 
					&& this->gameBoard[i][5] == 1)
					{score1++;}
				if(this->gameBoard[i][4] == 1 
					&& this->gameBoard[i][5] == 1 
					&& this->gameBoard[i][6] == 1)
					{score1++;}
				//check player 2
				if(this->gameBoard[i][0] == 2 
					&& this->gameBoard[i][1] == 2 
					&& this->gameBoard[i][2] == 2)
					{score2++;}
				if(this->gameBoard[i][1] == 2 
					&& this->gameBoard[i][2] == 2 
					&& this->gameBoard[i][3] == 2)
					{score2++;}
				if(this->gameBoard[i][2] == 2 
					&& this->gameBoard[i][3] == 2 
					&& this->gameBoard[i][4] == 2)
					{score2++;}
				if(this->gameBoard[i][3] == 2 
					&& this->gameBoard[i][4] == 2 
					&& this->gameBoard[i][5] == 2)
					{score2++;}
				if(this->gameBoard[i][4] == 2 
					&& this->gameBoard[i][5] == 2 
					&& this->gameBoard[i][6] == 2)
					{score2++;}
			}

			//check vertically
			for(j = 0; j < 7; j++)
			{
				//check player 1
				if(this->gameBoard[0][j] == 1 
					&& this->gameBoard[1][j] == 1 
					&& this->gameBoard[2][j] == 1)
					{score1++;}
				if(this->gameBoard[1][j] == 1 
					&& this->gameBoard[2][j] == 1 
					&& this->gameBoard[3][j] == 1)
					{score1++;}
				if(this->gameBoard[2][j] == 1 
					&& this->gameBoard[3][j] == 1 
					&& this->gameBoard[4][j] == 1)
					{score1++;}
				if(this->gameBoard[3][j] == 1 
					&& this->gameBoard[4][j] == 1 
					&& this->gameBoard[5][j] == 1)
					{score1++;}
				//check player 2
				if(this->gameBoard[0][j] == 2 
					&& this->gameBoard[1][j] == 2 
					&& this->gameBoard[2][j] == 2)
					{score2++;}
				if(this->gameBoard[1][j] == 2 
					&& this->gameBoard[2][j] == 2 
					&& this->gameBoard[3][j] == 2)
					{score2++;}
				if(this->gameBoard[2][j] == 2 
					&& this->gameBoard[3][j] == 2 
					&& this->gameBoard[4][j] == 2)
					{score2++;}
				if(this->gameBoard[3][j] == 2 
					&& this->gameBoard[4][j] == 2 
					&& this->gameBoard[5][j] == 2)
					{score2++;}
			}

			//check diagonally
			
			//check player 1
			if(this->gameBoard[2][0] == 1 
				&& this->gameBoard[3][1] == 1 
				&& this->gameBoard[4][2] == 1)
					{score1++;}
			if(this->gameBoard[3][1] == 1 
				&& this->gameBoard[4][2] == 1 
				&& this->gameBoard[5][3] == 1)
					{score1++;}

			if(this->gameBoard[1][0] == 1 
				&& this->gameBoard[2][1] == 1 
				&& this->gameBoard[3][2] == 1)
					{score1++;}
			if(this->gameBoard[2][1] == 1 
				&& this->gameBoard[3][2] == 1 
				&& this->gameBoard[4][3] == 1)
					{score1++;}
			if(this->gameBoard[3][2] == 1 
				&& this->gameBoard[4][3] == 1 
				&& this->gameBoard[5][4] == 1)
					{score1++;}

			if(this->gameBoard[0][0] == 1 
				&& this->gameBoard[1][1] == 1 
				&& this->gameBoard[2][2] == 1)
					{score1++;}
			if(this->gameBoard[1][1] == 1 
				&& this->gameBoard[2][2] == 1 
				&& this->gameBoard[3][3] == 1)
					{score1++;}
			if(this->gameBoard[2][2] == 1 
				&& this->gameBoard[3][3] == 1 
				&& this->gameBoard[4][4] == 1)
					{score1++;}
			if(this->gameBoard[3][3] == 1 
				&& this->gameBoard[4][4] == 1 
				&& this->gameBoard[5][5] == 1)
					{score1++;}

			if(this->gameBoard[0][1] == 1 
				&& this->gameBoard[1][2] == 1 
				&& this->gameBoard[2][3] == 1)
					{score1++;}
			if(this->gameBoard[1][2] == 1 
				&& this->gameBoard[2][3] == 1 
				&& this->gameBoard[3][4] == 1)
					{score1++;}
			if(this->gameBoard[2][3] == 1 
				&& this->gameBoard[3][4] == 1 
				&& this->gameBoard[4][5] == 1)
					{score1++;}
			if(this->gameBoard[3][4] == 1 
				&& this->gameBoard[4][5] == 1 
				&& this->gameBoard[5][6] == 1)
					{score1++;}

			if(this->gameBoard[0][2] == 1 
				&& this->gameBoard[1][3] == 1 
				&& this->gameBoard[2][4] == 1)
					{score1++;}
			if(this->gameBoard[1][3] == 1 
				&& this->gameBoard[2][4] == 1 
				&& this->gameBoard[3][5] == 1)
					{score1++;}
			if(this->gameBoard[2][4] == 1 
				&& this->gameBoard[3][5] == 1 
				&& this->gameBoard[4][6] == 1)
					{score1++;}

			if(this->gameBoard[0][3] == 1 
				&& this->gameBoard[1][4] == 1 
				&& this->gameBoard[2][5] == 1)
					{score1++;}
			if(this->gameBoard[1][4] == 1 
				&& this->gameBoard[2][5] == 1 
				&& this->gameBoard[3][6] == 1)
					{score1++;}

			if(this->gameBoard[0][3] == 1 
				&& this->gameBoard[1][2] == 1 
				&& this->gameBoard[2][1] == 1)
					{score1++;}
			if(this->gameBoard[1][2] == 1 
				&& this->gameBoard[2][1] == 1 
				&& this->gameBoard[3][0] == 1)
					{score1++;}

			if(this->gameBoard[0][4] == 1 
				&& this->gameBoard[1][3] == 1 
				&& this->gameBoard[2][2] == 1)
					{score1++;}
			if(this->gameBoard[1][3] == 1 
				&& this->gameBoard[2][2] == 1 
				&& this->gameBoard[3][1] == 1)
					{score1++;}
			if(this->gameBoard[2][2] == 1 
				&& this->gameBoard[3][1] == 1 
				&& this->gameBoard[4][0] == 1)
					{score1++;}


			if(this->gameBoard[0][5] == 1 
				&& this->gameBoard[1][4] == 1 
				&& this->gameBoard[2][3] == 1)
					{score1++;}
			if(this->gameBoard[1][4] == 1 
				&& this->gameBoard[2][3] == 1 
				&& this->gameBoard[3][2] == 1)
					{score1++;}
			if(this->gameBoard[2][3] == 1 
				&& this->gameBoard[3][2] == 1 
				&& this->gameBoard[4][1] == 1)
					{score1++;}
			if(this->gameBoard[3][2] == 1 
				&& this->gameBoard[4][1] == 1 
				&& this->gameBoard[5][0] == 1)
					{score1++;}

			if(this->gameBoard[0][6] == 1 
				&& this->gameBoard[1][5] == 1 
				&& this->gameBoard[2][4] == 1)
					{score1++;}
			if(this->gameBoard[1][5] == 1 
				&& this->gameBoard[2][4] == 1 
				&& this->gameBoard[3][3] == 1)
					{score1++;}
			if(this->gameBoard[2][4] == 1 
				&& this->gameBoard[3][3] == 1 
				&& this->gameBoard[4][2] == 1)
					{score1++;}
			if(this->gameBoard[3][3] == 1 
				&& this->gameBoard[4][2] == 1 
				&& this->gameBoard[5][1] == 1)
					{score1++;}

			if(this->gameBoard[1][6] == 1 
				&& this->gameBoard[2][5] == 1 
				&& this->gameBoard[3][4] == 1)
					{score1++;}
			if(this->gameBoard[2][5] == 1 
				&& this->gameBoard[3][4] == 1 
				&& this->gameBoard[4][3] == 1)
					{score1++;}
			if(this->gameBoard[3][4] == 1 
				&& this->gameBoard[4][3] == 1 
				&& this->gameBoard[5][2] == 1)
					{score1++;}

			if(this->gameBoard[2][6] == 1 
				&& this->gameBoard[3][5] == 1 
				&& this->gameBoard[4][4] == 1)
					{score1++;}
			if(this->gameBoard[3][5] == 1 
				&& this->gameBoard[4][4] == 1 
				&& this->gameBoard[5][3] == 1)
					{score1++;}
				
			//check player 2
			if(this->gameBoard[2][0] == 2 
				&& this->gameBoard[3][1] == 2 
				&& this->gameBoard[4][2] == 2)
					{score2++;}
			if(this->gameBoard[3][1] == 2 
				&& this->gameBoard[4][2] == 2 
				&& this->gameBoard[5][3] == 2)
					{score2++;}

			if(this->gameBoard[1][0] == 2 
				&& this->gameBoard[2][1] == 2 
				&& this->gameBoard[3][2] == 2)
					{score2++;}
			if(this->gameBoard[2][1] == 2 
				&& this->gameBoard[3][2] == 2 
				&& this->gameBoard[4][3] == 2)
					{score2++;}
			if(this->gameBoard[3][2] == 2 
				&& this->gameBoard[4][3] == 2 
				&& this->gameBoard[5][4] == 2)
					{score2++;}

			if(this->gameBoard[0][0] == 2 
				&& this->gameBoard[1][1] == 2 
				&& this->gameBoard[2][2] == 2)
					{score2++;}
			if(this->gameBoard[1][1] == 2 
				&& this->gameBoard[2][2] == 2 
				&& this->gameBoard[3][3] == 2)
					{score2++;}
			if(this->gameBoard[2][2] == 2 
				&& this->gameBoard[3][3] == 2 
				&& this->gameBoard[4][4] == 2)
					{score2++;}
			if(this->gameBoard[3][3] == 2 
				&& this->gameBoard[4][4] == 2 
				&& this->gameBoard[5][5] == 2)
					{score2++;}

			if(this->gameBoard[0][1] == 2 
				&& this->gameBoard[1][2] == 2 
				&& this->gameBoard[2][3] == 2)
					{score2++;}
			if(this->gameBoard[1][2] == 2 
				&& this->gameBoard[2][3] == 2 
				&& this->gameBoard[3][4] == 2)
					{score2++;}
			if(this->gameBoard[2][3] == 2 
				&& this->gameBoard[3][4] == 2 
				&& this->gameBoard[4][5] == 2)
					{score2++;}
			if(this->gameBoard[3][4] == 2 
				&& this->gameBoard[4][5] == 2 
				&& this->gameBoard[5][6] == 2)
					{score2++;}

			if(this->gameBoard[0][2] == 2 
				&& this->gameBoard[1][3] == 2 
				&& this->gameBoard[2][4] == 2)
					{score2++;}
			if(this->gameBoard[1][3] == 2 
				&& this->gameBoard[2][4] == 2 
				&& this->gameBoard[3][5] == 2)
					{score2++;}
			if(this->gameBoard[2][4] == 2 
				&& this->gameBoard[3][5] == 2 
				&& this->gameBoard[4][6] == 2)
					{score2++;}

			if(this->gameBoard[0][3] == 2 
				&& this->gameBoard[1][4] == 2 
				&& this->gameBoard[2][5] == 2)
					{score2++;}
			if(this->gameBoard[1][4] == 2 
				&& this->gameBoard[2][5] == 2 
				&& this->gameBoard[3][6] == 2)
					{score2++;}

			if(this->gameBoard[0][3] == 2 
				&& this->gameBoard[1][2] == 2 
				&& this->gameBoard[2][1] == 2)
					{score2++;}
			if(this->gameBoard[1][2] == 2 
				&& this->gameBoard[2][1] == 2 
				&& this->gameBoard[3][0] == 2)
					{score2++;}

			if(this->gameBoard[0][4] == 2 
				&& this->gameBoard[1][3] == 2 
				&& this->gameBoard[2][2] == 2)
					{score2++;}
			if(this->gameBoard[1][3] == 2 
				&& this->gameBoard[2][2] == 2 
				&& this->gameBoard[3][1] == 2)
					{score2++;}
			if(this->gameBoard[2][2] == 2 
				&& this->gameBoard[3][1] == 2 
				&& this->gameBoard[4][0] == 2)
					{score2++;}


			if(this->gameBoard[0][5] == 2 
				&& this->gameBoard[1][4] == 2 
				&& this->gameBoard[2][3] == 2)
					{score2++;}
			if(this->gameBoard[1][4] == 2 
				&& this->gameBoard[2][3] == 2 
				&& this->gameBoard[3][2] == 2)
					{score2++;}
			if(this->gameBoard[2][3] == 2 
				&& this->gameBoard[3][2] == 2 
				&& this->gameBoard[4][1] == 2)
					{score2++;}
			if(this->gameBoard[3][2] == 2 
				&& this->gameBoard[4][1] == 2 
				&& this->gameBoard[5][0] == 2)
					{score2++;}

			if(this->gameBoard[0][6] == 2 
				&& this->gameBoard[1][5] == 2 
				&& this->gameBoard[2][4] == 2)
					{score2++;}
			if(this->gameBoard[1][5] == 2 
				&& this->gameBoard[2][4] == 2 
				&& this->gameBoard[3][3] == 2)
					{score2++;}
			if(this->gameBoard[2][4] == 2 
				&& this->gameBoard[3][3] == 2 
				&& this->gameBoard[4][2] == 2)
					{score2++;}
			if(this->gameBoard[3][3] == 2 
				&& this->gameBoard[4][2] == 2 
				&& this->gameBoard[5][1] == 2)
					{score2++;}

			if(this->gameBoard[1][6] == 2 
				&& this->gameBoard[2][5] == 2 
				&& this->gameBoard[3][4] == 2)
					{score2++;}
			if(this->gameBoard[2][5] == 2 
				&& this->gameBoard[3][4] == 2 
				&& this->gameBoard[4][3] == 2)
					{score2++;}
			if(this->gameBoard[3][4] == 2 
				&& this->gameBoard[4][3] == 2 
				&& this->gameBoard[5][2] == 2)
					{score2++;}

			if(this->gameBoard[2][6] == 2 
				&& this->gameBoard[3][5] == 2 
				&& this->gameBoard[4][4] == 2)
					{score2++;}
			if(this->gameBoard[3][5] == 2 
				&& this->gameBoard[4][4] == 2 
				&& this->gameBoard[5][3] == 2)
					{score2++;}
		  break; 

	  case 4:
		  for(i = 0; i < 6; i++)
		  {
				//check horizontally
				//check player 1
				if(this->gameBoard[i][0] == 1 && this->gameBoard[i][1] == 1 
					&& this->gameBoard[i][2] == 1 && this->gameBoard[i][3] == 1)
					{score1++;}
				if(this->gameBoard[i][1] == 1 && this->gameBoard[i][2] == 1 
					&& this->gameBoard[i][3] == 1 && this->gameBoard[i][4] == 1)
					{score1++;}
				if(this->gameBoard[i][2] == 1 && this->gameBoard[i][3] == 1 
					&& this->gameBoard[i][4] == 1 && this->gameBoard[i][5] == 1)
					{score1++;}
				if(this->gameBoard[i][3] == 1 && this->gameBoard[i][4] == 1 
					&& this->gameBoard[i][5] == 1 && this->gameBoard[i][6] == 1)
					{score1++;}
				//check player 2
				if(this->gameBoard[i][0] == 2 && this->gameBoard[i][1] == 2 
					&& this->gameBoard[i][2] == 2 && this->gameBoard[i][3] == 2)
					{score2++;}
				if(this->gameBoard[i][1] == 2 && this->gameBoard[i][2] == 2 
					&& this->gameBoard[i][3] == 2 && this->gameBoard[i][4] == 2)
					{score2++;}
				if(this->gameBoard[i][2] == 2 && this->gameBoard[i][3] == 2 
					&& this->gameBoard[i][4] == 2 && this->gameBoard[i][5] == 2)
					{score2++;}
				if(this->gameBoard[i][3] == 2 && this->gameBoard[i][4] == 2 
					&& this->gameBoard[i][5] == 2 && this->gameBoard[i][6] == 2)
					{score2++;}
			}

			//check vertically
			for(j = 0; j < 7; j++)
			{
				//check player 1
				if(this->gameBoard[0][j] == 1 && this->gameBoard[1][j] == 1 
					&& this->gameBoard[2][j] == 1 && this->gameBoard[3][j] == 1)
					{score1++;}
				if(this->gameBoard[1][j] == 1 && this->gameBoard[2][j] == 1 
					&& this->gameBoard[3][j] == 1 && this->gameBoard[4][j] == 1)
					{score1++;}
				if(this->gameBoard[2][j] == 1 && this->gameBoard[3][j] == 1 
					&& this->gameBoard[4][j] == 1 && this->gameBoard[5][j] == 1)
					{score1++;}
				//check player 2
				if(this->gameBoard[0][j] == 2 && this->gameBoard[1][j] == 2 
					&& this->gameBoard[2][j] == 2 && this->gameBoard[3][j] == 2)
					{score2++;}
				if(this->gameBoard[1][j] == 2 && this->gameBoard[2][j] == 2 
					&& this->gameBoard[3][j] == 2 && this->gameBoard[4][j] == 2)
					{score2++;}
				if(this->gameBoard[2][j] == 2 && this->gameBoard[3][j] == 2 
					&& this->gameBoard[4][j] == 2 && this->gameBoard[5][j] == 2)
					{score2++;}
			}

			//check diagonally
			
			//check player 1
			if(this->gameBoard[2][0] == 1 && this->gameBoard[3][1] == 1 
				&& this->gameBoard[4][2] == 1 && this->gameBoard[5][3] == 1)
					{score1++;}
			if(this->gameBoard[1][0] == 1 && this->gameBoard[2][1] == 1 
				&& this->gameBoard[3][2] == 1 && this->gameBoard[4][3] == 1)
					{score1++;}
			if(this->gameBoard[2][1] == 1 && this->gameBoard[3][2] == 1 
				&& this->gameBoard[4][3] == 1 && this->gameBoard[5][4] == 1)
					{score1++;}
			if(this->gameBoard[0][0] == 1 && this->gameBoard[1][1] == 1 
				&& this->gameBoard[2][2] == 1 && this->gameBoard[3][3] == 1)
					{score1++;}
			if(this->gameBoard[1][1] == 1 && this->gameBoard[2][2] == 1 
				&& this->gameBoard[3][3] == 1 && this->gameBoard[4][4] == 1)
					{score1++;}
			if(this->gameBoard[2][2] == 1 && this->gameBoard[3][3] == 1 
				&& this->gameBoard[4][4] == 1 && this->gameBoard[5][5] == 1)
					{score1++;}
			if(this->gameBoard[0][1] == 1 && this->gameBoard[1][2] == 1 
				&& this->gameBoard[2][3] == 1 && this->gameBoard[3][4] == 1)
					{score1++;}
			if(this->gameBoard[1][2] == 1 && this->gameBoard[2][3] == 1 
				&& this->gameBoard[3][4] == 1 && this->gameBoard[4][5] == 1)
					{score1++;}
			if(this->gameBoard[2][3] == 1 && this->gameBoard[3][4] == 1 
				&& this->gameBoard[4][5] == 1 && this->gameBoard[5][6] == 1)
					{score1++;}
			if(this->gameBoard[0][2] == 1 && this->gameBoard[1][3] == 1 
				&& this->gameBoard[2][4] == 1 && this->gameBoard[3][5] == 1)
					{score1++;}
			if(this->gameBoard[1][3] == 1 && this->gameBoard[2][4] == 1 
				&& this->gameBoard[3][5] == 1 && this->gameBoard[4][6] == 1)
					{score1++;}
			if(this->gameBoard[0][3] == 1 && this->gameBoard[1][4] == 1 
				&& this->gameBoard[2][5] == 1 && this->gameBoard[3][6] == 1)
					{score1++;}

			if(this->gameBoard[0][3] == 1 && this->gameBoard[1][2] == 1 
				&& this->gameBoard[2][1] == 1 && this->gameBoard[3][0] == 1)
					{score1++;}
			if(this->gameBoard[0][4] == 1 && this->gameBoard[1][3] == 1 
				&& this->gameBoard[2][2] == 1 && this->gameBoard[3][1] == 1)
					{score1++;}
			if(this->gameBoard[1][3] == 1 && this->gameBoard[2][2] == 1 
				&& this->gameBoard[3][1] == 1 && this->gameBoard[4][0] == 1)
					{score1++;}
			if(this->gameBoard[0][5] == 1 && this->gameBoard[1][4] == 1 
				&& this->gameBoard[2][3] == 1 && this->gameBoard[3][2] == 1)
					{score1++;}
			if(this->gameBoard[1][4] == 1 && this->gameBoard[2][3] == 1 
				&& this->gameBoard[3][2] == 1 && this->gameBoard[4][1] == 1)
					{score1++;}
			if(this->gameBoard[2][3] == 1 && this->gameBoard[3][2] == 1 
				&& this->gameBoard[4][1] == 1 && this->gameBoard[5][0] == 1)
					{score1++;}
			if(this->gameBoard[0][6] == 1 && this->gameBoard[1][5] == 1 
				&& this->gameBoard[2][4] == 1 && this->gameBoard[3][3] == 1)
					{score1++;}
			if(this->gameBoard[1][5] == 1 && this->gameBoard[2][4] == 1 
				&& this->gameBoard[3][3] == 1 && this->gameBoard[4][2] == 1)
					{score1++;}
			if(this->gameBoard[2][4] == 1 && this->gameBoard[3][3] == 1 
				&& this->gameBoard[4][2] == 1 && this->gameBoard[5][1] == 1)
					{score1++;}
			if(this->gameBoard[1][6] == 1 && this->gameBoard[2][5] == 1 
				&& this->gameBoard[3][4] == 1 && this->gameBoard[4][3] == 1)
					{score1++;}
			if(this->gameBoard[2][5] == 1 && this->gameBoard[3][4] == 1 
				&& this->gameBoard[4][3] == 1 && this->gameBoard[5][2] == 1)
					{score1++;}
			if(this->gameBoard[2][6] == 1 && this->gameBoard[3][5] == 1 
				&& this->gameBoard[4][4] == 1 && this->gameBoard[5][3] == 1)
					{score1++;}
				
			//check player 2
			if(this->gameBoard[2][0] == 2 && this->gameBoard[3][1] == 2 
				&& this->gameBoard[4][2] == 2 && this->gameBoard[5][3] == 2)
					{score2++;}
			if(this->gameBoard[1][0] == 2 && this->gameBoard[2][1] == 2 
				&& this->gameBoard[3][2] == 2 && this->gameBoard[4][3] == 2)
					{score2++;}
			if(this->gameBoard[2][1] == 2 && this->gameBoard[3][2] == 2 
				&& this->gameBoard[4][3] == 2 && this->gameBoard[5][4] == 2)
					{score2++;}
			if(this->gameBoard[0][0] == 2 && this->gameBoard[1][1] == 2 
				&& this->gameBoard[2][2] == 2 && this->gameBoard[3][3] == 2)
					{score2++;}
			if(this->gameBoard[1][1] == 2 && this->gameBoard[2][2] == 2 
				&& this->gameBoard[3][3] == 2 && this->gameBoard[4][4] == 2)
					{score2++;}
			if(this->gameBoard[2][2] == 2 && this->gameBoard[3][3] == 2 
				&& this->gameBoard[4][4] == 2 && this->gameBoard[5][5] == 2)
					{score2++;}
			if(this->gameBoard[0][1] == 2 && this->gameBoard[1][2] == 2 
				&& this->gameBoard[2][3] == 2 && this->gameBoard[3][4] == 2)
					{score2++;}
			if(this->gameBoard[1][2] == 2 && this->gameBoard[2][3] == 2 
				&& this->gameBoard[3][4] == 2 && this->gameBoard[4][5] == 2)
					{score2++;}
			if(this->gameBoard[2][3] == 2 && this->gameBoard[3][4] == 2 
				&& this->gameBoard[4][5] == 2 && this->gameBoard[5][6] == 2)
					{score2++;}
			if(this->gameBoard[0][2] == 2 && this->gameBoard[1][3] == 2 
				&& this->gameBoard[2][4] == 2 && this->gameBoard[3][5] == 2)
					{score2++;}
			if(this->gameBoard[1][3] == 2 && this->gameBoard[2][4] == 2 
				&& this->gameBoard[3][5] == 2 && this->gameBoard[4][6] == 2)
					{score2++;}
			if(this->gameBoard[0][3] == 2 && this->gameBoard[1][4] == 2 
				&& this->gameBoard[2][5] == 2 && this->gameBoard[3][6] == 2)
					{score2++;}

			if(this->gameBoard[0][3] == 2 && this->gameBoard[1][2] == 2 
				&& this->gameBoard[2][1] == 2 && this->gameBoard[3][0] == 2)
					{score2++;}
			if(this->gameBoard[0][4] == 2 && this->gameBoard[1][3] == 2 
				&& this->gameBoard[2][2] == 2 && this->gameBoard[3][1] == 2)
					{score2++;}
			if(this->gameBoard[1][3] == 2 && this->gameBoard[2][2] == 2
				&& this->gameBoard[3][1] == 2 && this->gameBoard[4][0] == 2)
					{score2++;}
			if(this->gameBoard[0][5] == 2 && this->gameBoard[1][4] == 2 
				&& this->gameBoard[2][3] == 2 && this->gameBoard[3][2] == 2)
					{score2++;}
			if(this->gameBoard[1][4] == 2 && this->gameBoard[2][3] == 2 
				&& this->gameBoard[3][2] == 2 && this->gameBoard[4][1] == 2)
					{score2++;}
			if(this->gameBoard[2][3] == 2 && this->gameBoard[3][2] == 2 
				&& this->gameBoard[4][1] == 2 && this->gameBoard[5][0] == 2)
					{score2++;}
			if(this->gameBoard[0][6] == 2 && this->gameBoard[1][5] == 2 
				&& this->gameBoard[2][4] == 2 && this->gameBoard[3][3] == 2)
					{score2++;}
			if(this->gameBoard[1][5] == 2 && this->gameBoard[2][4] == 2 
				&& this->gameBoard[3][3] == 2 && this->gameBoard[4][2] == 2)
					{score2++;}
			if(this->gameBoard[2][4] == 2 && this->gameBoard[3][3] == 2 
				&& this->gameBoard[4][2] == 2 && this->gameBoard[5][1] == 2)
					{score2++;}
			if(this->gameBoard[1][6] == 2 && this->gameBoard[2][5] == 2 
				&& this->gameBoard[3][4] == 2 && this->gameBoard[4][3] == 2)
					{score2++;}
			if(this->gameBoard[2][5] == 2 && this->gameBoard[3][4] == 2 
				&& this->gameBoard[4][3] == 2 && this->gameBoard[5][2] == 2)
					{score2++;}
			if(this->gameBoard[2][6] == 2 && this->gameBoard[3][5] == 2 
				&& this->gameBoard[4][4] == 2 && this->gameBoard[5][3] == 2)
					{score2++;}
		  break; 

  }

  if(who == COMP)
  {
		if(computerIsRed) return score1; 
		else return score2; 
  }
  else if(who == HUMAN)
  {
		if(computerIsRed) return score2; 
		else return score1; 
  }
  else{
	  printf("Error. Score prediction fail"); 
	  exit(1); 
  }
}

int gameStatus::isCutOff() 
{
	if(currentDepth == depth) return true; 
	else return false; 
}

int gameStatus::eval() 
{
	/* if(columnsFull()) */
	/* { */
	/* 	countScore(*this); */ 
	/* 	if(humanIsRed()) */
	/* 	{ */
	/* 		int h_score = this->player1Score */
	/* 		int c_score = this->player2Score */
	/* 		return h_score - c_score; */ 
	/* 	} */
	/* } */
	int h_twos = scorePotential(2, HUMAN); 
	int h_threes = scorePotential(3, HUMAN); 
	int h_fours = scorePotential(4, HUMAN); 
	int c_twos = scorePotential(2, COMP); 
	int c_threes = scorePotential(3, COMP); 
	int c_fours = scorePotential(4, COMP); 

	int h_eval = (h_twos*2 + h_threes*5 + h_fours*10) + (c_twos*2 + c_threes*5 + c_fours*10); 
	return h_eval; 
}

int gameStatus::minVal(gameStatus &vgame, int alpha, int beta, int &val) 
{

	int move = -1; 
	int a2 = -1; 

	/* apply eval function lowest depth is reached */
	if(vgame.isCutOff()) 
	{
		val = vgame.eval(); 
		return 0; 
	}

	int v = vgame.pos_inf; 
	int v2 = -1; 
	int play;

	/* search each column */
	gameStatus temp = vgame; 
	for(int i = 0; i < 7; ++i)
	{
		// try a move
		play = playPiece(i, vgame); 
		if(play == 0) continue; 
		vgame.currentDepth++; 
		a2 = maxVal(vgame, alpha, beta, v2); 
		
		// reset state 
		vgame = temp; 
		
		// evaluate move result
		if(v2 < v)
		{
			v = v2; 
			move = i; 
			beta = std::min(beta, v); 
		}
		if(v <= alpha)
		{
			val = v; 
			return move; 
		}
	}

	val = v; 
	return move; 
}

// Depth-limited minimax search maxval function
int gameStatus::maxVal(gameStatus& vgame, int alpha, int beta, int &val) 
{
	int move = -1; 
	int a2 = -1; 

	/* apply eval function lowest depth is reached */
	if(vgame.isCutOff()) 
	{
		val = vgame.eval(); 
		return 0; 
	}

	int v = vgame.neg_inf; 
	int v2 = -1; 
	int play; 

	/* search each column */
	gameStatus temp = vgame; 

	for(int i = 0; i < 7; ++i)
	{
		// try a move
		
		play = playPiece(i, vgame); 
		if(play == 0) continue; 

		vgame.currentDepth++; 
		a2 = minVal(vgame, alpha, beta, v2); 
		
		// reset state 
		vgame = temp; 
		
		// evaluate move result
		if(v2 > v)
		{
			v = v2; 
			move = i; 
			alpha = std::max(alpha, v); 
		}
		if(v >= beta)
		{
			val = v; 
			return move; 
		}
	}

	val = v; 
	return move; 
}

// AI's depth-limited minimax search
int gameStatus::minimax()
{
	int col_move = -1; 
	int move_val = -1; 

	/* create virtual game */
	currentDepth = 0; 
	gameStatus vgame = *this; 

	col_move = maxVal(vgame, neg_inf, pos_inf, move_val); 

	return col_move; 
}


void validate(int argc, char** argv)
{
  char ** command_line = argv;

  if (argc != 5)
  {
    printf("Four command-line arguments are needed:\n");
    printf("Usage: %s interactive [input_file] [computer-next/human-next] [depth]\n", command_line [0]);
    printf("or:  %s one-move [input_file] [output_file] [depth]\n", command_line [0]);
	exit(1); 

  }

}

// save state of game to file
void saveGame(gameStatus &currentGame, char output[30])
{
	  currentGame.gameFile = fopen(output, "w");
	  if (currentGame.gameFile != 0)
	  {
		printGameBoardToFile(currentGame);
		fclose(currentGame.gameFile);
	  }
	  else
	  {
		printf("error: could not open output file %s\n", output);
	  }
}

// Output COMPNEXT if computer plays next
// otherwise output HUMANNEXT 
int whosTurn(char * nextTurn)
{
	int result = 0; 

	if (strcmp(nextTurn, "computer-next") == 0)
	{
		return COMPNEXT; 
	}
	else if(strcmp(nextTurn, "human-next") == 0) 
	{
		return HUMANNEXT;
	}
	else
	{
		printf("Error. Invalid next turn argument"); 	
		exit(1); 
	}

	return result; 
}


// Output current game status to file
void printGameBoardToFile(gameStatus &currentGame)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < 6; i++)
	{	
		for(j = 0; j < 7; j++)
		{
			fprintf(currentGame.gameFile, "%li", currentGame.gameBoard[i][j]);
		}
		fprintf(currentGame.gameFile, "\r\n");
	}
	fprintf(currentGame.gameFile, "%d\r\n", currentGame.currentTurn);
}

// Given a column and which player it is, 
// place that player's piece in the requested column
int playPiece(int column, gameStatus &currentGame)
{
	// if column full, return 1
	if(currentGame.gameBoard[0][column] != 0)
  {
		return 0;
  }
	
  int i;
	// starting at the bottom of the board, place the piece into the
	// first empty spot
	for(i = 5; i >= 0; i--)
	{
		if(currentGame.gameBoard[i][column] == 0)
		{
			currentGame.gameBoard[i][column] = currentGame.currentTurn;
			currentGame.pieceCount++;
			return 1;
		}
	}
  return 0;
}

// Human play sequence
void humanPlay(gameStatus &currentGame) 
{
	int h_move;
	while(true)
	{
		printf("\nPlease select a column to play (1-7): "); 
		std::cin >> h_move; 
		h_move -= 1; 

		/* validate column choice */
		if(h_move == -1)
		{
			printf("Can't choose col == -1\n"); 
		}

		int result = 0;
		result = playPiece(h_move, currentGame);
		if(result == 0)
		{
			printf("Can't choose a full column.\n"); 
		}
		else
		{
		  printf("\n\nmove %li: Player %s, column %li\n", 
			currentGame.pieceCount, ((currentGame.currentTurn == RED)? "RED" : "GREEN"), h_move+1);
		  if(currentGame.currentTurn == RED)
			currentGame.currentTurn = GREEN;
		  else if (currentGame.currentTurn == GREEN)
			currentGame.currentTurn = RED;
		  break; 
		}
	}
}

// The AI section.  
// Plays by performing depth-limited minimax search
void aiPlay(gameStatus &currentGame)
{	
	int ai_move = currentGame.minimax(); 

	/* validate column choice */
	if(ai_move == -1)
	{
		printf("AI Play Error. Col == -1\n"); 
		exit(1); 
	}

	int result = 0;
	result = playPiece(ai_move, currentGame);
	if(result == 0)
    {
      	/* aiPlay(currentGame); */
		printf("AI Play Error. AI chose a full column."); 
		exit(1); 

    }
    else
    {
      printf("\n\nmove %li: Player %s, column %li\n", 
        currentGame.pieceCount, ((currentGame.currentTurn == RED)? "RED" : "GREEN"), ai_move+1);
      if(currentGame.currentTurn == RED)
      	currentGame.currentTurn = GREEN;
      else if (currentGame.currentTurn == GREEN)
      	currentGame.currentTurn = RED;
    }
}

void countScore(gameStatus &currentGame)
{
  currentGame.player1Score = 0; 
  currentGame.player2Score = 0; 

  //check horizontally
  int i;
  for(i = 0; i < 6; i++)
  {
		//check player 1
		if(currentGame.gameBoard[i][0] == 1 && currentGame.gameBoard[i][1] == 1 
			&& currentGame.gameBoard[i][2] == 1 && currentGame.gameBoard[i][3] == 1)
			{currentGame.player1Score++;}
		if(currentGame.gameBoard[i][1] == 1 && currentGame.gameBoard[i][2] == 1 
			&& currentGame.gameBoard[i][3] == 1 && currentGame.gameBoard[i][4] == 1)
			{currentGame.player1Score++;}
		if(currentGame.gameBoard[i][2] == 1 && currentGame.gameBoard[i][3] == 1 
			&& currentGame.gameBoard[i][4] == 1 && currentGame.gameBoard[i][5] == 1)
			{currentGame.player1Score++;}
		if(currentGame.gameBoard[i][3] == 1 && currentGame.gameBoard[i][4] == 1 
			&& currentGame.gameBoard[i][5] == 1 && currentGame.gameBoard[i][6] == 1)
			{currentGame.player1Score++;}
		//check player 2
		if(currentGame.gameBoard[i][0] == 2 && currentGame.gameBoard[i][1] == 2 
			&& currentGame.gameBoard[i][2] == 2 && currentGame.gameBoard[i][3] == 2)
			{currentGame.player2Score++;}
		if(currentGame.gameBoard[i][1] == 2 && currentGame.gameBoard[i][2] == 2 
			&& currentGame.gameBoard[i][3] == 2 && currentGame.gameBoard[i][4] == 2)
			{currentGame.player2Score++;}
		if(currentGame.gameBoard[i][2] == 2 && currentGame.gameBoard[i][3] == 2 
			&& currentGame.gameBoard[i][4] == 2 && currentGame.gameBoard[i][5] == 2)
			{currentGame.player2Score++;}
		if(currentGame.gameBoard[i][3] == 2 && currentGame.gameBoard[i][4] == 2 
			&& currentGame.gameBoard[i][5] == 2 && currentGame.gameBoard[i][6] == 2)
			{currentGame.player2Score++;}
	}

	//check vertically
	int j;
	for(j = 0; j < 7; j++)
	{
		//check player 1
		if(currentGame.gameBoard[0][j] == 1 && currentGame.gameBoard[1][j] == 1 
			&& currentGame.gameBoard[2][j] == 1 && currentGame.gameBoard[3][j] == 1)
			{currentGame.player1Score++;}
		if(currentGame.gameBoard[1][j] == 1 && currentGame.gameBoard[2][j] == 1 
			&& currentGame.gameBoard[3][j] == 1 && currentGame.gameBoard[4][j] == 1)
			{currentGame.player1Score++;}
		if(currentGame.gameBoard[2][j] == 1 && currentGame.gameBoard[3][j] == 1 
			&& currentGame.gameBoard[4][j] == 1 && currentGame.gameBoard[5][j] == 1)
			{currentGame.player1Score++;}
		//check player 2
		if(currentGame.gameBoard[0][j] == 2 && currentGame.gameBoard[1][j] == 2 
			&& currentGame.gameBoard[2][j] == 2 && currentGame.gameBoard[3][j] == 2)
			{currentGame.player2Score++;}
		if(currentGame.gameBoard[1][j] == 2 && currentGame.gameBoard[2][j] == 2 
			&& currentGame.gameBoard[3][j] == 2 && currentGame.gameBoard[4][j] == 2)
			{currentGame.player2Score++;}
		if(currentGame.gameBoard[2][j] == 2 && currentGame.gameBoard[3][j] == 2 
			&& currentGame.gameBoard[4][j] == 2 && currentGame.gameBoard[5][j] == 2)
			{currentGame.player2Score++;}
	}

	//check diagonally
	
	//check player 1
	if(currentGame.gameBoard[2][0] == 1 && currentGame.gameBoard[3][1] == 1 
		&& currentGame.gameBoard[4][2] == 1 && currentGame.gameBoard[5][3] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[1][0] == 1 && currentGame.gameBoard[2][1] == 1 
		&& currentGame.gameBoard[3][2] == 1 && currentGame.gameBoard[4][3] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[2][1] == 1 && currentGame.gameBoard[3][2] == 1 
		&& currentGame.gameBoard[4][3] == 1 && currentGame.gameBoard[5][4] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[0][0] == 1 && currentGame.gameBoard[1][1] == 1 
		&& currentGame.gameBoard[2][2] == 1 && currentGame.gameBoard[3][3] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[1][1] == 1 && currentGame.gameBoard[2][2] == 1 
		&& currentGame.gameBoard[3][3] == 1 && currentGame.gameBoard[4][4] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[2][2] == 1 && currentGame.gameBoard[3][3] == 1 
		&& currentGame.gameBoard[4][4] == 1 && currentGame.gameBoard[5][5] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[0][1] == 1 && currentGame.gameBoard[1][2] == 1 
		&& currentGame.gameBoard[2][3] == 1 && currentGame.gameBoard[3][4] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[1][2] == 1 && currentGame.gameBoard[2][3] == 1 
		&& currentGame.gameBoard[3][4] == 1 && currentGame.gameBoard[4][5] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[2][3] == 1 && currentGame.gameBoard[3][4] == 1 
		&& currentGame.gameBoard[4][5] == 1 && currentGame.gameBoard[5][6] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[0][2] == 1 && currentGame.gameBoard[1][3] == 1 
		&& currentGame.gameBoard[2][4] == 1 && currentGame.gameBoard[3][5] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[1][3] == 1 && currentGame.gameBoard[2][4] == 1 
		&& currentGame.gameBoard[3][5] == 1 && currentGame.gameBoard[4][6] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[0][3] == 1 && currentGame.gameBoard[1][4] == 1 
		&& currentGame.gameBoard[2][5] == 1 && currentGame.gameBoard[3][6] == 1)
			{currentGame.player1Score++;}

	if(currentGame.gameBoard[0][3] == 1 && currentGame.gameBoard[1][2] == 1 
		&& currentGame.gameBoard[2][1] == 1 && currentGame.gameBoard[3][0] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[0][4] == 1 && currentGame.gameBoard[1][3] == 1 
		&& currentGame.gameBoard[2][2] == 1 && currentGame.gameBoard[3][1] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[1][3] == 1 && currentGame.gameBoard[2][2] == 1 
		&& currentGame.gameBoard[3][1] == 1 && currentGame.gameBoard[4][0] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[0][5] == 1 && currentGame.gameBoard[1][4] == 1 
		&& currentGame.gameBoard[2][3] == 1 && currentGame.gameBoard[3][2] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[1][4] == 1 && currentGame.gameBoard[2][3] == 1 
		&& currentGame.gameBoard[3][2] == 1 && currentGame.gameBoard[4][1] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[2][3] == 1 && currentGame.gameBoard[3][2] == 1 
		&& currentGame.gameBoard[4][1] == 1 && currentGame.gameBoard[5][0] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[0][6] == 1 && currentGame.gameBoard[1][5] == 1 
		&& currentGame.gameBoard[2][4] == 1 && currentGame.gameBoard[3][3] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[1][5] == 1 && currentGame.gameBoard[2][4] == 1 
		&& currentGame.gameBoard[3][3] == 1 && currentGame.gameBoard[4][2] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[2][4] == 1 && currentGame.gameBoard[3][3] == 1 
		&& currentGame.gameBoard[4][2] == 1 && currentGame.gameBoard[5][1] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[1][6] == 1 && currentGame.gameBoard[2][5] == 1 
		&& currentGame.gameBoard[3][4] == 1 && currentGame.gameBoard[4][3] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[2][5] == 1 && currentGame.gameBoard[3][4] == 1 
		&& currentGame.gameBoard[4][3] == 1 && currentGame.gameBoard[5][2] == 1)
			{currentGame.player1Score++;}
	if(currentGame.gameBoard[2][6] == 1 && currentGame.gameBoard[3][5] == 1 
		&& currentGame.gameBoard[4][4] == 1 && currentGame.gameBoard[5][3] == 1)
			{currentGame.player1Score++;}
		
	//check player 2
	if(currentGame.gameBoard[2][0] == 2 && currentGame.gameBoard[3][1] == 2 
		&& currentGame.gameBoard[4][2] == 2 && currentGame.gameBoard[5][3] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[1][0] == 2 && currentGame.gameBoard[2][1] == 2 
		&& currentGame.gameBoard[3][2] == 2 && currentGame.gameBoard[4][3] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[2][1] == 2 && currentGame.gameBoard[3][2] == 2 
		&& currentGame.gameBoard[4][3] == 2 && currentGame.gameBoard[5][4] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[0][0] == 2 && currentGame.gameBoard[1][1] == 2 
		&& currentGame.gameBoard[2][2] == 2 && currentGame.gameBoard[3][3] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[1][1] == 2 && currentGame.gameBoard[2][2] == 2 
		&& currentGame.gameBoard[3][3] == 2 && currentGame.gameBoard[4][4] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[2][2] == 2 && currentGame.gameBoard[3][3] == 2 
		&& currentGame.gameBoard[4][4] == 2 && currentGame.gameBoard[5][5] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[0][1] == 2 && currentGame.gameBoard[1][2] == 2 
		&& currentGame.gameBoard[2][3] == 2 && currentGame.gameBoard[3][4] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[1][2] == 2 && currentGame.gameBoard[2][3] == 2 
		&& currentGame.gameBoard[3][4] == 2 && currentGame.gameBoard[4][5] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[2][3] == 2 && currentGame.gameBoard[3][4] == 2 
		&& currentGame.gameBoard[4][5] == 2 && currentGame.gameBoard[5][6] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[0][2] == 2 && currentGame.gameBoard[1][3] == 2 
		&& currentGame.gameBoard[2][4] == 2 && currentGame.gameBoard[3][5] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[1][3] == 2 && currentGame.gameBoard[2][4] == 2 
		&& currentGame.gameBoard[3][5] == 2 && currentGame.gameBoard[4][6] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[0][3] == 2 && currentGame.gameBoard[1][4] == 2 
		&& currentGame.gameBoard[2][5] == 2 && currentGame.gameBoard[3][6] == 2)
			{currentGame.player2Score++;}

	if(currentGame.gameBoard[0][3] == 2 && currentGame.gameBoard[1][2] == 2 
		&& currentGame.gameBoard[2][1] == 2 && currentGame.gameBoard[3][0] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[0][4] == 2 && currentGame.gameBoard[1][3] == 2 
		&& currentGame.gameBoard[2][2] == 2 && currentGame.gameBoard[3][1] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[1][3] == 2 && currentGame.gameBoard[2][2] == 2
		&& currentGame.gameBoard[3][1] == 2 && currentGame.gameBoard[4][0] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[0][5] == 2 && currentGame.gameBoard[1][4] == 2 
		&& currentGame.gameBoard[2][3] == 2 && currentGame.gameBoard[3][2] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[1][4] == 2 && currentGame.gameBoard[2][3] == 2 
		&& currentGame.gameBoard[3][2] == 2 && currentGame.gameBoard[4][1] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[2][3] == 2 && currentGame.gameBoard[3][2] == 2 
		&& currentGame.gameBoard[4][1] == 2 && currentGame.gameBoard[5][0] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[0][6] == 2 && currentGame.gameBoard[1][5] == 2 
		&& currentGame.gameBoard[2][4] == 2 && currentGame.gameBoard[3][3] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[1][5] == 2 && currentGame.gameBoard[2][4] == 2 
		&& currentGame.gameBoard[3][3] == 2 && currentGame.gameBoard[4][2] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[2][4] == 2 && currentGame.gameBoard[3][3] == 2 
		&& currentGame.gameBoard[4][2] == 2 && currentGame.gameBoard[5][1] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[1][6] == 2 && currentGame.gameBoard[2][5] == 2 
		&& currentGame.gameBoard[3][4] == 2 && currentGame.gameBoard[4][3] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[2][5] == 2 && currentGame.gameBoard[3][4] == 2 
		&& currentGame.gameBoard[4][3] == 2 && currentGame.gameBoard[5][2] == 2)
			{currentGame.player2Score++;}
	if(currentGame.gameBoard[2][6] == 2 && currentGame.gameBoard[3][5] == 2 
		&& currentGame.gameBoard[4][4] == 2 && currentGame.gameBoard[5][3] == 2)
			{currentGame.player2Score++;}
}

// INTERACTIVE GAME
void playInteractive(char** command_line) 
{

  char * input = command_line[2];
  char * nextTurn = command_line[3];  
  std::string depth_input = command_line[4]; 
  int depth = std::stoi(depth_input); 
  char compOut[30] = "computer.txt"; 
  char humanOut[30] = "human.txt"; 

  gameStatus currentGame;	 // Declare current game
  printf("\nMaxConnect-4 game\n");


  /* building game state */
  currentGame.depth = depth; 
  currentGame.gameFile = fopen(input, "r");
  printf("Initial game state:\n");
  
  /* populate board model row by row from file */
  char current = 0;
  int i, j;
  if (currentGame.gameFile != 0)
  {
    for(i = 0; i < 6; i++)
    {
		for(j = 0; j < 7; j++)
		{
			do 
			{
			  current = getc(currentGame.gameFile);
			}
			while ((current == ' ') || (current == '\n') || (current == '\r'));

			currentGame.gameBoard[i][j] = current - 48;
			if(currentGame.gameBoard[i][j] > 0)
			{
			  currentGame.pieceCount++;
			}
		}
    }
 
    do 
    {
      current = getc(currentGame.gameFile);
    }
    while ((current == ' ') || (current == '\n') || (current == '\r'));
    
	/* last line of file defines current turn */
    currentGame.currentTurn = current - 48;
    fclose(currentGame.gameFile);
  }

  /* define the players */
  int turn = whosTurn(nextTurn); 
  if(turn == COMPNEXT && currentGame.currentTurn == 1)
  {
		currentGame.computerIsRed == true; 
  }
  else
  {
		currentGame.computerIsRed == false; 
  }

  /* play game */
  while(true)
  {
	  /* display game state each turn */
	  std::cout << "Depth: " << currentGame.depth << std::endl; 
	  printGameBoard(currentGame);
	  countScore(currentGame);
	  printf("Score: RED = %d, GREEN = %d\n\n", currentGame.player1Score, currentGame.player2Score);

	  /* board is full */
	  if(currentGame.pieceCount == 42)
	  {
		printf("\nBOARD FULL\n");
		printf("Game over!\n\n");

		return; 
	  }

	  // computer player next
	  if(turn == COMPNEXT)
	  {

		  /* AI's turn */
		  aiPlay(currentGame);
		  printf("game state after AI move:\n");

		  /* save game state */
		  saveGame(currentGame, compOut);

		  turn = HUMANNEXT; 

	  }

	  // human plays next
	  else
	  {
		  /* humans turn */
		  humanPlay(currentGame); 
		  printf("game state after human move:\n");


		  /* save game state */
		  saveGame(currentGame, humanOut);

		  turn = COMPNEXT; 
	  }

  }
  
}

// ONE MOVE GAME
void playOneMove(char** command_line) 
{

  char * input = command_line[2];
  char * output = command_line [3];
  std::string depth_input = command_line[4]; 
  int depth = std::stoi(depth_input); 

  gameStatus currentGame;	 // Declare current game
  printf("\nMaxConnect-4 game\n");


  /* building game state */
  currentGame.depth = depth; 
  currentGame.gameFile = fopen(input, "r");
  printf("game state before move:\n");
  
  /* populate board model row by row from file */
  char current = 0;
  int i, j;
  if (currentGame.gameFile != 0)
  {
    for(i = 0; i < 6; i++)
    {
		for(j = 0; j < 7; j++)
		{
			do 
			{
			  current = getc(currentGame.gameFile);
			}
			while ((current == ' ') || (current == '\n') || (current == '\r'));

			currentGame.gameBoard[i][j] = current - 48;
			if(currentGame.gameBoard[i][j] > 0)
			{
			  currentGame.pieceCount++;
			}
		}
    }
 
    do 
    {
      current = getc(currentGame.gameFile);
    }
    while ((current == ' ') || (current == '\n') || (current == '\r'));
    
	/* last line of file defines current turn */
    currentGame.currentTurn = current - 48;
    fclose(currentGame.gameFile);
  }

  /* display game state after move */
  printGameBoard(currentGame);
  countScore(currentGame);
  printf("Score: RED = %d, GREEN = %d\n\n", currentGame.player1Score, currentGame.player2Score);

  /* board is full */
  if(currentGame.pieceCount == 42)
  {
    printf("\nBOARD FULL\n");
    printf("Game over!\n\n");

    return; 
  }

  /* AI's turn */
  aiPlay(currentGame);
  printf("game state after move:\n");

  /* display game state after AI's turn */
  printGameBoard(currentGame);
  countScore(currentGame);
  printf("Score: RED = %d, GREEN = %d\n\n", currentGame.player1Score, currentGame.player2Score);
  
  /* save game state to file */
  currentGame.gameFile = fopen(output, "w");
  if (currentGame.gameFile != 0)
  {
    printGameBoardToFile(currentGame);
    fclose(currentGame.gameFile);
  }
  else
  {
    printf("error: could not open output file %s\n", output);
  }
}
