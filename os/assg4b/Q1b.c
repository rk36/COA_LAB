#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main (){
    int fd1[2];
    int fd2[2];
    int n;
    printf("Type number of elements");
    scanf("%d",&n);
    int arr[n];
    for(int i= 0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    if(pipe(fd1)==-1){
        printf("pipe failed");
    }
    if(pipe(fd2)==-1){
        printf("pipe failed");
    }
    int p = fork();
    if(p>0){
        int inp[n];
        read(fd1[0],inp,n*sizeof(int));
        for(int i = 0;i<n;i++)printf("%d",arr[i]);
        int p2 =fork();
        if(p2>0){

        }else{

        }

    }else{
        for(int i = 0;i<n/2;i++){
            int temp = arr[i];
            arr[i] = arr[n-i-1];
            arr[n-i-1] = temp;
        }
        close(fd1[0]);
        write(fd1[1],arr, n*sizeof(int));
        close(fd1[1]);
        exit(0);
    }


}
