//Mehmet Furkan Gülmez


#include  <stdio.h>
#define READ  0
#define WRITE 1

int isOnlyNumeral(char *buf,int len);
int isEmptyRecord(char *buf,int len);
int isEmptyRecordv2(char **buf,int len);

int main(){

	int fd1[2],fd2[2],pid,i;
	int result=0;
	char buffer[40];
	char *temp;

	if(pipe(fd1)==-1){fprintf(stderr,"pipe1 failed\n");}


	switch(pid=fork())//new process is creating
	{
		case -1://error
			fprintf(stderr,"forking child process failed\n");			
		break;
		case 0://child process 

			close(fd1[WRITE]);
			
			while(read(fd1[READ],buffer,40)){

			}
					
						
			close(fd1[READ]);


		

		break;
		default:// parent process

			//input is getting
			while(fgets(buffer,40,stdin)){	
				write(fd1[WRITE],buffer,40);
		
				if(isOnlyNumeral(&buffer,strlen(buffer))){
					result++;
				}			
				

			}
			
			close(fd1[WRITE]);	
			wait(NULL);
			close(fd1[READ]);
		
			
			printf("---------------\n");			
			printf("line_count : %d\n",result);
			printf("---------------\n");
		
	}


  	return 0;
}

int isOnlyNumeral(char *buf,int len){
	int i;
	int flag=1;
	
	
	for(i=0; i<len-1; i++){
		//numerals are between 48 and 57
		if(buf[i] < 48 || buf[i] > 57 )//ascii table
		{
				flag=0;		
		}

	}
	if(isEmptyRecord(buf,len)==1){flag=0;}
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


