#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <sys/types.h>
#include  <fcntl.h>
#include  <unistd.h>
#include <signal.h>
pid_t childpid;
int length=0;
void  split(char *commandline, char **splitter)
{
     while (*commandline != '\0') {       
          while (*commandline == ' ' || *commandline == '\t' || *commandline == '\n')
               *commandline++ = '\0';     
          *splitter++ = commandline; 
          length++;         
          while (*commandline != '\0' && *commandline != ' ') 
               commandline++;             
     }
     *splitter = '\0';                 
}

void execute_pipes(char **argv)
{
	int filedes[2]; 
	int filedes2[2];
	//printf("\n Inside pipeHandler");
	//printf("\nParg%s",argv[0]);
	//printf("\nParg%s",argv[1]);
	//printf("\nParg%s",argv[2]);
	int num_cmds = 0;
	char *command[256];
	pid_t pid;
	
	int err = -1, end=0,i=0,j=0,k=0,l=0;
	while (argv[l] != NULL){
		if (strcmp(argv[l],"|") == 0){
			num_cmds++;
		}
		l++;
	}
	num_cmds++;
	while (argv[j] != NULL && end != 1){
		k = 0;
		while (strcmp(argv[j],"|") != 0){
			command[k] = argv[j];
			j++;	
			if (argv[j] == NULL){
				end = 1;
				k++;
				break;
			}
			k++;
		}
		command[k] = NULL;
		j++;		
		
		if (i % 2 != 0){
			pipe(filedes); // for odd i
		}else{
			pipe(filedes2); // for even i
		}
		
		pid=fork();
		
		if(pid==-1){			
			if (i != num_cmds - 1){
				if (i % 2 != 0){
					close(filedes[1]); // for odd i
				}else{
					close(filedes2[1]); // for even i
				} 
			}			
			printf("Child process could not be created\n");
			return;
		}
		if(pid==0){
			
			if (i == 0){
				dup2(filedes2[1], STDOUT_FILENO);
			}
			else if (i == num_cmds - 1){
				if (num_cmds % 2 != 0){ // for odd number of commands
					dup2(filedes[0],STDIN_FILENO);
				}else{ // for even number of commands
					dup2(filedes2[0],STDIN_FILENO);
				}
			
			}else{ // for odd i
				if (i % 2 != 0){
					dup2(filedes2[0],STDIN_FILENO); 
					dup2(filedes[1],STDOUT_FILENO);
				}else{ // for even i
					dup2(filedes[0],STDIN_FILENO); 
					dup2(filedes2[1],STDOUT_FILENO);					
				} 
			}
			
			if (execvp(command[0],command)==err){
				kill(getpid(),SIGTERM);
			}		
		}
			
		if (i == 0){
			close(filedes2[1]);
		}
		else if (i == num_cmds - 1){
			if (num_cmds % 2 != 0){					
				close(filedes[0]);
			}else{					
				close(filedes2[0]);
			}
		}else{
			if (i % 2 != 0){					
				close(filedes2[0]);
				close(filedes[1]);
			}else{					
				close(filedes[0]);
				close(filedes2[1]);
			}
		}
				
		waitpid(pid,NULL,0);
				
		i++;	
	}

}


 

void  INThandler(int sig)
{
     char  c;
    if(sig==SIGINT)
     {
        printf("Child Killed"); 
        kill(childpid, SIGTERM); 
     }
	if(sig==SIGTSTP)
	{
		printf("process terminated "); 
        kill(childpid, SIGSTOP);
         signal(SIGTSTP, INThandler);
        
	}
      return;
} 


int cd(char *pth){
   char path[1000];
   strcpy(path,pth);
   char cwd[256]; 
   getcwd(cwd,sizeof(cwd));

   strcat(cwd,"/"); 
   strcat(cwd,path);
   chdir(cwd);    

   return 0;
  }
  

