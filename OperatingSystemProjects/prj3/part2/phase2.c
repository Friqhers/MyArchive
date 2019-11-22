// Mehmet Furkan Gülmez


#include  <stdio.h>
#define READ  0
#define WRITE 1

int isThereNumeral(char *buf,int len);
int isEmptyRecord(char *buf,int len);

int main(){

	int fd1[2],fd2[2];
	int pid, pid1;
	int result=0;
	char buffer[40];
	int flag;
	int c,status,i;
	
	if(pipe(fd1)==-1){fprintf(stderr,"pipe1 failed\n"); return 1;}
	if(pipe(fd2)==-1){fprintf(stderr,"pipe2 failed\n"); return 2;}


	if( (pid = fork ()) < 0 ){
		printf("Error!\n");
	}
	if(pid==0){
		//child-1 process 
	
         	close(fd1[READ]);
			
		while(fgets(buffer,40,stdin) != NULL){
			if(isEmptyRecord(buffer,strlen(buffer)) == 1){
				printf("Empty records are not allowed!\n");}
			else{
				write(fd1[WRITE],buffer,strlen(buffer));
			}
		}
					
					
		close(fd1[WRITE]);
		exit(0);		
	}


        if((pid = fork()) < 0){
		printf("Error!\n");
	}


	if(pid == 0){
		 close(fd1[READ]);
		 close(fd1[WRITE]);
		
		 close(fd2[WRITE]);
		 while(read(fd2[READ], buffer, 40) > 0){
				result++;
				printf("---------------\n");			
		    	        printf("line_count : %d\n",result);
		 		printf("---------------\n");
		
		} 
	 	close(fd2[READ]);
		exit(0);
	}
	close(fd1[WRITE]);
	close(fd2[READ]);

	while((c = read(fd1[READ],buffer,40)) > 0){
					


		if(isThereNumeral(&buffer,strlen(buffer))){
		
			write(fd2[WRITE],buffer,40);	

		}


	}
        
        close(fd1[READ]);
	close(fd2[WRITE]);

	i=wait(&status);

	return 0;
	

	
}

int isThereNumeral(char *buf,int len){
	int i;
	int flag=0;

	for(i=0; i<len-1; i++){
		//numerals are between 48 and 57

		if(buf[i] >= 48 && buf[i] <= 57 )//ascii table
		{
				flag=1;		
		}

	}
	
	return flag;
}
int isEmptyRecord(char *buf,int len){
	int i;
	int flag=1;
	for(i=0 ; i< len ; i++){
		//if there is an character that is different from \n , the record is not empty
		if(buf[i] != 10){
			flag=0;
		}
	}

	return flag;
}

