Author:Rishabh Gupta Roll no: 16CS01018 Date: August 2, 2018

Welcome to Readme.txt for assg3 . assg2 has been completed in lab and shown to TA. The copy is on lab computer. It being very trivial has been left out. 


 OS Assignment 3 - Perform twice,square,half operations on a number by keeping the process ID of all the processes same.

	This can be done by calling execvp command in each process ,so that the new process replaces the old one while keeping the process ID same.

	To run, execute the following command :

	gcc main.c -o main
	gcc square.c -o square
	gcc twice.c -o twice
	gcc half.c -o half
	
	Example :
	
	Command Line Input : ./main square twice half 3
	Output : 9 	

Code is available in main.c square.c half.c double.c . Please ignore other files if any. The first file that runs is main.

Author's note: 
I have already removed my compiled file to prevent any confusion. 
This code is written using help from various resources and inputs from
different people including batchmates, TAs and Lab Professor.
We have not been formally taught these concepts in theory class till the date
of writting this file. Kindly overlook any mistakes.

Status: The file completely fulfills the requirements of the code. 


Please note : My assignment is already evaluated by TA. (edited on Aug 9,2018) 
