#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Array of string references for built in commands.
char *commands[] = {
  "cd",
  "help",
  "exit",
  "game"
};

// Constant for the number of commands built into cshell.
const int NUM_COMMANDS = sizeof(commands) / sizeof(commands[0]);

// Cd function.
int Cd(char **args) {
  if (input[1] == NULL){
    perror("chdir null input argument error");
  } else {
    if (chdir(input[1]) != 0) {
      perror("chdir error");
    }
  }
  return 1;
}

// Help function.
int Help(char **args) {
  int i;

  printf("Welcome to my shell!\n");
  printf("The following commands are built in:\n");

  for (i=0; i < NUM_COMMANDS; i++) {
    printf("%d : %s\n", i, commands[i]);
  }

  return 1;
}

// Exit function.
int Exit(char **args) {
  return 0;
}

// Game function.
#define GUESS_BUFFER_SIZE 100
int Game(char **input) {
  int correct_guess_int;
  char correct_guess_str[GUESS_BUFFER_SIZE];
  char user_guess[GUESS_SIZE];

  srand(time(NULL));
  correct_guess_int = rand() % 10;

  while (correct_guess_int == 0 || correct_guess_int == 10) {
    correct_guess_int = rand() % 10;
  }

  snprintf(correct_guess_str, GUESS_BUFFER_SIZE, "%d", correct_guess_int);

  printf("I'm thinking of a number between 0 and 10 (exclusive)! Enter your guess: ")

  if (fgets(user_guess, GUESS_BUFFER_SIZE, stdin) == NULL) {
    perror("Invalid guess")
  }

  if (strcmp(correct_guess_str, user_guess) == 0) {
    printf("WOW! You got it, Congrats!\n")
  } else {
    printf("Nope! Maybe next time!\n")
  }

  return 1;
}

// Array of pointers to functions associated with built in cshell commands.
int (*command_functions[])(char **) = {
  &Cd,
  &Help,
  &Exit,
  &Game
};


