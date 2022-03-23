/*
 * Implementation of functions that find values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h>
 *****
 */

#include <stdlib.h>
#include <stdbool.h>

#include "find.h"

#define NOT_FOUND (-1)	// integer indicator for not found.

/*
 * Return the index of the first occurrence of <ch> in <string>,
 * or (-1) if the <ch> is not in <string>.
 */
int find_ch_index(char string[], char ch) {
	int length = sizeof(string) / sizeof(string[0]);
	for(int i = 0; i < length; i++){
		if(ch == string[i]){
			return i;
		}
	}
	return -1;
}

/*
 * Return a pointer to the first occurrence of <ch> in <string>,
 * or NULL if the <ch> is not in <string>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_ch_ptr(char *string, char ch) {
	while (*string){
		if (*string == ch){
			return string;
		} else {
			string++;
		}
	}
	return NULL;
}

/*
 * Return the index of the first occurrence of any character in <stop>
 * in the given <string>, or (-1) if the <string> contains no character
 * in <stop>.
 */
int find_any_index(char string[], char stop[]) {
	char ch;
	int count = 0;

	while(*string){
		ch = *string++;
		for(int j = 0; j < sizeof(stop); j++){
			if(ch == stop[j])
				return count;
		}
		count++;
	}
	return -1;

}

/*
 * Return a pointer to the first occurrence of any character in <stop>
 * in the given <string> or NULL if the <string> contains no characters
 * in <stop>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_any_ptr(char *string, char* stop) {
	char *holdptr = stop;
	while (*string){
		while(*holdptr){
			if (*string == *holdptr++){
				return string;
			}
		}
		holdptr = stop;
		*string++;
	}
	return NULL ;
}

/*
 * Return a pointer to the first character of the first occurrence of
 * <substr> in the given <string> or NULL if <substr> is not a substring
 * of <string>.
 * Note: An empty <substr> ("") matches *any* <string> at the <string>'s
 * start.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_substr(char *string, char* substr) {
	char *tempstring = string;
	char *tempsub = substr;
	if (!*substr) {
		return string;
	}
	while(*string){
		if(*tempstring++ == *tempsub++ && *tempstring++ == *tempsub++ 
		&& *tempstring++ == *tempsub++) 
			return string;
		*string++;
		tempstring = string;
		tempsub = substr;
	}


	return NULL ;	// placeholder
}
