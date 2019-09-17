#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>


void handler(int signno)
{
	if(signno==SIGALRM)
	printf("Alarm \n");
}
void handle_sigint(int sig)
{
    printf("Caught signal sigint%d\n", sig);
}
void handle_sigtstp(int sig)
{
    printf("Caught signal sigTstp%d\n", sig);
    exit(0);
}


int main()
{
	if(signal(SIGALRM,handler)==SIG_ERR)
	{
	printf("failed to register alarm handler\n");
	exit(1);
	}
	if(signal(SIGINT,handle_sigint)==SIG_ERR)
	{
	printf("failed to register SIGINT\n");
	exit(1);
	}
	if(signal(SIGTSTP,handle_sigtstp)==SIG_ERR)
	{
	printf("failed to register SIGINT\n");
	exit(1);
	}
	//alarm(2);
	while(1)
	{
		raise(SIGALRM);
		sleep(2);
	}
	return 0;
}