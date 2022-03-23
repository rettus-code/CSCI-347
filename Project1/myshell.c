/* CS 347 -- Mini Shell!
 * Original author Phil Nelson 2000
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include "argparse.h"
#include "builtin.h"


/* PROTOTYPES */

void processline (char *line);
char** argparse(char* line, int* argcp);
ssize_t getinput(char** line, size_t* size);
ssize_t testinput();
int argCount(char* line);

/* main
 * This function is the main entry point to the program.  This is essentially
 * the primary read-eval-print loop of the command interpreter.
 */

int main () {

 //write your code
 while(1) {
    char* buffer;
    size_t size = 0;
    int bytesRead = getinput(&buffer, &size); 
    if(buffer[bytesRead - 1] == '\n')
      buffer[bytesRead - 1] = 0;
    processline(buffer);
 }
 return EXIT_SUCCESS;
}


/* getinput
* line     A pointer to a char* that points at a buffer of size *size or NULL.
* size     The size of the buffer *line or 0 if *line is NULL.
* returns  The length of the string stored in *line.
*
* This function prompts the user for input.  If the input fits in the buffer
* pointed to by *line, the input is placed in *line.  However, if there is not
* enough room in *line, *line is freed and a new buffer of adequate space is
* allocated.  The number of bytes allocated is stored in *size.
*/
ssize_t getinput(char** line, size_t* size) {
  assert(line != NULL && size != NULL);
  errno = 0;
  //print the prompt e.g. %myshell%
  printf("myshell: ");
  ssize_t len = getline(line, size, stdin);
  if(len < 0)
    printf("Error: Invalid Input");
  return len;
}


/* processline
 * The parameter line is interpreted as a command name.  This function creates a
 * new process that executes that command.
 * Note the three cases of the switch: fork failed, fork succeeded and this is
 * the child, fork succeeded and this is the parent (see fork(2)).
 * processline only forks when the line is not empty, and the line is not trying to run a built in command
 */
void processline (char *line)
{
 /*check whether line is empty*/
    if(strlen(line) == 0)
      return;
    
    pid_t  pid;
    int    status;
    int noOfArgs = 0;
    /* Start a new process to do the job. */
    char** arguments = argparse(line, &noOfArgs);
    if(check(arguments[0])) {
      builtIn(arguments, noOfArgs);
    }
    else {
      pid = fork();
      if (pid < 0) {
        /* Fork wasn't successful */
        perror ("fork");
        return;
      }
      
      /* Check for who we are! */
      if (pid ==  0) {
        /* We are the child! */
        execvp(arguments[0], arguments);
        perror ("exec");
        fclose(stdin);
        exit (0);
      }
      /* Have the parent wait for child to complete */
      if (pid > 0) {
        wait(&status);
      }
    }
    free(*arguments);
    free(arguments);
}

