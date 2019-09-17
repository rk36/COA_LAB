#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define arr_size 10


/*
learning 
sizeof(arr) returns bit size used;
i.e. 
if arr[] = {1,23,2,32,2}
sizeof(arr) would give 5*4 = 20 
also return type is long int 

pipes are half duplex ,so at a time they can either write or read,
but it is not a good idea to use single pipe for both read and write as
it can have synchronisation issuese.so better use two pipes,pipes 
you have to close one end before using the other,so doing 
https://stackoverflow.com/questions/15965989/use-one-pipe-to-read-and-write-between-parent-and-child
for more


q sort in c, it requires compartor 
so define like 
where array_size should be number of elements, 
the 
comparator fun returns either +ve or negative values 

qsort(arr,arr_size, sizeof(arr[0]),corr_comparator);
int corr_comparator(const void *p, const void *q)
{
    // Get the values at given addresses
    int l = *(const int *)p;
    int r = *(const int *)q;
 
    return l-r;
}


*/


int corr_comparator(const void *p, const void *q)
{
    // Get the values at given addresses
    int l = *(const int *)p;
    int r = *(const int *)q;
 
    return l-r;
}


int err_comparator(const void *p, const void *q)
{
   
    return rand()%2;

}

int comp(const void* p ,const void* q)
{
	return *(const int*)p - *(const int*)q;

}
int main(int argc, char *argv[]) {
	int fd[2];
	int fd1[2];
	int fd_r[2];
	int fd1_r[2];
	//int childID = 0;

	// create pipe descriptors
	pipe(fd);
	pipe(fd1);
	pipe(fd_r);
	pipe(fd1_r);

	// fork() returns 0 for child process, child-pid for parent process.
	if (fork() != 0) 
	{
		// parent: writing only, so close read-descriptor.
		if(fork() == 0)
		{
		
		close(fd1[1]);
		int arr[80];
		// now read the data (will block until it succeeds)
		read(fd1[0], arr, sizeof(arr));
		int size= sizeof(arr)/sizeof(arr[0]);
		close(fd1[0]);
		// printf("Child(%d) ", getpid());
		// //printf("this is not  quciksort\n");
		// for(int i=0;i<arr_size;i++)
		// {
		// 	printf("%d\n",arr[i]);
		// }

		// printf("size = %d\n",arr_size );
		qsort(arr, arr_size , sizeof(arr[0]),err_comparator);
		// printf("Child(%d) ", getpid());
		// //printf("this is not  quciksort\n");
		printf(" sorted after second child \n");
		for(int i=0;i<arr_size;i++)
		{
			printf("%d ",arr[i]);
		}
		printf("\n");
		// close the read-descriptor
		close(fd1_r[0]);
		write(fd1_r[1],arr,sizeof(arr));
		close(fd1_r[1]);

		}
		
		else
		{

		close(fd[0]);
		close(fd1[0]);
		// send the childID on the write-descriptor.
		int x;
		//scanf("%d",&x);
		int childID[arr_size];
		for(int i=0;i<arr_size;i++)
		{
			childID[i] = rand()%100;
		}
		//int childID[] = {3,3,4,6};
		write(fd[1], childID, arr_size*sizeof(int));
		write(fd1[1],childID,arr_size*sizeof(int));
		//printf("size of childID %ld\n",sizeof(childID));
		//printf("Parent(%d)", getpid());
		close(fd1[1]);
		close(fd[1]);
		//sleep(3);
		wait(NULL);
		close(fd_r[1]);
		read(fd_r[0], childID, sizeof(childID));
		printf("correct child process\n");
		for(int i=0;i<arr_size;i++)
		{
			printf("%d ",childID[i] );
		}
		printf("\n");
		close(fd_r[0]);
		sleep(2);
		close(fd1_r[1]);
		read(fd1_r[0], childID, sizeof(childID));
		close(fd1_r[0]);

		printf("error child process\n");
		for(int i=0;i<arr_size;i++)
		{
			printf("%d ",childID[i] );
		}
		printf("\n");
		// close the write descriptor
		close(fd1_r[1]);
		}

	}
	 
	else {
		// child: reading only, so close the write-descriptor
		close(fd[1]);
		int arr[arr_size];
		// now read the data (will block until it succeeds)
		//printf("first child size = %ld\n",sizeof(arr));
		read(fd[0], arr,sizeof(arr));
		printf("this is first child\n");
		close(fd[0]);
		for(int i=0;i<arr_size;i++)
		{
			printf("%d ",arr[i]);
		}
		printf("Child(%d) \n", getpid());
		qsort(arr,arr_size, sizeof(arr[0]),comp);//arator);
		// close the read-descriptor
		// printf("this is quciksort\n");
		for(int i=0;i<arr_size;i++)
		{
			printf("%d ",arr[i]);
		}
		close(fd_r[0]);
		printf("hello\n");
		write(fd_r[1],arr,sizeof(arr));
		close(fd_r[1]);

		}
	return 0;
}