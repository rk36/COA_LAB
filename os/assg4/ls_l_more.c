#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char** argv)
{

  int fd[2];
  if(pipe(fd) == -1)
  {
    printf("Piping problem!\n");
    exit(0);
  }

  pid_t pid = fork();
  if(pid < 0)
  {
    printf("Forking problem!\n");
    exit(0);
  }
  else if(pid > 0)
  {

    //dup(STDOUT_FILENO);//copies the stdout file descriptor to the lowest index
    dup2(fd[1], STDOUT_FILENO);//stdout points to what writing end of pipe is pointing

    close(fd[1]);
    close(fd[0]);

    char* arg[] = {"ls","-l",NULL};
    execvp(arg[0],arg);
    //system("dir");

    wait(NULL);

  }
  else
  {

    int MAX_SIZE = 3000;
    int NO_LINES = 10;

    char list[MAX_SIZE];
    char dummy_var;

    close(fd[1]);//closes the writing end of pipe
    read(fd[0], list, MAX_SIZE);
    int i;

    int stops[100],pos=0;
    stops[pos++] = 0;
    for(i=0;i<=strlen(list);i++)
      if(list[i] == '\n')
        stops[pos++] = i+1;

    for(int i=0;i<pos;i++)
      printf("%d\n",stops[i]);

    printf("length = %d",(int)strlen(list));

    int count = 0,start = 0;
    i=0;
    //int flag = 0;
    printf("\033[H\033[J");

    do
    {
      for(i=stops[start];i<=strlen(list);i++)
      {

        if(list[i] == '\n')
          count++;
        printf("%c",list[i]);
        if(count == NO_LINES)
        {
          printf("\n\nmore");
          scanf("%c",&dummy_var);

          count = 0;
          //printf("\033[H\033[J");
          start++;
          break;
        }
      }
    }while(i <= strlen(list));

  }
}
