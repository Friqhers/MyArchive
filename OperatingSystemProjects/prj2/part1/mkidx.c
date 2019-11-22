/* mkidx.c: 
   - creates the sorted index file "pwd.idx" for ./passwd
     the local copy of /etc/passwd
   - returns '0' if successful,'n' otherwise
   - reads from stdin the number of records in "./passwd"
     this input may be provided with the command pipe:
          "cat ./passwd | wc -l | ./mkidx"

  - uses Low-level I/O API to create "pwd.idx"
         Stream I/O API to read "./passwd"
*/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct { // idx file record structure
	char actname [32+1];   // account name string +'\0'
	long int pwdoffset;    // passwd file offset
	int  rel;              // record length in ./passwd
} IdxRec, *pIdxRec;
         
#define PWDRLEN  1023  // max.length of an entry in /etc/passwd"
     
int main()
{	
	char buf[PWDRLEN+1]; int nbusr, i,  j;
	long int pos;		//  byte offset in ./passwd
	FILE *fppw;			//  -->   ./passwd
	pIdxRec IdxTab;		// index table         

	if (scanf("%d", &nbusr) == EOF) { perror("Invalid # user");return 1; }
	if ( nbusr < 1 ) { puts("Invalid user #");return 2; }	

	// allocate Index Table IdxTab [nbsusr]
	if (( IdxTab = malloc ( sizeof(IdxRec) * nbusr)) == NULL) 
		{ puts("buffer allocation error");return 3; }	

	if ( ( fppw= fopen("./passwd", "r") ) == NULL)
		{ perror("./passwd: "); return 4; } 

	pos = 0 ; // when ./passwd is open file position is set to 0 
	i = 0;
	// read nbusr entries from ./passwd and fill IdxTab 
	while (  (i < nbusr) && ( fgets(buf,  PWDRLEN,  fppw) != NULL )  ) { 
		j = 0; 
		// copy account name in IdxTab and insert 0 at the end of the logname 
   		while ( (j < 32)  && (( IdxTab[i].actname[j] = buf[j] ) != ':') )  j++ ; 
		IdxTab[i].actname[j] = 0 ;  // overwrite ':' with '0'
		      
		// save the record offset in "./passwd"
		IdxTab[i].pwdoffset = pos ; 

		// store the record length
		IdxTab[i].rel = strlen(buf) ;
		
		// read the position of the file pointer marking the start of the next entry 
		if ( (pos = ftell (fppw)) == -1) {perror("/etc/passwd pos "); return 4;};
		i++;
	}
	// bubble sort TabIdx entries in ascending order of 'actname'
	IdxRec tmp;
	for (i = 0; i < nbusr -2 ; i++)
		for (j = i+1; j < nbusr-1; j++)
			if (strcmp ((const char *) &IdxTab[i].actname, (const char *) &IdxTab[j].actname) > 0){
				tmp = IdxTab[i];
				IdxTab[i] = IdxTab[j];
				IdxTab[j] = tmp;
			}
	// list IdxTab contents
	for (i = 0; i < nbusr ; i++)	
		printf("acount: %d\toffset:%ld \t<%s>\n", i+1,IdxTab[i].pwdoffset , IdxTab[i].actname ); 
	
	// Create the index file './pwd.idx'
	int fdidx;
   	if ( ( fdidx = open("pwd.idx",
						O_WRONLY | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ) ) == -1) 
   			{perror("pwd.idx: "); return 5;}

    if ( write( fdidx, (const void *) IdxTab, (sizeof(IdxRec) * nbusr) ) == -1 )
			{perror("./idx write error: "); return 6;}

	if ( close(fdidx) < 0) 
   			{perror("pwd.idx: "); return 7;}
	if ( fclose(fppw)!= 0)
   			{perror("./passwd: "); return 8;}
	return 0;
}