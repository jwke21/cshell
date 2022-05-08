#include <stdlib.h>
#include <string.h>

#include "command_objs.h"

/* Description of cd() function. */
char *desc_cd = "";

/* Description of help() function. */
char *desc_help = "";

/* Description of exit() function. */
char *desc_exit = "";

/* Description of game() function. */
char *desc_game = "";

/********** HELPER METHODS TO INSTANTIATE COMMAND OBJECTS **********/

/* Instantiates cd Command object. */
int make_cd(void) 
{
  cmd_cd = malloc(sizeof(Command)); 

  if (cmd_cd == NULL) return -1;

  /* String reference. */
  char *name = "cd";
  char *cd_name = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(cd_name, name);

  /* Description of command to be used in help(). */
  char *text = 
  "NAME\n"
  "    cd\n\n"
  "DESCRIPTION\n"
  "    Changes the current working directory to the one given.\n\n"
  "USAGE\n"
  "    cd <path/to/dir>\n";

  char *cd_desc = malloc(sizeof(char) * strlen(text) + 1);
  strcpy(cd_desc, text);

  /* Assignment of values Command object. */
  cmd_cd->name = &cd_name;
  cmd_cd->func = &seashell_cd;
  cmd_cd->desc = &cd_desc;

  return 0;
}

/* Destroys cd Command object */
void destroy_cd(void)
{
  free(*cmd_cd->name);
  free(*cmd_cd->desc);
  free(cmd_cd);
}

/* Instantiates help Command object. */
int make_help(void)
{
  cmd_help = malloc(sizeof(Command));

  if (cmd_help == NULL) return -1;

  /* String reference. */
  char *name = "help";
  char *help_name = malloc(sizeof(char) * strlen(help) + 1);
  strcpy(help_name, name);

  /* Description of command to be used in help(). */
  char *text =
  "NAME\n"
  "    help\n\n"
  "DESCRIPTION\n"
  "    Prints out introduction to shell and the commands that are "
  "built into it. If built-in command name is provided, will print "
  "out a description of that command.\n\n"
  "USAGE\n"
  "    help\n"
  "  or"
  "    help <command>\n";
  char *help_desc = malloc(sizeof(char) * strlen(text) + 1);

  /* Assignment of values to Command object. */
  cmd_help->name = &cd_name;
  cmd_help->func = &seashell_help;
  cmd_help->desc = &help_desc;

  return 0;
}

/* Destroys help Command object. */
void destroy_help(void)
{
  free(*cmd_help->name);
  free(*cmd_help->desc);
  free(cmd_help);
}

/* Makes exit Command object. */
int make_exit(void)
{
  cmd_exit = malloc(sizeof(Command));

  if (cmd_exit == NULL) return -1;

  /* String reference. */
  char *name = "exit";
  char *exit_name = malloc(sizeof(char) * strlen(exit) + 1);
  strcpy(exit_name, name);

  /* Description of command to be used in help(). */
  char *text =
  "NAME\n"
  "    exit\n\n"
  "DESCRIPTION\n"
  "    Closes the shell.\n\n"
  "USAGE"
  "    exit\n";
  char *exit_desc = malloc(sizeof(char) * strlen(text) + 1);

  /*Assignment of values to Command object. */
  cmd_exit->name = &exit_name;
  cmd_exit->func = &seashell_exit;
  cmd_exit->desc = &exit_desc;

  return 0;
}

/* Destroys exit command object. */
int destroy_exit(void)
{
  free(*cmd_exit->name);
  free(*cmd_exit->desc);
  free(cmd_exit);
}

/* Makes game Command object */
int make_game(void)
{
  cmd_game = malloc(sizeof(Command));

  if (cmd_game == NULL) return -1;

  /* String reference. */
  char *name = "game";
  char *game_name = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(game_name, name);

  /* Description of command to be used in help(). */
  char *text =
  "NAME\n"
  "    game\n\n"
  "DESCRIPTION\n"
  "    Runs a guessing game where the user must guess a number "
  "between 1 and 10 (inclusive). The player gets three tries to "
  "guess before failue.\n\n"
  "USAGE\n"
  "    game\n";
  char *game_desc = malloc(sizeof(cahar) * strlen(text) + 1);

  /* Assignment of values to Command object. */
  cmd_game->name = &game_name;
  cmd_game->func = &seashell_game;
  cmd_game->desc = &game_desc;

  return 0;
}

/********** FUNCTIONS TO INSTANTIATE COMMAND OBJECTS **********/
int make_cmds(void)
{
  if (
    make_cd() == -1 ||
    make_help() == -1 ||
    make_exit() == -1 ||
    make_game() == -1 ||
  ) {
    return -1;
  }
  
  return 0;
}

void destroy_cmds(void)
{
  destroy_cd();
  destroy_help();
  destroy_exit();
  destroy_game();
}
