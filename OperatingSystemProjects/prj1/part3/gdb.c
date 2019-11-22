//Mehmet Furkan GÃ¼lmez


//sudo ./gdb <username> >> gdb.txt

#include <stdio.h>
#include <grp.h>

int main(int argc,char **argv){
 int i; 
 char **argptr;
 struct group *g;

 if(argc > 1){
  argptr=argv+1;
  printf("User: %s\n",*argptr);
  setgrent();
  while((g=getgrent())!=NULL){
   for(i=0;g->gr_mem[i]!=NULL;i++){
      if(strcmp(g->gr_mem[i],*argptr)==0){
         printf("Group Name: %s\nGroup ID: %d\n\n",g->gr_name,g->gr_gid);        
       }
    }
   }
  } 
  endgrent();
  return 0;
}