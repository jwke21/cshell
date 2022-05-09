#ifndef COMMANDS_H
#define COMMANDS_H

#define NUM_COMMANDS 4

#ifndef COMMAND_FUNCS_H
#define COMMAND_FUNCS_H

/********** BUILT-IN COMMAND PROTOTYPES **********/

/* Define a function pointer for a command function type. */
typedef int (*cmd_func) (char **);

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
 *    Prints out introduction to shell and the commands that are
 *    built into it.
*/
int seashell_help(char **);

/*
 * NAME seashell_exit()
 *
 * DESCRIPTION
 *    Exits the shell program.
*/
int seashell_exit(char **);

/*
 * NAME seashell_game()
 *
 * DESCRIPTION
 *    Runs a guessing game where the user must guess a number
 *    between 1 and 10. They get a maximum of three guesses
 *    before failing.
*/
int seashell_game(char **);

/* Array of function pointers for built-in commands. */
cmd_func cmd_funcs[NUM_COMMANDS] = {
  seashell_cd,
  seashell_help,
  seashell_exit,
  seashell_game
};

#endif // COMMAND_FUNCS_H

#ifndef COMMAND_OBJS_H
#define COMMAND_OBJS_H

/* Command struct stores info about a built-in command. */
typedef struct Command
{
  char **name;    // Pointer to string reference
  cmd_func func;  // Pointer to function
  char **desc;    // Pointer to description of func
} Command;

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
*/
void destroy_cmds(void);

/********** POINTERS TO COMMAND OBJECTS ************/

Command *cmd_cd;

Command *cmd_help;

Command *cmd_exit;

Command *cmd_game;

Command *cmds[NUM_COMMANDS] = {
  cmd_cd,
  cmd_help,
  cmd_exit,
  cmd_game
};

#endif // COMMAND_OBJS_H

#endif // COMMANDS_H
