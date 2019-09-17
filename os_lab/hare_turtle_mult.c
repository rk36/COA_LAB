#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
//#include <sys/types.h>

int harepos;
int turtlepos;
int finish_line;
bool status = true;

void* harefile()
{

	static int speed = 4;
	while(harepos < finish_line && status)
	{
	//printf("\n hare %d \n",harepos );
	harepos = harepos + speed ;
	if(harepos- turtlepos > 30)
	{
		int s = rand()%30;
		sleep(20+s);
		speed = 4;
	}	
	if(harepos - turtlepos < -5)
	{
		speed = speed + 2;
	}
	//sleep(1);
	sleep(1);
	}

}

void* turtlefile()
{
	while(turtlepos < finish_line && status)
	{ turtlepos++;
		//printf("\nturtle = %d\n", turtlepos);
         //sleep(1);
		sleep(1);
	}
}

// void* reward()
// {
// 	if(harepos > finish_line)
// 	{
// 		printf("hare wins \n");

// 	}
// 	if(turtlepos < turtlepos)
// 	{
// 		printf("turle wins \n");
// 	}
// }

int min(int a,int b)
{
   return a>b?b:a;
}

void* trackfile()
{
	while(status && turtlepos < finish_line && harepos < finish_line)
	{

	system("clear");

	for(int i=0;i <harepos;i++)
   {
    printf(" ");
   }
   printf("H");
   for(int i=harepos;i<finish_line;i++)
   {
    printf(" ");
   }
   printf(" ||\n");

   for(int i=0;i <turtlepos;i++)
   {
    printf(" ");
   }
   printf("T");
   for(int i=turtlepos;i<finish_line;i++)
   {
    printf(" ");
   }
    printf(" ||\n");

    sleep(1);
}
	
	if(turtlepos >= finish_line)
	{
	system("clear");

	for(int i=0;i <min(harepos,finish_line);i++)
   {
    printf(" ");
   }
   printf("H");
   for(int i=harepos;i<finish_line;i++)
   {
    printf(" ");
   }
   printf(" ||\n");

   for(int i=0;i <min(turtlepos,finish_line);i++)
   {
    printf(" ");
   }
   printf("T");
   for(int i=turtlepos;i<finish_line;i++)
   {
    printf(" ");
   }
    printf(" ||\n");


    printf("turtle won the race\n");
    status = false;
    sleep(1);

	}

	if(harepos >= finish_line)
	{
		system("clear");

	for(int i=0;i <min(harepos,finish_line);i++)
   {
    printf(" ");
   }
   printf("H");
   for(int i=harepos;i<finish_line;i++)
   {
    printf(" ");
   }
   printf(" ||\n");

   for(int i=0;i <min(turtlepos,finish_line);i++)
   {
    printf(" ");
   }
   printf("T");
   for(int i=turtlepos;i<finish_line;i++)
   {
    printf(" ");
   }
    printf(" ||\n");

    printf("hare won the race\n"); 
     status = false;
     sleep(1);
	}

           // printf("hare pos : %d\n",hare_pos);
     //       // printf("turtle pos : %d\n\n",turtle_pos);  
     // if(turtlepos >= finish_line)
     //     {printf("turtle won the race\n");
    	// 	status = false;
    	// }
     // else if( harepos >= finish_line)
     // {
     //     printf("hare won the race\n"); 
     //     status = false;
     // }
     
}


void signalhandler(int signo)
{
	if(signo == SIGINT)
	{
		int pos = rand()%finish_line;
		printf("enter hare pos\n");
		scanf("%d",&pos);
		harepos = pos;
		pos = rand()%finish_line;
		printf("enter turtle pos\n");
		scanf("%d",&pos);
		turtlepos = pos;
	}
}

int main()
{
	pthread_t hare,turtle,track;

    if(signal(SIGINT,signalhandler) == SIG_ERR)
    {
    	printf(" failed to form signal handle. \n");
    }

    printf("enter finsh line pos \n");
    scanf("%d",&finish_line);

     printf("enter hare pos \n");
    scanf("%d",&harepos);


     printf("enter turtle pos \n");
    scanf("%d",&turtlepos);

    pthread_create(&track,NULL,trackfile,NULL);
	pthread_create(&hare,NULL,harefile,NULL);
	pthread_create(&turtle,NULL,turtlefile,NULL);
	
	pthread_join(track,NULL);
	pthread_join(hare,NULL);
	pthread_join(turtle,NULL);
	

	return 0;
}