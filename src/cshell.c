#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "cshell.h"

#define MAXARGS 5   // Maximum num of args that a command line input can have
#define MAXLINE 80  // Maximum num of chars that a command line input can have

/* Reads the command line and stores it in string buffer. Returns buffer. */
char *read_cmd_line(void) 
{
  FILE *stream = stdin;
  char *cmd_line = malloc(sizeof(char) * MAXLINE);

  // Reads command line from the standard input and stores it in the cmd_line buffer.
  if (fgets(cmd_line, MAXLINE, stream) == NULL) {
    // If there was an error during execution of fgets, print the error to the standard 
    // error stream and exit.
    if (ferror(stream)) {
      fprintf(stderr, "%s: %s\n", "ReadCmdLine error", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  return cmd_line;
}


/* Parses the command line into distinct argument tokens. 
   Returns those tokens in an array. */
#define STRTOK_DELIMS " \t\r\n\a"
char **parse_cmd_line(char *cmd_line) 
{
  char **args = malloc(sizeof(char*) * (MAXARGS + 1));
  char *token;
  int i = 0;

  // Get pointers to each token in the command line string
  token = strtok(cmd_line, STRTOK_DELIMS);

  while (token != NULL) {
    // Store each token in the array of tokens
    args[i] = token;
    i++;


    // Check that the num of input tokens does not exceed maximum
    if (i > MAXARGS) {
      fprintf(stderr, "%s\n", "Too many args. Max args is 5.");
      exit(EXIT_FAILURE);
    }

    // Get next token
    token = strtok(NULL, STRTOK_DELIMS);
  }

  // NULL terminate the array of tokens
  args[i] = NULL;

  return args;
}

/* Executes Unix command */
int execute_unix_cmd(char **args) 
{
  pid_t pid;

  pid = fork();

  if (pid == 0) {
    // Child process executes command.
    execvp(args[0], args);

    // If child process reaches here, it is not a Unix command.
    printf("Command not found\n");
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
      // Forking error
      perror("Forking error");
  } else {
      // Parent process waits for child process to execute.
      wait(NULL);
  }
  return 1;
}


/* Executes the commands input to the command line. */
int execute_cmds(char **args) 
{
  // If there were no arguments input, do nothing.
  if (args[0] == NULL) {
    return 1;
  }

  int i;

  // Check if the input command is built into the shell.
  for (i = 0; i < NUM_COMMANDS; i++) {
    // If the input command is built into the shell return its execution.
    if (strcmp(args[0], cmd_names[i]) == 0) {
      return (cmd_funcs[i](args));
    }
  }
  // If command is not built into the shell check if it is a Unix command.
  return execute_unix_cmd(args);
}

/* Handles the command loop for the shell. */
void shell_loop(void) {
  char *cmd_line;  // command line buffer
  char **args;     // buffer for command line arguments
  int status;

  while (1) {
    // Print command prompt
    printf("seashell> ");
    // Read the command line
    cmd_line = read_cmd_line();
    // Parse the command line
    args = parse_cmd_line(cmd_line);
    // Execute commands
    status = execute_cmds(args);

    free(cmd_line);
    free(args);

    // Check the status of the execution
    if (!status) break;
  }
}


int main() {
  // Run command loop
  shell_loop();

  return EXIT_SUCCESS;
}
