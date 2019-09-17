#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
#define arr_size 10

int main()
{

	
	int size;
	int x;
	printf(" size of array \n");
	
	// for(int i=0;i<arr_size;i++)
	// {
	// 	scanf("%d",&arr[i]);
	// }

	int fd[2];
	int fd1[2];

	if(pipe(fd)<0)
	{
		perror("pipe");
	}

	if(pipe(fd1)<0)
	{
		perror("pipe");
	}

	printf("at close\n");

	


	pid_t pid;
	pid = fork();

	printf("afer fork\n");

	if(pid < 0)
	{
		perror("fork");
	}

	if(pid == 0)
	{	

		int arr2[arr_size];
		sleep(3);
		close(fd[1]);
		read(fd[0],arr2,arr_size);
		close(fd[0]);
		
		arr2[1] = arr2[2]; 
		printf("hello in first child\n");
		for(int i=0;i<arr_size;i++)
		{
			printf("%d ", arr2[i]);
		}
		return 0;

		
	}
	else
	{

		pid_t psid;
		psid = fork();
		int arr[arr_size];
		if(psid == 0)
		{
			int arr3[arr_size];
			close(fd1[1]);
			sleep(3);
			read(fd1[0],arr3,arr_size);
			arr3[9] = arr3[0];
			close(fd1[0]);
			printf("\nwait for second child\n");
			for(int i=0;i<arr_size;i++)
			{
				printf("%d ",arr[i]);
			}
			printf("\n");
			return 0;

		}
		else
		{
		//scanf("%d",&x);
		int arr[arr_size];
		//arr = malloc(arr_size*sizeof(int));
		for(int i=0;i<arr_size;i++)
		{
			arr[i] =0;
			printf("%d ",arr[i] );
		}
		printf("\n");
		
		close(fd[0]);
		write(fd[1],arr,arr_size*sizeof(int));
		close(fd[1]);

		// int arr2[arr_size];
		// printf("in parent \n");
		// read(fd[0],arr2,arr_size);
		// close(fd[0]);
		// for(int i=0;i<arr_size;i++)
		// {
		// 	printf("%d ",arr2[i]);
		// }
		// printf("\n");

		close(fd1[0]);
		write(fd1[1],arr,arr_size*sizeof(int));
		close(fd1[1]);

		}
		

	}
	return 0;

}