#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>

int main(int argc, char** argv)
{

  int fd1[2];
  int fd2[2];

  char fixed_str[] = "world";
  if(pipe(fd1) < 0)
  {
    printf("Piping error!\n");
    exit(0);
  }
  if(pipe(fd2) < 0)
  {
    printf("Piping problem!\n");
    exit(0);
  }

  char input_str[100];
  scanf("%s",input_str);

  pid_t pid = fork();
  if(pid < 0)
  {
    printf("Forking problem!\n");
    exit(0);
  }
  else if(pid > 0)
  {

    char concat_str[200];

    close(fd1[0]);//closing the reading end of pipe1
    write(fd1[1], input_str, strlen(input_str)+1);//sending the input string through pipe1 to child process
    close(fd1[1]);//closing the writing end of pipe1
    wait(NULL);

    close(fd2[1]);//closing the writing end of pipe2
    read(fd2[0], concat_str, 200);//getting the concatted string from child process
    printf("--> %s\n",concat_str);
    close(fd2[0]);//closing the reading end of pipe2

  }
  else
  {

    char concat_str[200];

    close(fd1[1]);//closing the writing end of pipe1
    read(fd1[0], concat_str, 200);//reading the input string from parent

    strcat(concat_str, fixed_str);//concating the given string with the fixed string

    close(fd1[0]);//closing the reading end of pipe1
    close(fd2[0]);//closing the reading end of pipe2

    write(fd2[1], concat_str, strlen(concat_str)+1);//sending the concatted string to parent
    close(fd2[1]);//closing the writing end of pipe2

    exit(0);

  }
}
