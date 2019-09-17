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

#define buff_max 1024
int win = 0;
#define finish_line 200

int main()
{
	int t = 3;
	int* hare_pos;
	//int* turtle_pos;

 	printf("please enter position \n of the hare and turtle respectively\n");
 	int x;
	scanf("%d",&x);
	hare_pos = &x;
	//scanf("%d",turtle_pos);

	char hare_add[23] = "/tmp/hare";
	char** hare_code_add;
	hare_code_add[0] = "hare";
	hare_code_add[1] = NULL;
	// char tur_add= '/tmp/turtle';
	// char rep_har_add= '/tmp/report_har';
	// char rep_tur_add= '/tmp/report_tur';
	// char god_hare_add= '/tmp/god_tur';
	// char god_tur_add= '/tmp/god_har';

	int fd[5];
	mkfifo(hare_add,666); // 666 allows to have the read and write all the files
	int *re;
	re = malloc(1*sizeof(int));
	// mkfifo(tur_add,666);
	// mkfifo(rep_har_add,666);
	// mkfifo(rep_tur_add,666);
	// mkfifo(god_tur_add,666);
	// mkfifo(god_hare_add,666);
    printf("\n file is open in main \n");
    fd[0] = open(hare_add,O_WRONLY);

    write(fd[0],hare_pos,sizeof(hare_pos));
    printf("\n go to hell \n");
    close(fd[0]);
    fd[0] = open(hare_add,O_RDONLY);
    read(fd[0],re,sizeof(int));
    close(fd[0]);
    printf("\n okeu \n");
    // fd[2] = open(rep_har_add,O_WRONLY);
    // write(fd[2],hare_pos,sizeof(hare_pos)+1);
    // close(fd[2]);
    //fd[1] = open(hare_add,O_WRONLY);
    // write(fd[1],hare_pos,sizeof(hare_pos)+1);
    // close(fd[1]);
    // fd[3] = open(rep_har_add,O_WRONLY);
    // write(fd[0],hare_pos,sizeof(hare_pos)+1);
    // close(fd[3]);
    // fd[0] = open(hare_add,O_WRONLY);
    // write(fd[0],hare_pos,sizeof(hare_pos)+1);
    // close(fd[0]);
    // fd[3] = open(rep_har_add,O_WRONLY);
    // write(fd[0],hare_pos,sizeof(hare_pos)+1);
    // close(fd[3]);

	//while(true)
	{

	pid_t hare;
	hare = fork();

	if(hare == 0)
	{
		// int fd_h;
		// char* hare_pos;
		// char buff[buff_max];
		// fd_h = open("hare_pos.txt",O_RDWR | O_CREAT | O_APPEND,0666);
		// read(fd_h,buff,buff_max);
		// hare_pos = buff;
		// //printf("hare pos %s\n",buff);
		// //printf("%s\n", buff);
		// int x;
		// x= atoi(hare_pos);
		// //printf("x =  %d\n", x);
		// if(x > finish_line )
		// {
		// 	printf("\n hare wins the race\n");
		// 	win = 1;
		// }
		// // else
		// // {
		// // 	move_of_hare(&x);
		// // }
		// x = x+5;

		//write(&x,sizeof(int*),1,fd_h);
		printf("\n going to the file \n");
		execv(hare_code_add[0],hare_code_add);
		//printf("\n in hare\n");
		//sleep(20);





	}
	else
	{
		// pid_t turtle;;
		// turtle = fork();
		// int fd_t;
		// if(turtle == 0)
		// {

		// 	printf("\n in turtle\n");
		// }
		// else
		// {
		// 	pid_t report;
		// 	report = fork();

		// 	if(report == 0)
		// 	{
		// 		printf("\n in report \n");
		// 	}
		// 	else
		// 	{

		// 		printf("\n in god \n");
		// 	}
		

		}
		// char* turtle_pos;
		// char buff[buff_max];
		// fd_t = open("turtle_pos.txt",O_RDWR | O_CREAT | O_APPEND,0667);
		// read(fd_t,buff,buff_max);
		// turtle_pos = buff;
		// //printf("\n turtle pos = %s\n",buff);
		// //printf("%s\n", buff);
		// int y = atoi(turtle_pos);
		// //printf("x =  %d \n",y);
		// if(y > finish_line)
		// {
		// 	printf("\n turtle wins the race \n");
		// 	win = 2;
		// }
		// else
		// {
		// 	move_of_turtle(&y);
		// }

	}

	return 0;
}

	

 
	

