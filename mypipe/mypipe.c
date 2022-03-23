/*****************************************************************************
*Write a program that executes two commands using a pipe*
*The two commands should be entered by the user as arguments enclosed by " " and separated by |, e.g. ./mypipe "command1 | command2"
*If no arguments are entered by the user, the program will assume command 1 is ls -l and command 2 is sort.
*The correctness of both commands is totally at the discretion of the user                           *
*The program should execute  the commands in pipe and show the output (if any)
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>               /* strsep, etc. */

#define MAX_NUM_ARGS 20           /* Maximum number of arguments allowed */
#define MAX_STR_LEN 200           /* Maximum string length */



int main(int argc, char * argv[])
{
       int fd[2];                 /* Two ends of the pipe */
       char * lhs = NULL;         /* Left hand side command of the pipe */
       char * rhs = NULL;          /* Right hand side command of the pipe */
       char * lhscommand = "ls";  /* Default command name on left hand side of pipe */
       char * rhscommand = "sort"; /* Default command name on right hand side of pipe */
       char * lhsargs[MAX_NUM_ARGS] = { "ls", "-l", NULL };   /* Default LHS args */
       char * rhsargs[MAX_NUM_ARGS] = { "sort", NULL };       /* Default RHS args */
       char * temp[MAX_NUM_ARGS +1];
    
       /*Parse the user input to extract the commands and their arguments*/
       /*Hint: read about strsep(3) */
       if(argc > 1){
              lhsargs[0] = NULL; lhsargs[1] = NULL; rhsargs[0] = NULL;
              lhs = strsep(&argv[1], "|");
              int i = 0;
              /*I use a temp array to hold the values for lhsargs counting up i to put args in
              then counting i down in next loop to fill lhsargs to remove " " in the last index
              with added benefit of setting i back to 0 for rhsargs' while loop. Just to be different*/
              while((temp[i]= strsep(&lhs, " ")) != NULL  && i < 21){
                     i++;}
              i--;        
              while(i > 0){
                     lhsargs[i - 1] = temp[i-1];
                     i--;
              }
              lhscommand = lhsargs[0];
              rhs = strsep(&argv[1], "|");
              strsep(&rhs, " ");
              while((rhsargs[i]= strsep(&rhs, " ")) != NULL && i < 20){
                     i++;}
              rhscommand = rhsargs[0];
       }
       /* Create the pipe */
       if (pipe(fd) == -1){
              printf("error creating pipe");
              return 1;
       }     /* fd[0] is read end, fd[1] is write end */


       /* Do the forking */
       switch ( fork() )
       {
              case 0 : dup2(fd[1], STDOUT_FILENO);
                     close(fd[0]);
                     close(fd[1]);
                     int lhn = execvp(lhscommand, lhsargs);
                     if(lhn == -1){printf("Command %s not found\n", *lhsargs); exit(1); };
              break;
              case -1 : printf ("The child process has not created");
              break;
              /* The LHS of command 'ls -l|sort' i.e. 'ls' should be
               executed in the child. */
              default: dup2(fd[0], STDIN_FILENO);
                     close(fd[0]);
                     close(fd[1]);
                     int rhn = execvp(rhscommand, rhsargs);
                     if(rhn == -1){printf("Command %s not found\n", *rhsargs); exit(1); };
              /*The RHS of command 'ls -l|sort' i.e. 'sort' should be
                executed in the parent. */

       }
       
}
