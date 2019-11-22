//Mehmet Furkan Gülmez


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main(){
	int pfd[2],i,n,status,p,fd;
	int pid[2];

	
	if(pipe(pfd) < 0){fprintf(stderr,"pipe failed\n"); return 1;}

			
	if( (pid[0] = fork()) < 0 ){
		printf("Fork1 error!\n");
	}

	if(pid[0] == 0)
	{//child-1 process
	
		close(pfd[READ]);
		
		dup2(pfd[WRITE], 1);
		execlp("cat","cat","/etc/passwd",(char *) NULL);
		
		
		printf("execlp failure for cat\n");
		return 10;		
	}
	
	if( (pid[1] = fork()) < 0){
		printf("Fork2 error!\n");
	}

	if(pid[1] == 0){
	//child-2 process
		


		close(pfd[WRITE]);
 	

		dup2(pfd[READ],0);
		
		
		execlp("grep","grep","/var",(char *) NULL);
		/*if(p == -1){
		printf("execlp failure for grep\n");
		return 20;}*/

		
      		//close(fd1[READ]);
		//close(fd1[WRITE]);
		

	}

	//parent process

      	close(pfd[READ]);
	close(pfd[WRITE]);

	i=0;
	while(i<2){
		n = wait(&status);
		i++;
	}
	printf("Parent exiting\n");

	return 0;	

}
