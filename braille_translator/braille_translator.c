/**
 * Name:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR (30)
typedef enum {false, true} bool;
FILE *in_file;
FILE *out_file;
size_t string;
char * buffer;
long int res;


//int charholder[MAX_CHAR];


/*This method will write the Braille letters either horizontally or vertically
 to the output_file.
 
 @param braille_line: an array of int arrays(Braille letters).
 @param length: length of braille_line, number of Braille letters in line.
 
 @return 1 on success, -1 if an error occurs*/
int write_braille_to_file(int **braille_line, int length)
{   int line_manage = res/60;
    int remain = res%60;
    out_file = fopen("outfile.txt", "w");
    for (int j = 0; j <= line_manage - 1; j++){
         
        for (int i = 0; i < 60; i++){
            if (braille_line[i+j*60][0] != 9){
                int ch1 = braille_line[i+j*60][0];
                int ch2 = braille_line[i+j*60][1];
                fprintf(out_file, "%d", ch1);
                fprintf(out_file, "%d", ch2);
                fputc(' ', out_file);
            }
        }
        fputc('\n', out_file);
        for (int i = 0; i < 60; i++){
            if (braille_line[i+j*60][0] != 9){
                int ch1 = braille_line[i+j*60][2];
                int ch2 = braille_line[i+j*60][3];
                fprintf(out_file, "%d", ch1);
                fprintf(out_file, "%d", ch2);
                fputc(' ', out_file);
            }
        }
        fputc('\n', out_file);
        for (int i = 0; i < 60; i++){
            if (braille_line[i+j*60][0] != 9){
                int ch1 = braille_line[i+j*60][4];
                int ch2 = braille_line[i+j*60][5];
                fprintf(out_file, "%d", ch1);
                fprintf(out_file, "%d", ch2);
                fputc(' ', out_file);
            }
        }
        fputc('\n', out_file);
        fputc('\n', out_file);
    }
    
        for (int i = 0; i < remain; i++){
            if (braille_line[i+line_manage*60][0] != 9){
                int ch1 = braille_line[i +line_manage*60][0];
                int ch2 = braille_line[i +line_manage*60][1];
                fprintf(out_file, "%d", ch1);
                fprintf(out_file, "%d", ch2);
                fputc(' ', out_file);
            }
        }
        fputc('\n', out_file);
        for (int i = 0; i < remain; i++){
            if (braille_line[i+line_manage*60][0] != 9){
                int ch1 = braille_line[i +line_manage*60][2];
                int ch2 = braille_line[i +line_manage*60][3];
                fprintf(out_file, "%d", ch1);
                fprintf(out_file, "%d", ch2);
                fputc(' ', out_file);
            }
        }
        fputc('\n', out_file);
        for (int i = 0; i < remain; i++){
            if (braille_line[i+line_manage*60][0] != 9){
                int ch1 = braille_line[i +line_manage*60][4];
                int ch2 = braille_line[i +line_manage*60][5];
                fprintf(out_file, "%d", ch1);
                fprintf(out_file, "%d", ch2);
                fputc(' ', out_file);
            }
        }
        fputc('\n', out_file);

    
    return 1;
}

/*This method translates an ASCII char to an array of 6 ints(a Brailler letter):
 0 3
 1 4
 2 5
 
 @param letter: the ASCII char to be translated.
 
 @return an int* that represents a Braille char, or NULL if that char is invalid.*/
