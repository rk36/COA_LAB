#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>

int main()
{
    int k,l,j;
    int fd;

    char* file1 = "/tmp/sort_child1";
    char* file11 = "/tmp/sort_child11";
    char* file22 = "/tmp/sort_child22";
    char* file2 = "/tmp/sort_child2";

    mkfifo(file1,0666);
    mkfifo(file2,0666);

    pid_t pid1;
    pid_t pid2;

    pid1 = fork();

    if(pid1<0)
    {   
        perror("fork");
    }

    if(pid1==0)
    {
            int arr[10];
           // char * file1 = "tmp/sort_child1";
            //int fd;

            int fd = open(file1,O_RDONLY);
		    int child_array[100];
		    read(fd,child_array,sizeof(child_array));
		    close(fd);


            // fd = open(file1,O_RDONLY);
            // read(fd,arr,sizeof(arr));
            // close(fd);
            int size = 5;//arr[1];

            printf("%d \n ", size);

            printf(" child 1 writing smthing \n");

            for(int i=1;i<= size ; i++)
            {
                printf("%d ",child_array[i]);
            }
            
            for(int i=1;i<=size ;i++)
            {
                arr[i] = 9;
            }

            // printf("\n");

            fd = open(file11,O_WRONLY);
            write(fd,arr,sizeof(arr));
            close(fd);


            // fd = open(file1,O_WRONLY);
            // write(fd,arr,sizeof(arr));
            // close(fd);

             for(int i=1;i<=size ;i++)
            {
                printf(" %d ",arr[i] );
            }

            printf("\n");

            printf("child 1 finished \n");

    }

    else
    {
        pid2 = fork();

        if(pid2<0)
        {
            perror("fork");
        }
        else if(pid2 == 0)
        {

            int arr[100];
            char * file2 = "/tmp/sort_child2";
            int fd;
            fd = open(file2,O_RDONLY);
            read(fd,arr,sizeof(arr));
            close(fd);
            int size = 5;//arr[0];

            printf(" child 2 writing smthing \n");
            for(int i=1;i<=size ;i++)
            {
                printf("%d ",arr[i]);
            }
            
            for(int i=1;i<=size ;i++)
            {
                arr[i] = 8;
            }
        
            printf("\n");

            int fd2 = open(file22,O_WRONLY);
            write(fd2,arr,sizeof(arr));
            close(fd2);

            printf("child 2 finished \n");
            
        }

        else
        {
            

            int arr[10];
            int arr2[10];
            int size = 5;
            arr[0] = size;

            for(int i=1;i<= size;i++)
            {   
                arr[i] = rand()%(size);
                arr2[i] = rand()%(size);

                arr[i] = 2;
                arr2[i] = 1;

                // printf("arr = %d ",arr[i]);
                // printf("arr2 =  %d ",arr2[i]);
            }

            // printf(" parent \n ");
            //   for(int i=1;i<=size ;i++)
            // {
            //     printf("%d ",arr[i]);
            
            // }

            //    for(int i=1;i<=size ;i++)
            // {
            //     printf("%d ",arr2[i]);
            
            // }



            int fd1 = open(file1,O_WRONLY);
            write(fd1,arr,sizeof(arr));
            close(fd1);

            int  fd2 = open(file2,O_WRONLY);
            write(fd2,arr2,sizeof(arr2));
            close(fd2);

           
            wait(NULL);

            int fd3 = open(file11,O_RDONLY);
            read(fd3,arr,sizeof(arr));
            close(fd3);


            printf(" parent is reading child 1");
            for(int i=0;i<=9;i++)
            {
                printf(" %d ",arr[i]);
            }
            printf("\n");

            int arr3[100];
            int fd4 = open(file22,O_RDONLY);
            read(fd4,arr3,sizeof(arr3));
            close(fd4);

            printf(" parent hghg is reading child 2");
            for(int i=0;i<=9;i++)
            {
                printf(" %d ",arr[i] );
            }
             printf("\n");
            
        }

    }
    return 0;
}