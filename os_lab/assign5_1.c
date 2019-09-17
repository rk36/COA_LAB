
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>

int turtle_pos;
int hare_pos;
int total_dis;
int mode = 0;
float x;
void signal_handler(int signo)
{

    if(signo == SIGUSR1)
    {
        //scanf(" %f",&x);
        turtle_pos = 0;
        mode = 1;

    }
    else if(signo == SIGUSR2)
    {

        //scanf(" %f",&x);
        hare_pos = 0;
        mode = 2;
    }
    else
        printf("use hare or turtle\n");
}
int main(int argc,char* argv[])
{
    int i,child_id;
    pid_t parent_pid = getpid();
    pid_t pid,gods_pid;
    int status = 0,finish = 1;
    int total_dis;
    int main_to_report[2];
    int main_to_hare[2];
    int main_to_turtle[2];
    int turtle_to_main[2];
    int hare_to_main[2];
    printf("distance\n");
    scanf(" %d",&total_dis);
    signal(SIGUSR1,signal_handler);
    signal(SIGUSR2,signal_handler);
    pipe(main_to_report);
    pipe(turtle_to_main);
    pipe(hare_to_main);
    pipe(main_to_turtle);
    pipe(main_to_hare);
    for(i = 0;i < 4;i++)
    {
        pid = fork();
        if((pid != 0) && i == 3)
          gods_pid = pid;
        if(pid == 0)
          break;
    }
    
 	if(i == 0)
    {
       close(turtle_to_main[0]);
       close(main_to_turtle[1]);
       char msg[10];
       char turt_temp_pos[6];
       char hare_temp_pos[6];
       int turtle_speed = 1;
       while(status != finish)
       {
          read(main_to_turtle[0],msg,sizeof(msg));
          strncpy(turt_temp_pos,msg,strstr(msg," ")-msg) ;
          strcpy(hare_temp_pos,strstr(msg," ")+1);
          hare_pos = atoi(hare_temp_pos);
          turtle_pos = atoi(turt_temp_pos);
          turtle_pos += turtle_speed;
          write(turtle_to_main[1],&turtle_pos,sizeof(turtle_pos));
          if((turtle_pos >= total_dis) || (hare_pos >= total_dis))
             break;   
       }
    }
    else if(i == 1) 
    {
        close(hare_to_main[0]);
        close(main_to_hare[1]);
        char msg[10];
        char turt_temp_pos[6];
        char hare_temp_pos[6];
        int hare_speed = 15;
        int min_distance = 30;
        int hare_crazy_speed = 20;
        int sleeping_time = 2;
        int sleeping = 0;
        int current =0;
        int token = 0;
        int threshold = 20;
        while(status != finish)
        {
          read(main_to_hare[0],msg,sizeof(msg));
          token++;
          strncpy(turt_temp_pos,msg,strstr(msg," ")-msg) ;
          strcpy(hare_temp_pos,strstr(msg," ")+1);
          hare_pos = atoi(hare_temp_pos);
          turtle_pos = atoi(turt_temp_pos);
          if((hare_pos- turtle_pos)>= threshold || sleeping)
			{
				if(!sleeping)
				{
					current = token;
					sleeping = 1;
				}
				if(current+sleeping_time>token && sleeping)
				{
					goto jump;
				}
				else
				{
					sleeping = 0;
				}
			}
			if(hare_pos >= turtle_pos)
			hare_pos += hare_speed;
			else
			hare_pos += hare_crazy_speed;
			jump:
          write(hare_to_main[1],&hare_pos,sizeof(hare_pos));
          if((turtle_pos >= total_dis) || (hare_pos >= total_dis))
             break;
        } 
    }

    else if(i == 2) 
    {
        close(main_to_report[1]);
        char msg[10];
        char turt_temp_pos[5];
        char hare_temp_pos[5];
        while(status != finish)
        { 
           read(main_to_report[0],msg,sizeof(msg));
           strncpy(turt_temp_pos,msg,strstr(msg," ")-msg) ;
           strcpy(hare_temp_pos,strstr(msg," ")+1);
           hare_pos = atoi(hare_temp_pos);
           turtle_pos = atoi(turt_temp_pos);
           //printf("\033[H\033[J")
           system("clear");

           for(int i=0;i <hare_pos;i++)
           {
            printf(" ");
           }
           printf("H");
           for(int i=hare_pos;i<total_dis;i++)
           {
            printf(" ");
           }
           printf(" ||\n");

           for(int i=0;i <turtle_pos;i++)
           {
            printf(" ");
           }
           printf("T");
           for(int i=turtle_pos;i<total_dis;i++)
           {
            printf(" ");
           }
            printf(" ||\n");

           // printf("hare pos : %d\n",hare_pos);
           // printf("turtle pos : %d\n\n",turtle_pos);  
           if((turtle_pos >= total_dis) || (hare_pos >= total_dis))
           {
             if(turtle_pos >= total_dis)
                 printf("turtle won the race\n");
             else
                 printf("hare won the race\n"); 
             break;
           }
        }

    }

    else if(i==3)
    {
       char line[10];
       while(status != finish)
       {
          printf("Select turtle or hare\n");
          scanf("%s",line);
          if(strstr(line,"turtle") != NULL)
              kill(parent_pid,SIGUSR1);
          else if(strstr(line,"hare") != NULL)
              kill(parent_pid,SIGUSR2);
          else
              printf("select from turtle or hare\n");
       }
    }

    else if(i == 4)
    {
       close(main_to_hare[0]);
       close(turtle_to_main[1]);
       close(hare_to_main[1]);
       close(main_to_report[0]);
       close(main_to_turtle[0]);
       char msg_to_report[10] = "just";
       char turt_temp_pos[5];
       char hare_temp_pos[5];
       while(status != finish)
       {

           sprintf(turt_temp_pos,"%d",turtle_pos);
           sprintf(hare_temp_pos,"%d",hare_pos);
           strcpy(msg_to_report,turt_temp_pos);
           strcat(msg_to_report," ");
           strcat(msg_to_report,hare_temp_pos);
           write(main_to_report[1],msg_to_report,sizeof(msg_to_report));
           write(main_to_turtle[1],msg_to_report,sizeof(msg_to_report));
           write(main_to_hare[1],msg_to_report,sizeof(msg_to_report));
           read(hare_to_main[0],&hare_pos,sizeof(hare_pos));
           read(turtle_to_main[0],&turtle_pos,sizeof(turtle_pos));
           if(mode==1)
           	turtle_pos = 0;
           if(mode==2)
           	hare_pos = 0;
           mode = 0;
           if((turtle_pos >= total_dis) || (hare_pos >= total_dis))
           {
             kill(gods_pid,SIGQUIT);
             sprintf(turt_temp_pos,"%d",turtle_pos);
             sprintf(hare_temp_pos,"%d",hare_pos);
             strcpy(msg_to_report,turt_temp_pos);
             strcat(msg_to_report," ");
             strcat(msg_to_report,hare_temp_pos);
             write(main_to_report[1],msg_to_report,sizeof(msg_to_report));
             if(turtle_pos >= total_dis)
                 write(main_to_hare[1],msg_to_report,sizeof(msg_to_report));

             else
                 write(main_to_turtle[1],msg_to_report,sizeof(msg_to_report)); 

             break;
           }
           sleep(1);              
       }
       wait(NULL);
       wait(NULL);
       wait(NULL);
       wait(NULL);
    } 
  return(0);
}