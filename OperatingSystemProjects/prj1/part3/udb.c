//Mehmet Furkan Gülmez


//sudo ./udb > udb.txt


#include <pwd.h>
#include <stdio.h>

int main(){
 struct passwd *p;
 
 p=getpwent();

 while(p!=NULL){
  printf("%s:",(*p).pw_name);
  printf("%d:",(*p).pw_uid);
  printf("%d:",(*p).pw_gid);
  printf("%s\n",(*p).pw_dir);
  p=getpwent();
 }
 return 0;
}