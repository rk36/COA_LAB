#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <unistd.h> 

int  main(int argc, char *argv[])
{

	int i=0;
	while(argv[i]!= NULL)
	{
		i++;
	}

	
	
	//printf(" twice --> %s\n", argv[i-1]);

		int a = atoi(argv[i-1]);

	a = a<<1; 
	
	//a = 40;
//	itoa(a,buff,10);
	char* tempchar;
	tempchar = malloc(1024*sizeof(char));
	char new[3] ="./";
	strcpy(tempchar,new);
  	strcat(tempchar,argv[1]);
  	//strcpy(argv[1],tempchar);

  	//printf("\n this %s\n",tempchar);
	char z[13] ;
    sprintf(z,"%d",a);
    argv[i-1] = z;

    if(i==2)
	{
		printf(" required value is %s \n",argv[1]);
		return 0;
	}
    execvp(tempchar,++argv);
	//printf("%s\n",argv[i-1]);
	//printf("%s\n",argv[i-1]);
return 0;
	
}