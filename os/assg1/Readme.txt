Author:Rishabh Gupta Roll no: 16CS01018 Date: August 2, 2018

Welcome to Readme.txt for assg2


TO COMPILE this file:
 gcc main.c -o main
TO RUN the main using:
./main

This will now start a shell. The shell displays your current location
followed by '>'.
 TO QUIT write:
exit

Code is available in main.c. Please ignore other files.

Nearly all commands that i am aware of  except piping are implemented. 

Author's note: 
I have already removed my compiled file to prevent any confusion. 
This code is written using help from various resources and inputs from
different people including batchmates, TAs and Lab Professor.
We have not been formally taught these concepts in theory class till the date
of writting this file. Kindly overlook any mistakes.

Status: The file completely fulfills the requirements of the code. Few
	extra concepts have been also been implemented.

Commands tested by me:
cd, ls, ls -a, cd .. , cd / , mkdir, rmdir, pwd, touch, cat, man,
nano (on my computer its running, this readme is written using nano), rm, cd etc

WORKING AND EXPLAINATION: This file is basically divided into 3 parts:

1. Read line 
2. parse the line
3. execute

shell_read_line is nothing but storing the command in a character array.
Another efficent way to do it using readline(). This pointer is returned
in line whih is then sent for parsing on basis of " " using shell_split_line
This is done using the famous command strtok. This parse array 
returns an array of strings. This is processed by shell_execute.
shell execute runs on two things : shell_launch (which uses execvp) and
set of commands which execvp cannot run like cd, exit, help.
So we make a note of commands which are to be run but are not available
to run using execvp and loop through it to check if user is running them.
if not, we use shell_launch. Shell launch runs of a simple logic:
if its a child process use execvp
else if its a parent wait for child process to complete
else throw an error by checking pid
This all keeps running inside loop shell_loop. 
This sums up the explaination for making the shell.

Please note : My assignment is already evaluated by TA. (edited on Aug 9,2018) 
