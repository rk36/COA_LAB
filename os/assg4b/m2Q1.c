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
    int n = 5;
    int arr[n];
    printf("line 31 \n");
    fd = open("myfifo", O_RDONLY);
    read(fd,arr,sizeof(arr));
    close(fd);
    for(int i = 0;i<n;i++)printf("%d ", arr[i]);
    printf("\nline 36");
}