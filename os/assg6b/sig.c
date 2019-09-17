#include<stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>
void handleC(int val){
    printf("Caught an error, req no : %d \n", val);
}
void handleZ(int val){
    printf("termination request received, req no : %d \n", val);
    exit(0);
}
void handleA(int val){
    printf("Alarm \n");
}
int main (){
    if(signal(SIGALRM, handleA)==SIG_ERR){
        printf("failed to respond to SIGALRM");
    }
    if(signal(SIGINT, handleC)==SIG_ERR){
        printf("failed to respond to SIGINT");
    }
    if(signal(SIGTSTP, handleZ)==SIG_ERR){
        printf("failed to respond to SIGTSTP. Still Termination acknowledged");
        exit(0);
    }


    while(1){
//        raise(SIGALRM);
        sleep(4);
        alarm(2);
    }
}
