
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
			//printf("child of child 1 \n");
			printf("child of child 1 \n parent id :- %d current process id:- %d\n",getpid(),getppid());
		}
		else
		{
			wait(NULL);
			pid_t pidcc2 = fork();

			if(pidcc2 < 0 )
			{
				perror("fork");
			}
			else if( pidcc2 == 0)
			{
				//printf("child of child 1 \n");
				printf("child of child 1 \n parent id :- %d current process id:- %d\n",getpid(),getppid());
			}
			else
			{
			//printf("child 1 \n");
				wait(NULL);
				printf("child 1 \n parent id :- %d current process id:- %d\n",getpid(),getppid());
			} 
		}

	}
	else
	{
		pid_t pidpc2 = fork();

		if(pidpc2 < 0 )
		{
			perror("fork");
		}

		else if(pidpc2 == 0)
		{
			pid_t pidcc = fork();

		if(pidcc < 0 )
		{
			perror("fork");
		}
		else if( pidcc == 0)
		{
			//printf("child of child 2 \n");
			printf("child of child 2 :- parent id :- %d current process id:- %d\n",getpid(),getppid());
		}
		else
		{
			wait(NULL);
			pid_t pidcc2 = fork();

			if(pidcc2 < 0 )
			{
				perror("fork");
			}
			else if( pidcc2 == 0)
			{
				//printf("child of child 2 \n");
				printf("child of child 2 \n parent id :- %d current process id:- %d\n",getpid(),getppid());
			}
			else
			{
			//printf("child 2 \n");
				wait(NULL);
				printf("child 2 \n parent id :- %d current process id:- %d\n",getpid(),getppid());
			} 
		}

		}
		else 
		{
			wait(NULL);
			//printf("main process 1 \n");
			printf("main process 1 \n parent id :- %d current process id:- %d\n",getpid(),getppid());
		}
	}

}