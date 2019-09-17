#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <error.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>

struct position
{
	int a;
	int b;
};


typedef struct position pos;

int n=3;
int x=3;
int m=3;

int mat1[3][3] = { {1,0,0},{0,1,0 },{0,0,1}};

int mat2[3][3] = { {1,2,3},{2,3,5},{5,6,7}};

int arr[3][3];

void intialise(int n,int m)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			arr[i][j] = 0;
		}
	}
}

typedef struct position pos;

void printarray(int n,int m)
{

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			printf("%d ",arr[i][j]);
		}
     }
    printf("\n");
}

static void* multi(void* q)
{

   	//int arr[x];
	pos* p = q;
	int arrter[x];
	int sum=0;
	for(int i=0;i<x;i++)
	{
		sum += mat1[p->a][i]*mat2[i][p->b];

	}

	arr[p->a][p->b] = sum;
	printf("arr[%d][%d] = %d \n",p->a,p->b,arr[p->a][p->b]);
	//pthread_join()
	// for(int i=0;i<x;i++)
	// {
	// 	arrter[i] = mat1[p->a][i]*mat2[i][p->b];
	// }
	//print_exit(arrter);
	//return arrter;
	//return arr;
}

int main()
{

	//char* file = "tmp/file2";



	//mkfifo(file,0666);
	// int n;
	// int m;
	// printf("num of rows \n");
	// scanf("%d",&n);
	// printf("numeber of columns \n");
	// scanf("%d",&m);

	 n = 3;
	 m = 3;

	 intialise(n,m);
	// int mat[n][m] = {
	// 	[1,2,3]
	// 	,[2,3,5]
	// 	,[5,6,7]
	// };


	//for(int i=0;i<n;i++)
	pthread_t thread[n*m+1];

	//printarray(n,m);

	pos p;

	int subarr[x];
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{

			p.a = i;
			p.b = j;
			sleep(1);
			//printf("p =  %d %d \n",p.a,p.b );
			 
			 if(i == 0 && j ==0)
			 {
			 	pthread_create(&thread[0],NULL,&multi,&p);
			 }
			 sleep(1);
			 pthread_create(&thread[i*n + j],NULL,&multi,&p);
			subarr = pthread_create(&thread[i*n + j],NULL,&multi,&p);
			for(int it=0;it<x;it++)
			{
				arr[i][j] += subarr[it];
			}
			
		}
	}

	// for(int i=0;i<n;i++)
	// {
	// 	for(int j=0;j<m;j++)
	// 	{
			
	// 		pthread_join(thread[i*3 + j],NULL);

	// 	}
	// }

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			
			if(i ==0 && j==0) pthread_join(thread[0],NULL);
			pthread_join(thread[i*n + j],NULL);

		}
	}



	// for(int i=0;i<n;i++)
	// {
	// 	for(int j=0;j<m;j++)
	// 	{
	// 		printf("%d ",arr[i][j]);
	// 	}
	// 	printf("\n");
	// }
	arr[0][0] = 1;
	printarray(n,m);

	printf(" hel \n");

	return 0;


}