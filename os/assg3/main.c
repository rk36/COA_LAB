//
// Created by rishabh on 7/8/18.
//
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    argv++;
    char inp[512];
    inp[0] = '.';
    inp[1] = '/';
    int i = 0;
    for(i = 2;i<512;i++){
        if(argv[0][i-2]=='\0')break;
        else{
            inp[i] = argv[0][i-2];
        }
    }
    inp[i] = '\0';
    argv++;
    execvp(inp,argv);
    return 0;
}