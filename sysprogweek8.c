#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

void childCode(int delay){
    printf("child %d will sleep for %d\n", getpid(), delay);
    sleep(delay);
    printf("child done!\n");
    exit(17);
}

void parentCode(int childPid){
    int wait_rv;
    int child_status;
    int high_8, low_7, bit_7;
    
    wait_rv = wait(&child_status);
    printf("done waiting for %d, wait returned %d\n", childPid, wait_rv);
    
    high_8 = child_status >> 8;
    low_7 = child_status & 0x7F;
    bit_7 = child_status & 0x80;
    printf("Status: exit=%d, sig=%d, core=%d\n\n", high_8, low_7, bit_7);
}


main(){
    int newPid, random;
    void childCode(), parentCode();
    
    int numberOfChildren = 0;
    printf("How many children?");
    scanf("%d", &numberOfChildren);
    
    srand(time(0));
    
    printf("\nBefore: %d\n", getpid());
    for(int i = 0; i < numberOfChildren; i++ ){
        random = rand()%10;
        if( (newPid = fork()) == -1){
            perror("fork");
        } else if (newPid == 0){
            childCode(random);
        } else {
            parentCode(newPid);
        }
    }
}
