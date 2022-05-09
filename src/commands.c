#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


/********** IMPLEMENTATION OF COMMAND FUNCTIONS **********/

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

/********** HELPER METHODS TO INSTANTIATE COMMAND OBJECTS **********/

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
