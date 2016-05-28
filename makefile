all:project1  

project1: shell.c 
	gcc shell.c -o shell
	./shell

clean:
	rm shell


