#include "commands.h"

#ifndef CSHELL_H
#define CSHELL_H

/*
 * NAME read_cmd_line()
 *
 * DESCRIPTION
 *    Reads the command line and stores it in string
 *    buffer to be returned.
 *
 * RETURNS
 *    Unparsed String representation of command line.
*/
char *read_cmd_line(void);

/*
 * NAME parse_cmd_line()
 *
 * DESCRIPTION
 *    Parses the command line into distinct String
 *    tokens to be returned.
 *
 * RETURNS
 *    Array containing String tokens of CLI args.
*/
char **parse_cmd_line(char *cmd_line);

/*
 * NAME execute_unix_cmd()
 *
 * DESCRIPTION
 *    Executes Unix process.
 *
 * RETURNS
 *    0 if Unix process was executed sucessfully.
 *    -1 otherwise.
*/
int execute_unix_cmd(char **args);

/*
 * NAME execute_cmds()
 *
 * DESCRIPTION
 *    Executes the commands in the CLI array.
 *
 * RETURNS
 *    0 if commands were executed successfully.
 *    -1 otherwise.
*/
int execute_cmds(char **args);

/*
 * NAME shell_loop()
 *
 * DESCRIPTION
 *    Handles the command loop for the shell.
*/
void shell_loop(void);

#endif // CSHELL_H
