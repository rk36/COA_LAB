//
// Created by rishabh on 21/8/18.
//

// C program to demonstrate use of fork() and pipe()
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    // We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child

    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe

    char fixed_str[] = "forgeeks.org";
    char input_str[100];
    pid_t p;
    int num1=pipe(fd1);
    int num2 = pipe(fd2);
    if (num1==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (num2==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    scanf("%s", input_str);
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }
    else if(p>0){
        char str[100];
        close(fd1[0]); //close read end of parent
        write(fd1[1],input_str,strlen(input_str)+1); //write in pipe1
        close(fd1[1]); //close pipe1 write end
        wait(NULL);
        close(fd2[1]);//close write end of pipe2
        read(fd2[0],str,100);
        printf("Concatenated string %s\n", str);
        close(fd2[0]);
    }else{
        close(fd1[1]);
        char inp_str[100];
        read(fd1[0], inp_str,100);
        int k = strlen(inp_str);
        for(int i = 0;i<strlen(fixed_str);i++)inp_str[k++] = fixed_str[i];
        inp_str[k] = '\0';
        close(fd1[0]);
        close(fd2[0]);
        write(fd2[1],inp_str,strlen(inp_str)+1);
        close(fd2[1]);
        exit(0);
    }
}