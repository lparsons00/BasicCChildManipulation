//to load a program called “wc” (word count)
//to count file1. file1 is received
//from the command line argument.

#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 


int main()
{
    //execvp runs the executable file saved as CHILDTWO
    char *args[]={"./CHILDTWO",NULL}; 
    execvp(args[0],args);
}