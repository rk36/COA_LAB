#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

pid_t pid,pid1;
//* fork a child process *//
pid = fork();
if (pid < 0) { 
fprintf(stderr, "Fork Failed");
return 1;
}
else if (pid == 0) 
{ 
pid1 = getpid();
printf("child: pid = %d",pid); 
//I* A *I
printf("child: pid1 = %d",pid1); 
}

else 
//   I* parent process *I
{
pid1 = getpid() ;
printf("parent: pid = %d",pid);
printf("parent: pid1 = %d" ,pid1); 
wait(NULL);
}
return 0; 
}