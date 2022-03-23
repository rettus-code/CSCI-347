#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "argparse.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define FALSE (0)
#define TRUE  (1)

int argCount(char* line);



/*
* argCount is a helper function that takes in a String and returns the number of "words" in the string assuming that whitespace is the only possible delimeter.
*/
int argCount(char*line)
{
  int i = 0;
  int count = 0;
  int test = 0;
  while(line[i] != '\0') {
    if(line[i] == ' ') {
      i++;
      continue;
    }
    else {
      count++;
      i++;
      while(line[i] != ' ') {
        if(line[i] == '\0') {
          break;
        }
        i++;
      }
    }
  }
  return count;
}



/*
*
* Argparse takes in a String and returns an array of strings from the input.
* The arguments in the String are broken up by whitespaces in the string.
* The count of how many arguments there are is saved in the argcp pointer
*/
char** argparse(char* line, int* argcp)
{
  int i = 0;
  int j = 0;
  *argcp = argCount(line);
  char** returnArray = (char**)malloc((*argcp + 1) * sizeof(char*));
  while(line[i] != '\0') {
      if(line[i] == ' ') {
          i++;
          continue;
      }
      else{
          returnArray[j] = &(line[i]);
          j++; i++;
          while(line[i] != ' ') {
            if(line[i] == '\0') {
                break;
            }
            i++;
          }
          if(line[i] == 0) {
            break;
          }
          line[i] = 0;
          i++;
      }
   }
   returnArray[*argcp] = NULL;
   return returnArray;
}

