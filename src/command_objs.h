#include "command_funcs.h"

#ifndef COMMAND_OBJS_H
#define COMMAND_OBJS_H

/* Command struct stores info about a built-in command. */
typedef struct Command
{
  char *cmd_name;            // Pointer to string reference
  int (*cmd_func) (char **); // Pointer to function
  char **help_desc;          // Pointer to description of func
}

/* Array of string references for built in commands. */
char *command_names[NUM_COMMANDS] = {
  "cd",
  "help",
  "exit",
  "game"
}

/* Array of function pointers for built in commands. */
int (*command_funcs[]) (char **) = {
  &seashell_cd;
  &seashell_help;
  &seashell_exit;
  &seashell_game
}

#endif // COMMAND_OBJS_H
