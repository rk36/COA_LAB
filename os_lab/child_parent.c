#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    
    int parl;
    int man;

    parl = fork();

    if(parl == 0)
    {
        printf("child process \n");
        printf("child process \n Child %d : parent : %d \n",getpid(),getppid());
    }
    else
    {
        man = fork();


        printf("parent process\n");
        wait(&parl);
        printf("parent process Child %d : parent : %d \n", getpid(),getppid());
    }
    
    return 0;
}
