//
// Created by rishabh on 21/8/18.
//

// C program to demonstrate use of fork() and pipe()
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(){

    mkfifo("myfifo",0666);
//     int pid;
//     pid = fork();
int fd;
    int n;
    scanf("%d",&n);
    printf("line 20 %d",n);
    int arr[n];
    for(int i = 0;i< n;i++){
        printf("line 23- ");
        scanf("%d",&arr[i]);
        printf("%d ",arr[i]);
    }
    for(int i = 0;i<n;i++)printf("line27 %d ", arr[i]);
    fd = open("myfifo", O_WRONLY);
    write(fd,arr,n*sizeof(int));
    close(fd);
printf("line 31");
}