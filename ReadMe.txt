Name:Divya Ladwa B#: B00594267
Name:Ankit Mahale B#: B00594269

Commands:
Untar the file:tar ­-xvf dladwa1_amahale2_assign1.tar.gz
To run the file : make 
make clean after every run.

Tar file contains:
shell.c(main program that contains all code)
makefile
ReadMe.txt
commandLine.c
./commandLine
insertionsort.c
./insertionsort
input.txt
output.txt


This code has been tested on Bingsuns.
Tested all the commands using 2 file:

commandLine.c file to demonstrate foreground and background process with multiple arguments.

minish> ls 
minish> ls &
minish> ./commandLine 12 23 34 45 45
minish> ./commandLine 12 23 34 45 45 &
minish> ./commandLiine < input.txt (input.txt contains the argument list:12 23 34 45 45)
minish> ./insertionsort > output.txt (output.txt contains the sorted list after insertion sort is done)
minish> ./commandLiine < input.txt &
minish> ./insertionsort > output.txt &
minish> ./commandLiine < input.txt > output.txt (input.txt contains the argument list:12 23 34 45 45 and output.txt contains output of commandLine.c program)
minish> ./commandLiine < input.txt > output.txt &
minish> ls -l | wc -l
minish> ls -l | wc -l | less
minish> [Ctrl-C]
minish> [Ctrl-Z]
minish> kill pid(pid is the stopped process or a process in background)
minish> exit
minish> pwd
minish>
 



