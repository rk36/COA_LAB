#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
#define buff_size 1024

int main()
{
 
 int fd;
 int* val;
 char hare_add[23]= "/tmp/hare";
 
 //fd = open(hare_add,O_RDONLY);
 printf("\n file is open \n");
 read(fd,val,sizeof(int));
 printf("\n file is read \n");
 printf("\n val %d\n",*val);
 close(fd);
 return 0;


}