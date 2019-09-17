#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<ncurses.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>

static int T , H;
static int MAX_TRACK;
static int HARE_SPEED;
static int TORTOISE_SPEED;
static int SLEEP_TIME;
static int IS_FAR;
static int TORTOISE_WAITING_TIME;
static int HARE_WAITING_TIME;
static int go;

int kbhit(void)
{
        struct timeval        timeout;
        fd_set                readfds;
        int                how;

        /* look only at stdin (fd = 0) */
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);

        /* poll: return immediately */
        timeout.tv_sec = 0L;
        timeout.tv_usec = 0L;

        how = select(1, &readfds, (fd_set *)NULL, (fd_set *)NULL, &timeout);
        /* Change "&timeout" above to "(struct timeval *)0"       ^^^^^^^^
         * if you want to wait until a key is hit
         */

        if ((how > 0) && FD_ISSET(0, &readfds))
                return 1;
        else
                return 0;
}

void *tortoise(void *arg)
{

  while(T < MAX_TRACK && H < MAX_TRACK)
  {

    while(go == 1){}
    T++;
    sleep(TORTOISE_WAITING_TIME);

  }
  return NULL;

}
void *hare(void* arg)
{

  while(T < MAX_TRACK && H < MAX_TRACK)
  {

    while(go == 1){}
    H++;
    if((H-T) > IS_FAR) sleep(SLEEP_TIME);
    else sleep(HARE_WAITING_TIME);

  }
  return NULL;

}
void *print_pos(void *arg)
{

  initscr();
  //noecho();
  curs_set(FALSE);
  while(T < MAX_TRACK && H < MAX_TRACK)
  {

    sleep(1);
    while(go == 1){}
    // printf("\033[H\033[J");
    // printf("T -> %d\nH -> %d\n",T,H);
    clear();
    mvprintw(0, T, "T");
    mvprintw(1, H, "H");
    // mvprintw(2, T, "/___\\/ ");
    // mvprintw(3, T, " U U   ");
    // mvprintw(4, H, "     (\\\\ ");
    // mvprintw(5, H, "     \\|| ");
    // mvprintw(6, H, "  __ (_\";");
    // mvprintw(7, H, " /    \\  ");
    // mvprintw(8, H, "{}___)\\)_");
    //
    // mvprintw(0, MAX_TRACK, "|");
    // mvprintw(1, MAX_TRACK, "|");
    refresh();
    while(go == 1){}

  }
  if(T >= MAX_TRACK)
    printf("\n\nTortoise won!\n");
  else
    printf("\n\nHare won!\n");

  sleep(5);
  endwin();
  return NULL;

}
void *report(void *arg)
{

  pthread_t hare_id, tortoise_id, print_id;
  pthread_create(&hare_id, NULL, hare, NULL);
  pthread_create(&tortoise_id, NULL, tortoise, NULL);
  pthread_create(&print_id, NULL, print_pos, NULL);


  pthread_join(hare_id, NULL);
  pthread_join(tortoise_id, NULL);
  pthread_join(print_id, NULL);
  return NULL;

}
void* god(void *arg)
{

  while (T < MAX_TRACK && H < MAX_TRACK)
  {

      if(kbhit())
      {

        go = 1;
        //printf("\033[H\033[J");
        clear();
        char racer;
        int pos;

        printf("\nT = %d\nH = %d\n",T,H);
        scanf("%c",&racer);
        scanf("%d",&pos);

        printf("\nWhat are god's order?\n");
        //printf("%c %d\n",racer,pos);
        if(racer == 'T')//strcmp(racer, "T") == 0)
        {
          T = pos;
          printf("came here! %d\n",T);
        } //
        else if(racer == 'H')//strcmp(racer, "H") == 0)
          H = pos;
        else
        printf("Press H or T\n");

        go = 0;

      }

  }
  return NULL;

}

int main()
{

    T = 0;
    H = 0;
    MAX_TRACK = 78;
    HARE_SPEED = 4;
    TORTOISE_SPEED = 1;
    SLEEP_TIME = 20;
    IS_FAR = 20;
    TORTOISE_WAITING_TIME = 2;
    HARE_WAITING_TIME = 1;
    go = 0;

    pthread_t report_id, god_id;
    pthread_create(&report_id, NULL, report, NULL);
    pthread_create(&god_id, NULL, god, NULL);
    pthread_join(report_id, NULL);
    pthread_join(god_id, NULL);
    return 0;

}
