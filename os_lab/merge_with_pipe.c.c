// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	int fd1,fd2;
	char* read_write1= '/tmp/new';
	char* read_write2= '/tmp/new2';

	myfifo(read_write,0666);

	if(pid<0)
	{
		printf("perror");
	}

	if(pid == 0)
	{

	}

	else
	{
		
		// now read the data (will block until it succeeds)
		//printf("first child size = %ld\n",sizeof(arr));
		pid_t = pid1;
		if(pid<0)
			{
				printf("perror");
			}

			if(pid == 0)
			{

			}
			else
			{

			}
		read(fd[0], arr,sizeof(arr));
		printf("this is first child\n");
		close(fd[0]);
		for(int i=0;i<arr_size;i++)
		{
			printf("%d\n",arr[i]);
		}
		printf("Child(%d) \n", getpid());
		qsort(arr,arr_size, sizeof(arr[0]),corr_comparator);
		// close the read-descriptor
		// printf("this is quciksort\n");
		for(int i=0;i<arr_size;i++)
		{
			printf("%d\n",arr[i]);
		}
		close(fd_r[0]);
		printf("hello\n");
		write(fd_r[1],arr,sizeof(arr));
		close(fd_r[1]);

	}

}