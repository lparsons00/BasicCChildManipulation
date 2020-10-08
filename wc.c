#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[] ){
    printf("I am wc.c called by execvp()\n"); 
    FILE *fPtr;
    char path[20]; 
	strcpy(path, argv[1]);
    int wordCount = 1;
    char c;
    
	
    fPtr = fopen(path, "r");
    while((c = fgetc(fPtr)) != EOF) {
        if (c == ' ' || c == '\n'){
            wordCount++;
            //printf("%d, %c", wordCount, c);
        }
    }
    printf("\n\nNUMBER OF WORDS: %d\n", wordCount);
    fclose(fPtr);
	return 0;
}
