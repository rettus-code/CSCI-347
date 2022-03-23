//Michael Rettus


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h> 
#include <unistd.h> 

#define FALSE (0)
#define TRUE  (1)

int main() {
	int tot_chars = 0 ;	/* total characters */
	int tot_lines = 0 ;	/* total lines */
	int tot_words = 0 ;	/* total words */

	/* REPLACE WITH ADDITIONAL VARIABLE DECLARATIONS YOU NEED */
    int ch;
    int prevCh;

	/* REPLACE WITH THE CODE FOR WORD COUNT */

    while ((ch = getchar()) != EOF){
        tot_chars++;
        //if ch = " " checks prevCH to not be " ", "/n", or "-" then tot_words++
        if (ch == 32 && (prevCh != 32 && prevCh != 10  && prevCh != 45)){
            tot_words++;
        };

        /*if ch = "/n" tot_lines++ 
        then checks if prevCh is not " ", "/n", or "-" then tot_words++*/
        if (ch == 10){
            tot_lines++;
            if (prevCh != 32 && prevCh != 10  && prevCh != 45){
                tot_words++;
            };
        };

        //if ch ="-" checks prevCh to not be " ", "/n", or "-" then tot_words++
        if (ch == 45 && (prevCh != 32 && prevCh != 10  && prevCh != 45)){
            tot_words++;
        }

        //holds the char from this iteration into the next iteration 
        prevCh = ch;
    };
    
    printf(" %d  %d %d \n", tot_lines, tot_words, tot_chars);
	return 0 ;
}


