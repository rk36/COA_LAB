// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

/*


define stddlib for using rand()

*/



void merge(int arr[],int low ,int mid,int high)
{
	int i=low;
	int j=mid+1;
	int b[high-low+1];
	// int l = mid-low;
	// int r = high - mid; 
	int count=0;

	while(i<=mid && j<=high)
	{
		if(arr[i]>arr[j])
		{
			b[count] = arr[j];
			j++;
		}
		else
		{
			b[count] = arr[i];
			i++;
		}
		count++;
	}

	if(j<high)
	{
		while(j<=high)
		{
			b[count] = arr[j];
			j++;
			count++;
		}
	}
	
	else if(i< low)
	{
		while(i<=low)
		{
		b[count] = arr[i];
		i++;
		count++;
		}
	}


	for(int i=0;i<=count;i++)
	{
		arr[low+i] = b[i]; 
	}

}

void mergesort(int arr[],int low,int high)
{
	if(low<high)
	{
		int mid = (low+high)/2;
		mergesort(arr,low,mid);
		mergesort(arr,mid+1,high);
		merge(arr,low,mid,high);
	}

}



#define arr_size 10

int main()
{
	pid_t pid;

	int fd,fd1,fd2;
	char* read_write1= "/tmp/new";
	char* read_write2= "/tmp/new2";

	mkfifo(read_write1,0666);
	mkfifo(read_write2,0666);

	pid = fork();
	if(pid<0)
	{
		printf("perror");
	}

	if(pid == 0)
	{
		int arr1[arr_size/2];

		fd1 = open(read_write1,O_RDONLY);

		read(fd1,arr1,sizeof(arr1));

		// for(int i=0;i<arr_size/2;i++)
		// {
		// 	printf(" %d ",arr1[i]);
		// }

		printf("child 1 \n");

		mergesort(arr1,0,arr_size/2-1);

		for(int i=0;i<arr_size/2;i++)
		{
			printf(" %d ",arr1[i]);
		}

		printf("\n");
		close(fd1);



		//fd = open(myfifo, O_RDONLY);
 
	}

	else
	{
		
		// now read the data (will block until it succeeds)
		//printf("first child size = %ld\n",sizeof(arr));
		pid_t  pid1;
		pid1 = fork(); 
		if(pid1<0)
			{
				printf("perror");
			}

			if(pid1 == 0)
			{

				int mid = arr_size/2;
				int left = arr_size-mid;
				int arr2[left];

				fd2 = open(read_write2,O_RDONLY);
				read(fd2,arr2,sizeof(arr2));
				// for(int i=0;i<left;i++)
				// {
				// 	printf(" %d ",arr2[i]);
				// }
				printf("\n");
				printf("child 2 \n");
				mergesort(arr2,0,arr_size-mid-1);
		
				for(int i=0;i<left;i++)
				{
					printf(" %d ",arr2[i]);
				}
				printf("\n");


				close(fd2);
			}
			else
			{
				int arr[arr_size];
				int fd3;

				for(int i=0;i<arr_size;i++)
				{
					arr[i] = rand()%100;
				}
				int mid = arr_size/2;
				int arr1[mid];
				int arr2[arr_size - mid ];

				for(int i=0;i<mid;i++)
				{
					arr1[i]= arr[i];
				}
				for(int i=0;i<(arr_size-mid);i++)
				{
					arr2[i] = arr[i+mid];
				}

				fd = open(read_write1,O_WRONLY);

				write(fd,arr1,sizeof(arr1));
				close(fd);

				fd3 =  open(read_write2,O_WRONLY);
				write(fd3,arr2,sizeof(arr2));
				close(fd3);

			}
		// read(fd[0], arr,sizeof(arr));
		// printf("this is first child\n");
		// close(fd[0]);
		// for(int i=0;i<arr_size;i++)
		// {
		// 	printf("%d\n",arr[i]);
		// }
		// printf("Child(%d) \n", getpid());
		// qsort(arr,arr_size, sizeof(arr[0]),corr_comparator);
		// // close the read-descriptor
		// // printf("this is quciksort\n");
		// for(int i=0;i<arr_size;i++)
		// {
		// 	printf("%d\n",arr[i]);
		// }
		// close(fd_r[0]);
		// printf("hello\n");
		// write(fd_r[1],arr,sizeof(arr));
		// close(fd_r[1]);

	}

}