int main(int argc, char **argv)
{
	
     char  commandline[500];             
     char  *splitter[50]; 
     char  buff[500];             
     char  *arguements[10]; 
     char *diff_array[10];
     char* currentDirectory;
     pid_t  pid;
     int status;             
     
      while(1)              
      { 
      	if(signal(SIGINT, INThandler)==SIG_ERR)
      		printf("Cannot catch signal");
      	if(signal(SIGTSTP, INThandler)==SIG_ERR)
      		printf("Cannot catch signal");
         printf("\nminish -> "); 
         length=0;    
          gets(commandline);  
          
          if(!strcmp(commandline,""))continue;            
          printf("\n");
          
          split(commandline, splitter); 
          printf("Length %d ", length);
          if (strcmp(splitter[0], "exit") == 0)  
				killpg(getpgrp(),SIGKILL);     
                  pid = fork();
                  if (pid == -1)
                  {
                      printf("Fork failed\n");
                  } 
                  
                   if (pid == 0)
                  { //printf("child pid %d", getpid());
                 // -------------------------------------------------------------------------------
                int  iter=0,kiter=0;
                          if(splitter[1]!=NULL && !strcmp(splitter[1], "<")  && (splitter[3]!=NULL && !strcmp(splitter[3], ">")))
                          {
                             FILE *fp=fopen(splitter[2], "r");
                           fgets(buff, 255, (FILE*)fp);
                             split(buff,arguements);
                             char arg[10];
                             int set=0;
                             if(splitter[4]!=NULL && !strcmp(splitter[3],">"))
                             {
                             set=1;
                            strcpy(arg,splitter[4]);
                            }
                             fclose(fp);
                             iter=0;kiter=1;
                             while(iter<10)
                           {
                               splitter[kiter]=arguements[iter];
                               iter++;
                               kiter++;
                           } 
                            if(set==1)
                            {
                           		int file1=open(arg,O_WRONLY);
                           		dup2(file1,1);
                           		execvp(splitter[0], splitter);
                           }
                           else
                           {
                           	execvp(splitter[0], splitter);
                           }
                           
                                                      
                         }
                   //---------------------------------------
                   
                   iter=0,kiter=0;
                          if(splitter[2]!=NULL && !strcmp(splitter[2], "<")  && (splitter[4]!=NULL && !strcmp(splitter[4], "|")) && (splitter[6]!=NULL && !strcmp(splitter[6], ">")))
                          {
                          			int pipefd[2];
    							int pid1,pid2;
        						char *grep_args[] = {splitter[0], splitter[1], NULL};
        						char *wc_args[] = {splitter[5], NULL};
        						int  status;
        // make a pipe (fds go in pipefd[0] and pipefd[1])
        						pipe(pipefd);
        						pid1 = fork();
    							pid2=fork();
            					if (pid1 == 0)
            					{
        // replace standard output with output part of pipe
        							int in;
        							in = open("input.txt", O_RDONLY);
        							dup2(in, 0); 
                					dup2(pipefd[1], 1);
                // close unused unput half of pipe
                					execvp(splitter[0], grep_args);
        //close(in);
        //close(pipefd[0]);
           						 }
            					if(pid2 ==0)
            					{
									int out;
        							out = open("output.txt",O_CREAT|O_WRONLY| O_RDONLY| O_APPEND,0755);
                // replace standard input with input part of pipe
                					dup2(pipefd[0], 0);
        							dup2(out, 1);
                // close unused hald of pipe
               						 close(pipefd[1]);
                // execute wc
               						 execvp(splitter[5], wc_args);
        							close(out);               
            					} 
                                                      
                         }
                   
                         
                  //-----------------------------------
                       iter=0,kiter=0;
                          if(splitter[1]!=NULL && !strcmp(splitter[1], "<"))
                          {
                             FILE *fp=fopen(splitter[2], "r");
                           fgets(buff, 255, (FILE*)fp);
                             split(buff,arguements);
                          
                             fclose(fp);
                             iter=0;kiter=1;
                             while(iter<10)
                           {
                               splitter[kiter]=arguements[iter];
                               iter++;
                               kiter++;
                           } 
                            
                           	execvp(splitter[0], splitter);
                                                   
                         }
                         
                         
                         
                         
                         
                          if (splitter[1]!=NULL && !strcmp(splitter[1], "&"))
                          { 
                            //printf("hi1");
                            splitter[1]=NULL;
                            execvp(splitter[0],splitter);
                          }
                         

                        if (splitter[1]!=NULL && !strcmp(splitter[1], ">"))  
                          {
                            int file=open(splitter[2],O_WRONLY);
                            dup2(file,1);
                            execvp(splitter[0], splitter);
                          }
                          if(strcmp(splitter[0],"cd")==0)  
                		 {
                   			 cd(splitter[0]);
                		}
                		  if(!strcmp(splitter[0], "kill"))
                		  {
                		  		splitter[2]=splitter[1];
           						splitter[1]="-9";
           						if(execvp(*splitter,splitter)<0)
           							perror("Kill failed");
                		  }
                         if((splitter[1]!=NULL && !strcmp(splitter[1], "|")) || (splitter[2]!=NULL && !strcmp(splitter[2], "|")) || (splitter[3]!=NULL && !strcmp(splitter[3], "|")))
                          {
                              execute_pipes(splitter);
                          }
                          else
                          {
                            
                            execvp(splitter[0],splitter);
                            
                          }
                        _exit(EXIT_FAILURE); 

                  
                }
                  else 
                  {
                  
                  		signal(SIGINT, SIG_IGN);
                  		signal(SIGTSTP, SIG_IGN);
                  		childpid=pid;
                        int status;
                        
                        if ((splitter[length-1]!=NULL && !strcmp(splitter[length-1], "&"))) //|| (splitter[3]!=NULL && !strcmp(splitter[3], "&")) || (splitter[2]!=NULL && !strcmp(splitter[2], "&")) || (splitter[4]!=NULL && !strcmp(splitter[4], "&")) || (splitter[5]!=NULL && !strcmp(splitter[5], "&")))  
                        {
                      		
                      		//printf("This is parent and printing child id : %d", childpid);
                        }
                     
                     
                      else
                      {
                        waitpid(pid, &status, 0);
                      }  
                         
                  } 

          


           
      }       
                                     
                     
     
    
}
//