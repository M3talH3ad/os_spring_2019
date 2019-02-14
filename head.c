/*
Author: Siddharth Sharma
Course: CS-GY 6223 Spring 2019
Instructor: Kamen Yotov
Assignment: 1
*/

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[2048];

void head(int fd, int numLines)
{
    int index, bytes_read;
    int l = 0;
    
    bytes_read = read(fd,buf,sizeof(buf));

    while ((bytes_read > 0) && (l < numLines))
    {
        for (index = 0;l < numLines; index++)
        {
            if (buf[index] == '\n')
            {
                printf(1, "\n");
                l++;
            }
            else
            {
                printf(1,"%c",buf[index]);
            }
        }
    }

    if (bytes_read < 0)
    {
        printf(1, "Error: Cannot read the given file \n");
        exit();
    }

}

int fileChecker(char *fp){
    int fd;
    if((fd = open(fp, 0)) < 0){
        printf(1, "head: cannot open the file %s\n", fp);
        close(fd);
        return 0;
    }
    close(fd);
    return 1;
}


int main(int argc, char *argv[])
{
    int fd;
    int decider;
    int defaultLinesToRead = 10;

    if(argc <= 1){
        head(0, defaultLinesToRead);
        exit();
    }


    else if (argc == 2)
    {
        char lineNumber[256];
        strcpy(lineNumber, argv[1]);

        if (argv[1][0] == '-')
        {
            char *ptr = lineNumber;
            ptr += 1;
            int numLines = atoi(ptr);

            if (numLines == 0 && ptr[0] != '0'){
                printf(1, "Usage: head [-][number of lines] [file path]\n");
                exit();
            }
            head(0, numLines);
            exit();
        }

        decider=fileChecker(argv[1]);
        if(decider == 0){
            printf(1, "Usage: head [-][number of lines] [file path]\n");
            exit();
        }
        fd = open(argv[1], 0);  
        head(fd, defaultLinesToRead);
        close(fd);
    }

    else if (argc == 3)
    {
        char lineNumber[256];
        strcpy(lineNumber, argv[1]);
        
        if (argv[1][0] == '-')
        {
            char *ptr = lineNumber;
            ptr += 1;
            int numLines = atoi(ptr);

            decider=fileChecker(argv[2]);
            
            if(decider == 0){
                printf(1, "Usage: head [-][number of lines] [file path]\n");
                exit();
            }
            fd = open(argv[2], 0);

            head(fd,numLines);
            close(fd);
        }
        else
        {
            printf(1, "Usage: head [-][number of lines] [file path]\n");
            exit();
        }
    }
    else
    {
        printf(1, "Usage: head [-][number of lines] [file path]\n");
    }

    exit();
}