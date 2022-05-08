#include "command_funcs.h"

#ifndef COMMAND_OBJS_H
#define COMMAND_OBJS_H

/* Define a function pointer for a command function type. */
typedef int (*cmd_func) (char **);

/* Command struct stores info about a built-in command. */
typedef struct Command
{
  char *name;     // Pointer to string reference
  cmd_func func;  // Pointer to function
  char *desc;     // Pointer to description of func
} Command;

/* Array of string references for built in commands. */
char *cmd_names[NUM_COMMANDS] = {
  "cd",
  "help",
  "exit",
  "game"
}

/* Array of function pointers for built in commands. */
int (*cmd_funcs[NUM_COMMANDS]) (char **) = {
  &seashell_cd;
  &seashell_help;
  &seashell_exit;
  &seashell_game
}

/*
 * NAME 
 *    make_cmds
 *
 * DESCRIPTION
 *    Instantiates a Command object for each of the built-in
 *    shell commands which can be then referenced via the 
 *    pointers declared below.
 *
 * RETURNS
 *    0 if all Command objects were successfully instantiated.
 *    -1 if there was a failure.
*/
int make_cmds(void);

/*
 * NAME
 *    destory_cmds
 *
 * DESCRIPTION
 *    Destroys all Command objects for each of the built-in
 *    shell commands.
 *
 * RETURNS
 *    0 if all the Command objects were successfully destroyed.
 *    -1 if there was a failure.
*/
int destroy_cmds(void);

/********** POINTERS TO COMMAND OBJECTS ************/

Command *cmd_cd;

Command *cmd_help;

Command *cmd_exit;

Command *cmd_game;

#endif // COMMAND_OBJS_H
