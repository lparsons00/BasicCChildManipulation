//to load a program called “wc” (word count)
//to count file1. file1 is received
//from the command line argument.

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fileCount = 1;
    FILE *fptr;
    char toOpen[20];
    char ch;
    
    printf("Please input file to count:\n");
    scanf("%s", toOpen);

    if ((fptr = fopen(toOpen,"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    ch = fgetc(fptr);
    while (ch != EOF)
    {
        if(ch == ' '){
            fileCount++;
        }
        ch = fgetc(fptr);
    }
    fclose(fptr);
    printf("\nFile Count:%d\n", fileCount);
}