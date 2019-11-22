//Mehmet Furkan Gülmez


#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <sys/types.h>

void  parse(char *p, char **argv)//split function
{
	while (*p != '\0') {      

		while (*p == ' ' || *p == '\t' || *p == '\n')
			*p++ = '\0';    

		*argv++ = p;         

		while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '\n') 
			p++;            
	}
	*argv = '\0';   
            
}


int  main()
{
	char  input[1024];             
	char  *argv[64];
	pid_t  pid;
	int status;

	
	while (1) {                  
		printf("Shell_Command -> ");    
		gets(input);
               
		   
		
		parse(input, argv);	    
			
		 if (strcmp(argv[0], "exit") == 0)  
	               exit(0);     
             
         
		//new process create and execute
		if ((pid = fork()) < 0) {       
			printf("forking child process failed\n");
			exit(1);
		}
		else if (pid == 0) { //child process  
			printf("------------------------------------------------\n"); 
			printf("Process_Id:%d, Parent_Process_Id:%d\n",getpid(),getppid());
			printf("------------------------------------------------\n");
			if (execvp(*argv, argv) < 0) {     
			printf("exec failed\n");
			exit(1);
			}
		}
		else {  //parent process                           
			while (wait(&status) != pid); // wait for completion  	    
               
		} 
		printf("\n");      
	     }
return 0;
}


