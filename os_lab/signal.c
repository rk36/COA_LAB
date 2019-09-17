#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
// user -defined signal handler for alarm. 

void alarm_handler(int signo)
{ 
	if (signo == SIGALRM)
		{ 
			printf("alarm goes off\n");
	 	}
	else if(signo == SIGINT)
	{
		printf("\nclose the program\n");
		exit(0);
	}
	else if(signo == SIGTSTP)
	{
		printf("\n signal to kill\n");
		exit(0);
	}
} 



int main(void)
{ // register the signal handler 
	if (signal(SIGALRM , alarm_handler) == SIG_ERR)

	{ 	
		printf (" failed to register alarm handler .") ;
		exit (1);
	}
	if (signal(SIGINT , alarm_handler) == SIG_ERR)

	{ 	
		printf (" failed to register alarm handler .") ;
		exit (1);
	}
	if (signal(SIGTSTP , alarm_handler) == SIG_ERR)

	{ 	
		printf (" failed to register alarm handler .") ;
		exit (1);
	}

	alarm (3);      // set alarm to fire in 3 seconds .
	while (1) 
	{ 
	        //alarm (3); 
		sleep (2);
		printf(" so the alarm is going off \n"); 
		alarm(3);

	}     // wait until alarm goes off
}
