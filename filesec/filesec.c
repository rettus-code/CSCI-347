#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    //Check for the correctness of the entered command. If it is incorrect, display a usage message
    //write your code here

    char outputFile[128];
    char* command = argv[1];
    char* file = argv[2];
    if (argc == 3){
        if (strcmp(argv[1], "-e") == 0)
        {
            int pFile = open(file, O_RDONLY);
            strcat(outputFile, file);
            strcpy(outputFile, ".");
            strcpy(outputFile, "_enc.txt");

            //encrypt the contents of the input file and save the results in the output file. Do not forget to create the output file
            //write your code here
            char name[9];
            for(int i = 0; i<9; i++){
                name[i] = file[i];
            }
            char *newFile = name;
            int enc = open(newFile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            int i = 0;

            while(read(pFile, &outputFile[i], 1) == 1){
                outputFile[i] += 100;
                write(enc, &outputFile[i], 1);
                i++;
            }

            //close the files
            //write your code here
            close(enc);

            return 0;
        }

        if (strcmp(argv[1], "-d") == 0)
        {
            int pFile = open(file, O_RDONLY);
            //create and open the output file
            //write your code here
            strcat(outputFile, file);
            strcpy(outputFile, ".");
            strcpy(outputFile, "_dec.txt");
            char name[9];
            for(int i = 0; i<9; i++){
                name[i] = file[i];
            }
            char *newFile = name;
            int dec = open(newFile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

            //decrypt the contents of the input file and save the results in the output file
            //write your code here
            int i = 0;

            while(read(pFile, &outputFile[i], 1) == 1){
                outputFile[i] -= 100;
                write(dec, &outputFile[i], 1);
                i++;
            }
            //close the files
            //write your code here
            close(dec);
            return 0;
            
        }
    }
    printf("./filesec -e|-d [filename]\n");
}

