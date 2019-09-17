#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>


void merge(int arr1[],int arr2[],int arr[],int n1,int n2)
{

	int b[n1+n2];
	// int l = mid-low;
	// int r = high - mid; 
	int count=0;
	int i=0;
	int j=0;

	while(i<n1 && j<n2)
	{
		if(arr1[i]>arr2[j])
		{
			b[count] = arr2[j];
			j++;
		}
		else
		{
			b[count] = arr1[i];
			i++;
		}
		count++;
	}

	if(j<n2)
	{
		while(j<n2)
		{
			b[count] = arr2[j];
			j++;
			count++;
		}
	}
	
	else if(i< n1)
	{
		while(i<n1)
		{
		b[count] = arr1[i];
		i++;
		count++;
		}
	}


	for(int i=0;i<=count;i++)
	{
		arr[i] = b[i]; 
	}

}

// void mergesort(int arr[],int low,int high)
// {
// 	if(low<high)
// 	{
// 		int mid = (low+high)/2;
// 		mergesort(arr,low,mid);
// 		mergesort(arr,mid+1,high);
// 		merge(arr,low,mid,high);
// 	}

// }

int comparetor (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

int  printarr(int arr[],int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d ",arr[i] );
	}
	printf("\n");
	return 0;
}


int main()
{
	pid_t pid;
	char* arr_1 = "/tmp/merge_array1";
	char* arr_2 = "/tmp/merge_array2";

	mkfifo(arr_1,0666);
	mkfifo(arr_2,0666);

	int n;

   
	//scanf("%d",&n);
	//int arr[n];
	int arr[] = {1,-12,-13,3,0,2,-3,-17,98,43};
	n = sizeof(arr)/sizeof(arr[0]);

	int n1 = n>>1;
	int n2 = n - n1;

	int arr1[n1];
	int arr2[n2];
	for(int i=0;i<n1;i++)
	{
		arr1[i] = arr[i];
	}
	int j=0;
	for(int i=n1;i<n;i++,j++)
	{
		arr2[j] = arr[i];
	}
	

	// for(int i=0;i<n;i++)
	// 	scanf("%d",&arr[i]);


	// int arr1[] = {1,-12,-13} ;
	// int arr2[] = {3,0,2,-3};
 //    int arr3[n1];
 //    int arr4[n2];

 	pid = fork();
	if(pid <0)
	{
		perror("fork()");
	}

	else if(pid == 0)
	{

		int fd = open(arr_1,O_RDONLY);
		int child_array[n1];
		read(fd,child_array,sizeof(child_array));
		close(fd);
		// printf("before sort c1 ");
		// printarr(child_array,n1);
		// printf("in c1\n");
		//qsort(child_array,n1,sizeof(int),comparetor);
		for(int i=0;i<n;i++)
			{
				arr_1[i] = 1;
			} 
		
		// printf("after sort c1 n1 = %d\n",n1);//,printarr(child_array,n1));
		// printarr(child_array,n1);
		fd = open(arr_1,O_WRONLY);
		
		write(fd,child_array,sizeof(child_array));
		close(fd);
		printf("fun of c2 \n");
		// printarr(child_array,n1);
		//exit(1);
	}
	else // parent child
	{
		pid_t p2;
		p2 = fork();
		if(p2 < 0) 
		{
			perror("fork()");
		}
		else if(p2 == 0)
		{
			int fd  = open(arr_2,O_RDONLY);
			int child_array[n2];

			read(fd,child_array,sizeof(child_array));
			close(fd);
			// printf("before sort c2 n2 = %d \n",n2);
			// printarr(child_array,n2);

			//qsort(child_array,n2,sizeof(int),comparetor);
			
			// printf("after sort c2 \n");
			// printarr(child_array,n2);
			// printf("in c2 \n");
			fd = open(arr_2,O_WRONLY);

			for(int i=0;i<n;i++)
			{
				arr_2[i] = 0;
			} 
			// printf("in c2 181 \n");
			write(fd,child_array,sizeof(child_array));
			close(fd);
			printf("fun of c2 \n");
			printarr(child_array,n2);
			//exit(1);
 }
		else
		{
			int fd1 = open(arr_1,O_WRONLY);

			write(fd1,arr1,sizeof(arr1));
			close(fd1);

			int fd2 = open(arr_2,O_WRONLY);
			write(fd2,arr2,sizeof(arr2));
			close(fd2);

			//wait(NULL);
			// printf("in parent \n");
			fd1 = open(arr_1,O_RDONLY);
			read(fd1,arr1,sizeof(arr1));
			// printf("hellow wold\n");
			//printarr(arr1,n1);
			close(fd1);
			fd2 = open(arr_2,O_RDONLY);
			read(fd2,arr2,sizeof(arr2));
			// printf("hellowdff wold\n");
			printarr(arr1,n1);
			printarr(arr2,n2);
			close(fd2);

			//merge(arr1,arr2,arr,n1,n2);

			for(int i=0;i<n;i++)
			{
				printf("%d ",arr[i] );
			} 
			printf("feder \n");

		}
	}

	return 0;
}