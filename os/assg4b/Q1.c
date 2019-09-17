//
// Created by rishabh on 21/8/18.
//

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

int compare(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
int main()
{
    // We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child

    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe

    int input_num[100];
    pid_t p;
    int num1=pipe(fd1);
    int num2 = pipe(fd2);
    if (num1==-1)
    {
        perror("Pipe Failed");
        return 1;
    }
    if (num2==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    int asz;
    scanf("%d", &asz);
    int a[asz];
    for(int i = 0;i<asz;i++)scanf("%d",&a[i]);
    printf("checking input ");
    for(int i = 0;i<asz;i++)printf("%d ", a[i]);
    printf("\n");
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }
    else if(p>0){
	int inp1[asz];
        wait(NULL);
	
        close(fd1[1]);//close write end of pipe2
        read(fd1[0],inp1,asz* sizeof(int));
        for(int i = 0;i<asz;i++)printf("%d ", inp1[i]);
        printf("\n");
  //      close(fd2[1]);
  //      read(fd1[0],inp1,asz* sizeof(int));

        pid_t p2;
        p2 = fork();
        if(p2>0){
            wait(NULL);
            close(fd2[1]);//close write end of pipe2
            read(fd2[0],inp1,asz* sizeof(int));
            close(fd2[0]);
            printf("second child\n");
            for(int i = 0;i<asz;i++)printf("%d ", inp1[i]);
            printf("\n");


        }else{
            for(int i = 0;i<asz;i++) inp1[i] = a[i];
            close(fd2[0]);
            qsort(inp1,asz,sizeof(int),compare);
//            printf("second child\n");
//            for(int i = 0;i<asz;i++)printf("%d ", inp1[i]);
//            printf("\n");
            write(fd2[1],inp1,asz* sizeof(int));
            close(fd2[1]);
            exit(0);
        }

    }else{
        int inp1[asz];
        for(int i = 0;i<asz;i++) inp1[i] = a[i];
        for(int i = 0;i<3;i++){
            int temp = inp1[i];
            inp1[i] =inp1[asz-1-i] ;
            inp1[asz-1-i] = temp;
        }

        printf("child process 1 here:");
        for(int i = 0;i<asz;i++)printf("%d ", inp1[i]);
        printf("\n");
        close(fd1[0]);
        write(fd1[1],inp1,asz* sizeof(int));
        close(fd1[1]);
        exit(0);
    }
}