int *ASCII_to_braille(char letter)
{   
    int *brailleLetter;
    brailleLetter = (int*) malloc (sizeof(int) * 6);
    if (letter == 32){
        printf("%c", letter);
        for (int i = 0; i < 6; i++){
            brailleLetter[i] = 0;
        }
        return brailleLetter;
    }
    if (!((letter > 96 && letter < 123) || (letter > 64 && letter < 91) || (letter > 47 && letter < 58))){
            brailleLetter[0] = 9;
            return brailleLetter;
        }
    if (letter > 96 && letter < 123){
        printf("%c", letter);
        letter -= 97;
    }
    if (letter > 64 && letter < 91){
        printf("%c", letter);
        letter -= 65;
    }
    if (letter > 48 && letter < 58){
        printf("%c", letter);
        letter -= 49;
    }
    if (letter == 48){
        printf("%c", letter);
        brailleLetter[0] = 0; brailleLetter[1] = 1; brailleLetter[2] = 1; 
        brailleLetter[3] = 1; brailleLetter[4] = 0; brailleLetter[5] = 0;
        return brailleLetter;
    }
    if (letter == 22){
        brailleLetter[0] = 0; brailleLetter[1] = 1; brailleLetter[2] = 1; 
        brailleLetter[3] = 1; brailleLetter[4] = 0; brailleLetter[5] = 1;
        return brailleLetter;
    }
    if (letter >21){
        letter -= 1;
    }
    int remain = letter%10;
    switch (remain){
        case 1 :
            brailleLetter[0] = 1; brailleLetter[1] = 0; brailleLetter[2] = 1; brailleLetter[3] = 0;
            break;
        case 2 :
            brailleLetter[0] = 1; brailleLetter[1] = 1; brailleLetter[2] = 0; brailleLetter[3] = 0;
            break;
        case 3 :
            brailleLetter[0] = 1; brailleLetter[1] = 1; brailleLetter[2] = 0; brailleLetter[3] = 1;
            break;
        case 4 :
            brailleLetter[0] = 1; brailleLetter[1] = 0; brailleLetter[2] = 0; brailleLetter[3] = 1;
            break;
        case 5 :
            brailleLetter[0] = 1; brailleLetter[1] = 1; brailleLetter[2] = 1; brailleLetter[3] = 0;
            break;
        case 6 :
            brailleLetter[0] = 1; brailleLetter[1] = 1; brailleLetter[2] = 1; brailleLetter[3] = 1;
            break;
        case 7 :
            brailleLetter[0] = 1; brailleLetter[1] = 0; brailleLetter[2] = 1; brailleLetter[3] = 1;
            break;
        case 8 :
            brailleLetter[0] = 0; brailleLetter[1] = 1; brailleLetter[2] = 1; brailleLetter[3] = 0;
            break;
        case 9 :
            brailleLetter[0] = 0; brailleLetter[1] = 1; brailleLetter[2] = 1; brailleLetter[3] = 1;
            break;
        case 0 :
            brailleLetter[0] = 1; brailleLetter[1] = 0; brailleLetter[2] = 0; brailleLetter[3] = 0;
            break;
    }
    int decade = letter/10;
    if (decade == 0){
        brailleLetter[4] = 0; brailleLetter[5] = 0;
    }
    if (decade == 1){
        brailleLetter[4] = 1; brailleLetter[5] = 0;
    }
    if (decade == 2){
        brailleLetter[4] = 1; brailleLetter[5] = 1;
    }
    
    return brailleLetter;
}

/*This method reads from in_file up to MAX_CHAR per call to fread(), then builds an 
 array of Braille letters by calling ASCII_to_braille(). It will write the Braille
 to out_file by calling write_braille_to_file().
 
 @return 1 on success, and -1 if an error occurs.*/
int translate_to_braille(char* fileName)
{   
    int multi = res/MAX_CHAR;
    int remainder = res%MAX_CHAR;
    int **brailleCarrier;
    brailleCarrier = (int**) malloc (sizeof(int*) * res);
    in_file = fopen(fileName, "r");
    int *braille;
    
    int i = 0;
    while (i < res){
        buffer = (char*) malloc (sizeof(char) * MAX_CHAR);
        if (buffer == NULL) 
            {fputs ("Memory error",stderr); return -1;}
        string = fread(buffer, 1, MAX_CHAR, in_file);
        if (i > multi * 30 -1) {
            for (int j = 0; j< remainder; ++j){
                brailleCarrier[i+j] = (int*) malloc (sizeof(int) * 6);
                braille= (int*) malloc (sizeof(int) * 6);
                braille = ASCII_to_braille(buffer[j]);
                for (int k = 0; k < 6; k++){
                    brailleCarrier[j+i][k] = braille[k];
                }
                memset(braille, 0, 6);
            }
        } else {
            for (int j = 0; j<MAX_CHAR; ++j){
                brailleCarrier[i+j] = (int*) malloc (sizeof(int) * 6);
                braille = ASCII_to_braille(buffer[j]);
                for (int k = 0; k < 6; k++){
                    brailleCarrier[j+i][k] = braille[k];
                }
            }
        }
        i += 30;
        memset(buffer, 0, MAX_CHAR);
        
    }
    write_braille_to_file( brailleCarrier, 6); 
    return 1;
}


/*The program should validate that only one argument was supplied, and that it opens
 a valid file. The in_file will be translated from ASCII to Braille. It will create 
 the output file, and call translate_to_braille().

 The program should output the translation to a file named in_file.txt.output.
 e.g.: in_file: some_text.txt 
       out_file: some_text.txt.output
 
 @return 0 on success, and a 1 on error, exiting.*/
int main(int argc, char **argv)
{
    if (argc != 2){
        printf("./braille <src_file_name>");
        return 0;
    }
    in_file = fopen("reading.txt", "r");
    if(NULL == in_file)
    {
        printf("\n fopen() Error!!! in_file\n");
        return 1;
    }
    fseek(in_file, 0L, SEEK_END);
    res = ftell(in_file);
    printf("%ld", res);
    out_file = fopen("outfile.txt", "w");
    if(NULL == out_file)
    {
        printf("\n fopen() Error out_file!!!\n");
        return 1;
    }
    translate_to_braille(argv[1]);
    fclose(in_file);
    fclose(out_file);
    return 0;
}
