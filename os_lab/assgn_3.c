#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for using getcwd() for path and directory
#include <string.h>
#include <sys/stat.h>
#include <dirent.h> // for using scandir() for ls;
#include <fcntl.h> // for file operation
#include <error.h> // for writing error 
#include <sys/types.h>
#include <sys/wait.h> // for using execve


void parsed(char* input,char** parsed_string);


int main()

{

	
  	char* temp;
  	char** parsed_string;
  	parsed_string = malloc(1024*sizeof(char*));
  	temp = malloc(1024* sizeof(char));
  	scanf("%[^\n]s",temp);

  	parsed(temp,parsed_string);

  	int i=0;
  	printf("\n");
  	// while(parsed_string[i]!= NULL)
  	// {
  	// 	printf("%s\n",parsed_string[i]);
  	// 	i++;

  	// }
		int count = 0;
		
		char* tempchar;
		tempchar = malloc(1024*sizeof(char));
		char new[3] ="./";
		//strcpy(tempchar,new);
		//printf("%s\n", tempchar);
		//printf("value of %d",i);
  		
  		
  		//pid_t pid=fork();
    		
			//if (pid==0) 
			 /* child process */

			    //static char *argv[]={parsed_string[0],NULL};

  				//parsed_string 
  				strcpy(tempchar,new);
  				strcat(tempchar,parsed_string[0]);
  				//strcpy(parsed_string[0],tempchar);
  				//printf("\n this %s\n",tempchar );


  				//printf(" \n not repeating \n");
			    execvp(tempchar,parsed_string);
			
			    	
			    //printf("%s\n",parsed_string[1]);
			    //exit(127); /* only if execv fails */
				
			
    		// else 
    		// { /* pid!=0; parent process */
      //   	waitpid(pid,0,0); /* wait for child to exit */
    		// }
    	

  //printf("%s\n", parsed_string[i-1]);

 return 0; 
}




void parsed(char* input,char** parsed_string)
{
	int i;
	char *temp;
	temp = malloc(1024* sizeof(char));
	strcpy(temp,input);

	for(i=0;i<1024;i++)
	{
		parsed_string[i] = strsep(&temp," ");
		//parsed_string[i] = strsep(parsed_string," ");
		if(parsed_string[i] == NULL)
			break;
		if(strlen(parsed_string[i]) == 0)
			i--;
	}
	parsed_string[i] = NULL;
	//printf("%s\n",parsed_string[i-1] );

}


void runPipedCommands(char** command) 
{
    //int numPipes = countPipes(userInput);
	int no_pipes;
	while(command[no_pipes]!= NULL)
	{
		no_pipes +=1;
	}

    int status;
    int i = 0;
    pid_t pid;

    int pipefds[2*no_pipes];

    for(i = 0; i < (no_pipes); i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }


    int j = 0;
    int cmd_no = 0;
    while(command[cmd_no] != NULL) {
        pid = fork();
        if(pid == 0) {

            //if not last command
            if(command[cmd_no] !=  NULL){
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*numPipes
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror("dup2");///j-2 0 j+1 1
                    exit(EXIT_FAILURE);

                }
            }


            for(i = 0; i < 2*no_pipes; i++){
                    close(pipefds[i]);
            }

            if( execvp(command[i],command) < 0){
                    //perror(*command->arguments);
                    exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }

        cmd_no +=1;
        j+=2;
    }
    /**Parent closes the pipes and wait for children*/

    for(i = 0; i < 2 * no_pipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < no_pipes + 1; i++)
        wait(&status);
}