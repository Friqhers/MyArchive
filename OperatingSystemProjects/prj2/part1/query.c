//Mehmet Furkan Gülmez


#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>


typedef struct{
 char accountname[33];
 long int pwdoffset;
 int recordlength;
}IdxRec;

int main(){
int fp1, fp2, len;
 FILE *test;
 char accountName[32];
 IdxRec input;
 long int offset;
 char str[40],*ptr;
 char **result=(char**)malloc(30*sizeof(char *));

 
 if((fp2=open("pwd.idx",O_RDONLY,0))< 0){
 	printf("pwd.idx Error opening file\n");
	exit(1);
 }

 printf("Enter account name:");
 fgets(accountName,32,stdin);
 printf("%s\n",accountName);

 //reading pwd.idx 
 while((read(fp2,&input,sizeof(IdxRec)))> 0){
 	if(strcmp(strtok(accountName,"\n"),input.accountname)==0){
		offset=input.pwdoffset;
		len=input.recordlength;
	}
 }
 
 if((fp1=open("./passwd",O_RDWR,2)) < 0){
 	printf("Can't open passwd file\n");
	exit(1);
 }

 if(lseek(fp1,offset,SEEK_SET)< 0 ){
	printf("Offset position error\n");
 	exit(1);
 }

 while((fp1=read(fp1,str,len))< 0 ){
	printf("Can't read file\n");
        exit(1);
 }

 ptr=strtok(str,":");
 int i =0;
 while(ptr != NULL){
 	result[i]=ptr;
	ptr=strtok(NULL, ":");
	i++;
 }

 if(i==7){
	printf("Home Directory: %s Login_Shell: %s\n",result[5],result[6]);

 }
 else{
	printf("invalid user\n");exit(1);}

 






 return 0;
}