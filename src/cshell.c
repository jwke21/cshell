#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXARGS 5 // Maximum num of args that a command line input can have
#define MAXLINE 80 // Maximum num of chars that a command line input can have


// Built in shell commands.
char *commands[] = {
    "cd",
    "help",
    "exit",
    "game"
};


// Constant for the number of shell commands.
const int NUM_COMMANDS = sizeof(commands) / sizeof(commands[0]);


// Cd function.
int Cd(char **input) {
    if (input[1] == NULL) {
        perror("chdir null input argument error\n");
    } else {
        if (chdir(input[1]) != 0) {
        fprintf(stderr, "%s: %s\n", "chdir error", strerror(errno));
        }
    }
    return 1;
}


// Help function.
int Help(char **input) {
    printf("Welcome to my shell!\n");
    printf("The following commands are built in:\n");

    int i;

    for (i=0; i < NUM_COMMANDS; i++) {
        printf("%d : %s\n", i, commands[i]);
    }
    return 1;
}


// Exit function.
int Exit(char **input) {
    return 0;
}


// Game function.
#define GUESS_SIZE MAXLINE
int Game(char **input) {
    int correct_guess_int;
    char correct_guess_str[GUESS_SIZE];
    char user_guess[GUESS_SIZE];

    srand(time(NULL));
    correct_guess_int = rand() % 100;

    while (correct_guess_int == 0 || correct_guess_int == 100) {
        correct_guess_int = rand() % 100;
    }
    snprintf(correct_guess_str, GUESS_SIZE, "%d", correct_guess_int);

    printf("I'm thinking of a number between 0 and 100! Enter your guess: ");
    if (fgets(user_guess, GUESS_SIZE, stdin) == NULL) {
        perror("Invalid guess.");
    }

    if (strcmp(correct_guess_str, user_guess) == 0) {
        printf("WOW! You got it, Congrats!\n");
    } else {
        printf("Nope! Maybe next time\n");
    }

    return 1;
}


// Array of command function pointers.
int (*command_functions[])(char **) = {
    &Cd,
    &Help,
    &Exit,
    &Game
};


// Reads the command line and stores it in string buffer. Returns buffer.
char *ReadCmdLine(void) {
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


// Parses the command line into distinct argument tokens. Returns those tokens in an array.
#define STRTOK_DELIMS " \t\r\n\a"
char **ParseCmdLine(char *cmd_line) {
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


// Execute Unix command
int ExecuteUnixCmd(char **args) {
    int status;
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


// Executes the commands input to the command line.
int ExecuteCmds(char **args) {
    // If there were no arguments input, do nothing.
    if (args[0] == NULL) {
        return 1;
    }

    int i;

    // Check if the input command is built into the shell.
    for (i = 0; i < NUM_COMMANDS; i++) {
        // If the input command is built into the shell return its execution.
        if (strcmp(args[0], commands[i]) == 0) {
        return (command_functions[i](args));
        }
    }
    // If command is not built into the shell check if it is a Unix command.
    return ExecuteUnixCmd(args);
}


// Runs the command loop for the shell.
void ShellLoop(void) {
    char *cmd_line; // command line buffer
    char **args; // buffer for command line arguments
    int status;

    while (1) {
        // Print command prompt
        printf("k-sea-shell> ");
        // Read the command line
        cmd_line = ReadCmdLine();
        // Parse the command line
        args = ParseCmdLine(cmd_line);
        // Execute commands
        status = ExecuteCmds(args);

        free(cmd_line);
        free(args);

        // Check the status of the execution
        if (!status) break;
    }
}


int main() {
    // Run command loop
    ShellLoop();

    return EXIT_SUCCESS;
}
