
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t  pidpc1;
    pidpc1 = fork();
	if(pidpc1 <0 )
		{
			perror("fork");
		}
	else if(pidpc1 == 0)
	{
		pid_t pidcc = fork();

		if(pidcc < 0 )
		{
			perror("fork");
		}
		else if( pidcc == 0)
		{
			printf("child of child 1 \n");
			printf("parent id :- %d current process id:- %d\n",getpid(),getppid());
		}
		else
		{
			wait(NULL);
			printf("child 1 \n");
			printf("parent id :- %d current process id:- %d\n",getpid(),getppid());
		}

	}
	else
	{
		wait(NULL);
		pid_t pidpc2 = fork();

		if(pidpc2 < 0 )
		{
			perror("fork");
		}

		else if(pidpc2 == 0)
		{
			printf("child 2 \n");
			printf("parent id :- %d current process id:- %d\n",getpid(),getppid());
		}
		else 
		{
			wait(NULL);
			printf("main process 1 \n");
			printf("parent id :- %d current process id:- %d\n",getpid(),pidpc1);
		}
	}

}