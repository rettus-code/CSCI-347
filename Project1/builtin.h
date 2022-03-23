#ifndef BUILTIN_H
#define BUILTIN_H

/*BuiltIn
* args    args is an array of char*'s that contain a command and the arguments
*that command
*argcp    The count of how many arguments are in args
* returns 1 if it finds a builtin command to run, returns 0 otherwise
*/
int builtIn(char** args, int argcp);
void exitProgram(char** args, int argcp);
void cd(char** args, int argpcp);
void pwd();
void ls(char** args, int argpcp);
int check(char* arg);
void _ls(const char *dir,int op_a,int op_l);
#endif

