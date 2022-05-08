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

/********** INSTANTIATION OF COMMAND OBJECTS **********/

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
  char * name = "help";
  
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
}

/* Destroys help Command object. */
int destroy_help(void)
{
  free(*cmd_help->name);
  free(*cmd_help->desc);
  free(cmd_help);
}


