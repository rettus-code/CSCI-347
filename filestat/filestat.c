#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    
    mode_t file_perm;          /* File permissions */
    struct stat file_details;  /* Detailed file info */
   
        
    /* Retrieve the file details */
   //write your code here

    stat(argv[1], &file_details);
    /* Get the file type */
    //write your code here

    if(S_ISDIR(file_details.st_mode)){
        printf("%s", "File type: Directory\n");
    }
    else if(S_ISREG(file_details.st_mode)){
        printf("%s", "File type: Regular\n");
    }
    else if(S_ISCHR(file_details.st_mode)){
        printf("%s", "File type: Character special file\n");
    }
    else if(S_ISBLK(file_details.st_mode)){
        printf("%s", "File type: Block special file\n");
    }
    else if(S_ISFIFO(file_details.st_mode)){
        printf("%s", "File type: Pipe or FIFO\n");
    }
    else if(S_ISLNK(file_details.st_mode)){
        printf("%s", "File type: Symbolic link\n");
    }
    else if(S_ISSOCK(file_details.st_mode)){
        printf("%s", "File type: Socket\n");
    }
    /* Get the time of last access of the file */
        
    //write your code here
    char accessTime[30];
    strftime(accessTime, 30, "%a %b %d %H:%M:%S %Y", localtime(&(file_details.st_atim.tv_sec)));
    printf ("Time of last access: %s\n", accessTime);
    /* Get the file permissions */
    printf("File Permissions:\n");
    //write your code here
    char *read;
    char *write;
    char *ex;
    if(file_details.st_mode & S_IRUSR)              
        read = "Readable";
    else
        read = "Not readable, ";     
    if(file_details.st_mode & S_IWUSR)
        write = "Writable, ";
    else
        write = "Not writable, ";  
    if(file_details.st_mode & S_IXUSR)
        ex = "Executable";
    else
        ex = "Not executable";
    printf("User : %s, %s, %s\n", read, write, ex);
    if(file_details.st_mode & S_IRGRP)  
        read = "Readable";        
    else
        read = "Not readable, ";     
    if(file_details.st_mode & S_IWGRP)
        write = "Writable, ";
    else
        write = "Not writable, ";  
    if(file_details.st_mode & S_IXGRP)
        ex = "Executable";
    else
        ex = "Not executable";
    printf("Group : %s, %s, %s\n", read, write, ex);
        if(file_details.st_mode & S_IROTH)              
        read = "Readable";
    else
        read = "Not readable, ";     
    if(file_details.st_mode & S_IWOTH)
        write = "Writable, ";
    else
        write = "Not writable, ";  
    if(file_details.st_mode & S_IXOTH)
        ex = "Executable";
    else
        ex = "Not executable";
    printf("Other : %s, %s, %s\n", read, write, ex);
    
    /*EXTRA CREDIT*/
    printf("\n \n EXTRA CREDIT...\n");
    printf( "File name = %s\n", argv[1]);
    printf("File path = %s\n", realpath(".", argv[1]));
    printf("i-node = %li, device number = %li, links = %li\n", file_details.st_ino, file_details.st_dev, file_details.st_nlink);
    printf("user id = %i, group id = %i, size in bytes = %li\n", file_details.st_uid, file_details.st_gid, file_details.st_size);
    char modTime[30];
    char statTime[30];
    strftime(modTime, 30, "%a %b %d %H:%M:%S %Y", localtime(&(file_details.st_mtim.tv_sec)));
    strftime(statTime, 30, "%a %b %d %H:%M:%S %Y", localtime(&(file_details.st_ctim.tv_sec)));
    printf ("Time of last modification: %s\n", modTime);
    printf ("Time of last file status change: %s\n", statTime);
    printf("best I/O block size = %li, number of disk blocks allocated = %li\n", file_details.st_blksize, file_details.st_blocks);
    return 0;
}
