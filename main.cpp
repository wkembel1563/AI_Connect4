#include "maxconnect4.h"

int main(int argc, char ** argv)
{
  validate(argc, argv); 

  char** command_line = argv; 

  char * game_mode = command_line [1];

  /* determining game mode */
  if (strcmp(game_mode, "interactive") == 0)
  {
	playInteractive(command_line); 
	return 0; 
  }
  else if (strcmp (game_mode, "one-move") == 0)
  {
	playOneMove(command_line); 
  }
  else
  {
    printf("%s is an unrecognized game mode\n", game_mode);
	exit(1); 
  }


  return 0;
}
