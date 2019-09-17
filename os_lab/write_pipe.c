// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 


int main()
{
    int fd;
 
    // FIFO file path
    char * myfifo = "/tmp/myfifo";
    char* read_file = "/tmp/read_file";
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);
    mkfifo(read_file,0666);
 
    char arr1[80], arr2[80];

    while (1)
    {
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);
 
        // Take an input arr2ing from user.
        // 80 is maximum length
        fgets(arr2, 80, stdin);

        printf(" what is the file \n ");
 
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, arr2, sizeof(arr2));
        close(fd);

        //fd = open(read_file, O_RDONLY);
        fd = open(myfifo, O_RDONLY);
        // Read from FIFO
        read(fd, arr1, sizeof(arr1));
 
        // Print the read message
        printf("User2: %s\n", arr1);
        close(fd);
 
    }
    return 0;
}