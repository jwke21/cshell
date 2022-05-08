#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "command_funcs.h"

/* seashell_cd() function. */
int seashell_cd(char **args)
{
  // Check that dir path was provided.
  if (args[1] == NULL) {
    fprintf(stderr, "correct usage: cd <path/to/file>");
  } else {
    // Check that chdir command executes successfully.
    if (chdir(args[1]) == -1) {
      perror("seashell: ");
    }
  }
  return 1;
}

/* seashell_help() function. */
int seashell_help(char **args)
{
  int i;

  /* If user did not pass in command as option. */
  if (args[1] == NULL) {
    printf("Welcome to my shell!\n");
    printf("The following commands are built in:\n");
    
    for (i = 0; i < NUM_COMMANDS; i++) {
      printf("%d : %s\n", i + 1, commands[i]);
    }
    printf("\n");

    printf("To see what a command does type:\n");
    printf("    help <command>\n");
    
    return 1;
  }

  /* Check that user passed in valid option. */
  for (i = 0; i < NUM_COMMANDS; i++) {
    if (strcmp(args[1], cmd_names[i]) == 0) {
      // TODO: CREATE ARRAY OF COMMAND STRUCTS ON HEAP
      printf("%s\n", *cmds[i]->desc);
      return 0;
    }
  }

  /* Inform user that command is not recognized. */
  printf("%s is not a recognized built-in shell command.\n", args[1]);
  printf("Use 'help' command with no options to see list of valid commands");

  return 1;
}

/* seashell_exit() function. */
int seashell_exit(char **args)
{
  return 0;
}

/* seashell_game() function. */
int seashell_game(char **args)
{
  const int MAX_GUESS_LEN = 3;
  int correct_guess_int, num_guesses;
  char correct_guess_str[MAX_GUESS_LEN];
  char user_guess[MAX_GUESS_LEN];

  srand(time(NULL));  // Set the rand with current time as seed
  correct_guess_int = rand() % 10;  // Get number between 1-10 (inclusive)
  if (correct_guess_int = 0) {
    correct_guess_int = 10;
  }

  snprintf(correct_guess_str, "%d", correct_guess_int);

  num_guesses = 3;
  printf("I'm thinking of a number between 1 and 10 (inclusive)...\n");
  while (num_guesses > 0) {
    printf("Enter your guess: ");

    // Error check
    if (fgets(user_guess, MAX_GUESS_LEN, stdin) == NULL) {
      perror("seashell");
    }
    
    if (strcmp(correct_guess_str, user_guess) == 0) {
      printf("WOW! You got it! Congratulations!\n");
      num_guesses = 0;
    } else if ((num_guesses - 1) == 0) {
      printf("Nope! Sorry you're out of guesses, better luck next time!\n");
    } else {
      printf("Nope! Try again!\n");
    }

    num_guesses--;
  }

  return 1;
}
