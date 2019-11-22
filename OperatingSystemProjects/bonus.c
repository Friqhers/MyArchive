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
  int fp1,fp2,len;
  long int offset;
  char accountName[33];
  char comment[255];
  IdxRec input;
  char str[40],*ptr;
  char **result=(char**)malloc(30*sizeof(char *));

  if((fp2=open("pwd.idx",O_RDONLY,0))< 0){
 	 printf("pwd.idx Error opening file\n");
	 exit(1);
  }

  printf("Enter account name:");
  fgets(accountName,32,stdin);
  if(strlen(accountName) == 0 ){
	printf("Account name can't be empty !\n");
	exit(1);
  }
  printf("Entered account: %s\n",accountName);

  //reading pwd.idx 
  while((read(fp2,&input,sizeof(IdxRec)))> 0){
  	if(strcmp(strtok(accountName,"\n"),input.accountname)==0){
 		offset=input.pwdoffset;
 		len=input.recordlength;
 	}
  }

  if((fp1=open("./passwd.srt",O_RDWR,2)) < 0){
 	 printf("Can't open passwd.srt file\n");
   	 exit(1);
  }

  if(lseek(fp1,offset,SEEK_SET)< 0 ){
	 printf("Offset position error\n");
 	 exit(1);
  }

  while((fp1=pread(fp1,str,len,offset))< 0 ){
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

  int sizeofComment;
  //if all the fields are not empty
  if(i==7){
	 char *pos2;
         if((pos2=strchr(result[6],'\n'))!=NULL){
		*pos2='\0';
	 }
     	 printf("Home Directory: %s Login_Shell: %s Comment:%s\n",result[5],result[6],result[4]);
	 sizeofComment=strlen(result[4]);
	 printf("Size of comment field: %d\n",sizeofComment);
	 printf("Record length: %d\n",len);

         printf("Enter a comment for %s account: ",accountName);
         fgets(comment,255,stdin);
	 char *pos;
         if((pos=strchr(comment,'\n'))!=NULL){
		*pos='\0';
	 }
         printf("Entered Comment: %s\n",comment);
         printf("Size of entered comment: %d\n",strlen(comment));
         
         //if size of entered comment and the size of original comment is same
         if(strlen(comment)== sizeofComment){

   		if((fp1=open("./passwd.srt",O_RDWR,2))<0){
 			printf("\nError\n");
		}

                pwrite(fp1,comment,strlen(comment),offset+len-strlen(result[6])-strlen(result[5])-sizeofComment-3);
                
   		//after update operation

   		pread(fp1,str,len,offset);
   		printf("After Updated: %s\n",str);
	}
	else{
		printf("No changes made\n");
	}
  }
  else if(i==6){
	 //No comment created
	 printf("Home Directory: %s Login_Shell: %s Comment: No comment\n",result[4],result[5]);
	 sizeofComment=0;
	 printf("Size of comment field: %d\n",sizeofComment);
	 printf("Record length: %d\n",len);
	 printf("No changes made\n");
  }
  else{
	 printf("invalid user i=%d\n",i);
	 close(fp1);
         close(fp2);
         exit(1);
  }

  close(fp1);
  close(fp2);
  return 0;
}