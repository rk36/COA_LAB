//
// Created by rishabh on 7/8/18.
//

//
// Created by rishabh on 7/8/18.
//

//
// Created by rishabh on 7/8/18.
//
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main(int argc, char *argv[]) {
    char inp[512];
    inp[0] = '.';
    inp[1] = '/';
    int i = 0;
    for (i = 2; i < 512; i++) {
        if (argv[0][i - 2] == '\0')break;
        else {
            inp[i] = argv[0][i - 2];
        }
    }
    inp[i] = '\0';
    int x = atoi(argv[argc - 1]) / 2;
    sprintf(argv[argc - 1], "%d", x);
    if (argc == 1) {
        printf("%d\n", atoi(argv[argc - 1]));
        return 0;
    }
        argv++;
        execvp(inp, argv);
        return 0;
}
