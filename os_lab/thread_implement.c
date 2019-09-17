#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>

// void create_thread()
// {
// 	pthread_t hi;
// 	pthread_create(&hi,NULL,printhi,NULL);
// 	pthread_join(hi,NULL)
// }


/*
pthread_join(threadname,attr)
it leads to waiting of the thr

#include <pthread.h>

       int pthread_join(pthread_t thread, void **retval);

The pthread_join() function waits for the thread specified by thread to
terminate.  If that thread has already terminated, then  pthread_join()
returns immediately.  The thread specified by thread must be joinable.


After  a  successful  call  to pthread_join(), the caller is guaranteed
that the target thread has terminated.  The caller may then  choose  to
do any clean-up that is required after termination of the thread (e.g.,
freeing memory or other resources that were  allocated  to  the  target
thread).


ctrl -z does not lead to termination but forcefully stops a program, but the program
still exist in the background



*/



void* printhi()
{
	int x=0;

	while(1)
	{
	printf("hi -%ld, -%d\n",pthread_self(),x);
	x++;
	sleep(1);
	}
}

void* printhello()
{
	while(1)
	{
	printf("hello\n");
	sleep(1);
	//pthread_join(hi,NULL);
	}
}

void signalwork(int signo)
{
	if(signo == SIGINT)
	{
	 pthread_t hi;
	 pthread_create(&hi,NULL,printhi,NULL);
	//  pthread_join(hi,NULL);
	}
}

int main()
{
	//pthread_t hi;
	pthread_t hello;

	if(signal(SIGINT,signalwork) == SIG_ERR)
	{
		printf("failed to form signal handling \n");
	}
	//pthread_create(&)
	pthread_create(&hello,NULL,printhello,NULL);
	//pthread_create(&hi,NULL,printhi,NULL);
	//pthread_create(&hello,NULL,printhello,NULL);
	
	//pthread_join( hi,NULL);
	pthread_join(hello,NULL);

	return 0;

}