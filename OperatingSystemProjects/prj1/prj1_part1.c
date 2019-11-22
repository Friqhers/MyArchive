//MEHMET FURKAN GÜLMEZ


#include <stdlib.h>
#include <stdio.h>
#include <sys/utsname.h>//for uname func
#include <string.h>

void deleteequalsign(char ***name)
{
 int l=strlen(**name);
 char *temp=malloc(l);
 temp=**name;
 temp[l-1]=NULL;
 name=*temp;
}

int main(int argc,char **argv,char **env)
{
  char **argptr,**envptr;
  char name,hostname[64];
  struct utsname info;
  printf("running <%s> with %d parameter\n",*argv,argc-1);
  if(argc > 1)
  {
    for(argptr=argv+1;*argptr !=NULL;argptr++)
     {
       printf("searching %s in the Environment Vector \n",*argptr);
       deleteequalsign(&argptr);
       printf("%s\n",getenv(*argptr));
     }
    
    if(gethostname(&hostname,64)==0){
      printf("Host is %s\n",hostname);
    }
    else{
      printf("Host name cannot be found\n");
    }

    if(uname(&info)>=0){
      printf("Operating System: %s\n",info.sysname);
      printf("Release: %s\n",info.release);
      printf("Machine: %s\n",info.machine);
    }
  }

  return 0;
}
