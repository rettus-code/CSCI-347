#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include "builtin.h"
#include <string.h>
#include <dirent.h> 

#define GREEN  "\x1B[32m"
#define CYAN  "\e[0;36m"
#define YEL "\e[0;33m"
//Prototypes
void exitProgram(char** args, int argcp);
void cd(char** args, int argpcp);
void pwd();
char *get_current_dir_name(void);
int check(char* arg);
void _ls(const char *dir,int op_a,int op_l);

/* builtIn
 ** built in checks each built in command the given command, if the given command
 * matches one of the built in commands, that command is called and builtin returns 1.
 *If none of the built in commands match the wanted command, builtin returns 0;
  */
int builtIn(char** args, int argcp)
{
    if (strcmp(args[0], "pwd") == 0){
      pwd();
      return 1;
  } else if (strcmp(args[0], "exit") == 0){
      exitProgram(args, argcp);
      return 1;
  } else if (strcmp(args[0], "cd") == 0){
      cd(args, argcp);
      return 1;
  } else if (strcmp(args[0], "_ls") == 0){
    if (argcp == 1){
		  _ls(".",0,0);
      return 1;
	  } else if (argcp == 2) {
      if (args[1][0] == '-') {
        int op_a = 0, op_l = 0;
        char *p = (char*)(args[1] + 1);
        while(*p){
          if(*p == 'a') op_a = 1;
          else if(*p == 'l') op_l = 1;
          else{
            perror("Option not available");
            exit(EXIT_FAILURE);
          }
          p++;
        }
        _ls(".",op_a,op_l);
        return 1;
      }
    }
  }
  printf("Use the following commands:\n pwd - print current directory\n");
  printf("exit [value] - exit the shell with the value\n cd - change the current directory\n");
  printf("_ls - lists file and directories in pwd\n");
  return 0;
}
int check(char* arg) {
  int returnable = 0;
  if (strcmp(arg, "pwd") == 0)
    returnable = 1;
  if (strcmp(arg, "exit") == 0)
    returnable = 1;
  if (strcmp(arg, "cd") == 0)
    returnable = 1;
  if (strcmp(arg, "_ls") == 0)
    returnable = 1;
  return returnable;
}
void exitProgram(char** args, int argcp)
{   
    if (argcp == 1) {
      free(*args);
      free(args);
      exit(0);
    }
    exit(atoi(args[1]));
}

void pwd()
{
  char * cwd = get_current_dir_name();
  printf("you are currently in: %s%s \n",YEL, cwd);
  free(cwd);
}

void cd(char** args, int argcp)
{
  char s[512];
  printf("%s\n", getcwd(s, 512));
  if (chdir(args[1]) == -1){
    printf("directory does not exist");
  }
  printf("%s\n", getcwd(s, 512));
}

void _ls(const char *dir,int op_a,int op_l)
{
  struct dirent * dirs;
  DIR * directory = opendir(dir);
  if(!directory){
		if (errno = ENOENT)
		{
			//If the directory is not found
			perror("Directory doesn't exist");
		}
		else
		{
			//If the directory is not readable then throw error and exit
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}
  pwd();
  while ((dirs = readdir(directory)) != NULL)
    {
      if (!op_a && dirs->d_name[0] == '.')
			  continue;
      if(dirs-> d_type != DT_DIR){
		    printf("%s%s  ",CYAN, dirs->d_name);
      } else if(dirs -> d_type == DT_DIR && strcmp(dirs->d_name,".")!=0 && strcmp(dirs->d_name,"..")!=0 ){
        printf("%s%s  ",GREEN, dirs->d_name);
        
      }
		  if(op_l) printf("\n");
    }
    closedir(directory);
    printf("\n");
}

