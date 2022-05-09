#include "command_objs.h"

#ifndef COMMAND_FUNCS_H
#define COMMAND_FUNCS_H

/********** BUILT-IN COMMAND PROTOTYPES **********/

/*
 * NAME seashell_cd()
 *
 * DESCRIPTION
 *
 * Changes the current working directory to the one given.
*/
int seashell_cd(char **);

/*
 * NAME seashell_help()
 *
 * DESCRIPTION
 *
 * Prints out introduction to shell and the commands that are
 * built into it.
*/
int seashell_help(char **);

/*
 * NAME seashell_exit()
 *
 * DESCRIPTION
 *
 * Exits the shell program.
*/
int seashell_exit(char **);

/*
 * NAME seashell_game()
 *
 * DESCRIPTION
 *
 * Runs a guessing game where the user must guess a number
 * between 1 and 10. They get a maximum of three guesses
 * before failing.
*/
int seashell_game(char **);

/* Array of function pointers for built-in commands. */
cmd_func cmd_funcs[NUM_COMMANDS] = {
  &seashell_cd,
  &seashell_help,
  &seashell_exit,
  &seashell_game
};

#endif // COMMAND_FUNCS_H
