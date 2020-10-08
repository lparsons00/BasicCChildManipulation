#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1000

//to run:
//1. compile wc.c (found in line 82)
//2. wc.c code is found line 61-79
//3. $ mainreturn.cpp -o main 
//4. $ ./main f1 f2
// f1 is file 1 location
// f2 is file 2 location

int    g_argc;
char **g_argv;

void main(int argc, char *argv[]){
    int newPid;
    int counter = 0;
    
    //change below to command line
	char file1[20];
    char file2[20];
	g_argc = argc;
    g_argv = argv;
	
	//char file2[] = argv[1];
    //char file2[20] = argv[2];
    
    printf("\nBefore:%d\n", getpid());
	int j = 0;
    for(; j < 3;j++){
        counter++;
        if((newPid = fork()) == -1){
            perror("Error Forking.");
        } else if (newPid == 0){
            childCode(counter, file1, file2);
        } else {
            parentCode(newPid);
        }
    }
}

void childCode(int counter, char f1[20], char f2[20]){
    printf("CHILD: %d\n", counter);
    switch(counter){
        case 1: childOne();
                break;
        case 2: childTwo(f1);
                break;
        case 3: childThree(f2);  
                break;
    }
    printf("\nChild Done!\n");
    exit(17);
}
    
    
void childOne(){
    int topMark = 0;
	int tempMark = 0;
	int i =0;
    for(; i< 10; i++){
        printf("INPUT STUDENT MARKS:\n");
        scanf("%d", &tempMark);
        if(tempMark > topMark){
            topMark = tempMark;
        }
    }
    printf("Top Mark: %d", topMark);
}  

/*
void wc(char f1[20]){
    printf("I am wc.c called by execvp()\n"); 
    FILE *fPtr;
    char path[20]; strcpy(path, f1);
    int wordCount = 1;
    char c;
    
    fPtr = fopen(path, "r");
    while((c = fgetc(fPtr)) != EOF) {
        if (c == ' ' || c == '\n'){
            wordCount++;
            printf("%d, %c", wordCount, c);
        }
    }
    printf("NUMBER OF WORDS: %d", wordCount);
    fclose(fPtr);
}*/


void childTwo(char f1[20]){
    //calls wc 'word count' program
    //gcc wc.c -o wc
    char *cmd = "./wc";
    char *argv[3];
    argv[0] = "./wc";
    argv[1] = g_argv[1];
    argv[2] = NULL;
	
    execvp(cmd, argv); //This will run "wc f1" as if it were a command
	
} 
    
void childThree(char f2[20]){
    FILE *fPtr;
    FILE *fPtr2;
    FILE *tempPtr;
    char path[20]; strcpy(path, g_argv[2]);
    printf("this is the path: %s", path);
	
    char buffer[BUFFER_SIZE];
    char oldWord[10] = "execute";
    char newWord[10] = "run";
    char oldWordTwo[10] = "study";
    char newWordTwo[10] = "examine";
    int looper = 0;
    
    while(looper < 2){
        fPtr = fopen(path, "r");
        tempPtr = fopen("replace.txt", "w+");
        
        //if failed opening, print error and exit
        if((fPtr == NULL) || (tempPtr == NULL)){
            printf("Error reading files.");
            exit(19);
        }
        
        //call replaceAll funct
        while((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL){
            replaceAll(buffer, oldWord, newWord);
            fputs(buffer, tempPtr);
        }
        
        //rename replace.tmp as program.txt
        rename("replace.txt", g_argv[2]);
        printf("\nSuccessfully replaces all occurances of %s with %s.", oldWord, newWord);
        
        looper++;
        strcpy(newWord, newWordTwo);
        strcpy(oldWord, oldWordTwo);
        
        fclose(fPtr);
        fclose(tempPtr);
    }  
    //call appendText funct
    appendText(fPtr, tempPtr, f2);
}

void replaceAll(char *str, const char *oldWord, const char *newWord){
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int oldLength = strlen(oldWord);

    while((pos = strstr(str, oldWord)) != NULL){
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + oldLength);
    }
}

void appendText(FILE * fPtr, FILE *tempPtr, char f2[20]){
    char dataAppend[] = "this is the updated version\n";
    char ch, ab;
    char path[20]; strcpy(path, g_argv[2]);
    //change program to f2
    fPtr =  fopen(path, "r");
    tempPtr = fopen("replace.txt", "w+");
    fprintf(tempPtr, dataAppend);
    
    while( ( ch = fgetc(fPtr) ) != EOF ){
        fputc(ch, tempPtr);
    }
    
    fclose(tempPtr);
    fclose(fPtr);
    //change program to f2
    rename("replace.txt", path);
    
    remove("replace.txt");
}

void parentCode(int childPid){
    int wait_rv; 
    int child_status;
    int high_8, low_7, bit_7;
    wait_rv = wait(&child_status);
    printf("Done waiting for %d\n", childPid);
    
    high_8 = child_status >> 8;
    low_7 = child_status & 0x7F;
    bit_7 = child_status & 0x80;
    printf("STATUS: exit=%d, sig=%d, core=%d\n\n", high_8, low_7, bit_7);
}