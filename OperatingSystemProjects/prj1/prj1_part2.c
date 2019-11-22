//Mehmet Furkan Gülmez




//To run this program you should use this concatenated command =>  cat /etc/passwd > ./passwd | wc -l < /etc/passwd > maxrnum.txt ; ./sort


#include <stdio.h>

// actcmp returns 0 if s==t, <0 if s<t, >0 if s>t
int actcmp(char *s, char *t)
{ 

       for( ; *s == *t ; s++, t++)
		if ( *s == ':') return 0; // s = t
	if ( *s == ':') return -1 ;   // s < t
	if ( *t == ':') return +1 ;   // s > t
	return *s - *t ;
}
#define MAXRLEN  1023  // max.record lengt in "/etc/passwd"


int main()
{	
        int MAXRNUM;//maximum record number
	int nbusr, i, j, tmp,y,a,b;
	FILE *fppwd;		//  -->   ./passwd
	FILE *fpsrt;		//  -->   ./passwd.srt 
        FILE *fpmaxrnum;        //  -->   ./maxrnum.txt => for reading the maximum record number from the user.
        char maxrecords[10],temp[MAXRLEN];
        
 
        if( (fpmaxrnum = fopen("./maxrnum.txt","r") ) == NULL )
                { perror("./maxrnum.txt: "); return 1; }

        fgets(maxrecords,10,fpmaxrnum);
        MAXRNUM=atoi(maxrecords); //convert char number to int
        printf("MAXRNUM : %d\n",MAXRNUM);

                 
        int *SortIdx=(int *) malloc((MAXRNUM+1)*sizeof(int)); 

        char *SortTab[MAXRNUM];
        for(y=0;y<MAXRNUM;y++){
          SortTab[y]=(char *)malloc(MAXRLEN*sizeof(char));
        }

	if ( ( fppwd= fopen("./passwd", "r") ) == NULL)
		{ perror("./passwd: "); return 1; } 

	// fgets reads a ./passwd record including '\n'
    //       stores it as a string adding by a '\0'
	i = 0;    
	for ( nbusr= 0; nbusr < MAXRNUM ; nbusr++ ) {
		SortIdx[nbusr] = nbusr;  // set index to records order
		if (fgets(temp, MAXRLEN, fppwd) != NULL )
	        {
                   for(y=0;y<MAXRLEN;y++){
                     if(temp[y]!=NULL && temp[y]!="\0"){
                      SortTab[nbusr][y]=temp[y]; 
                     }
                     else break;
                   }
                    SortTab[nbusr][y]=NULL;
                }
                else break;
	}

      
       
   

       //getting the first letters of all records and writing them to firstletters pointer array
       char *tempchar,templetter;
       char *firstletters=malloc((MAXRNUM+1)*sizeof(char));
       for(i=0;i<MAXRNUM;i++){
         firstletters[i]=SortTab[i][0];
       }

       //selectionsort
       int min_idx;
       for(i=0;i<MAXRNUM-1;i++){
        
         min_idx=i;
         for(j=i+1;j<MAXRNUM;j++){
           if(firstletters[j]<firstletters[min_idx])
             min_idx=j;
 
         }

         tempchar = SortIdx[min_idx];
         SortIdx[min_idx] = SortIdx[i];    
	 SortIdx[i] = tempchar;
         
         templetter=firstletters[min_idx];
         firstletters[min_idx]=firstletters[i];
         firstletters[i]=templetter;
        
       }




	// Create sorted passwd file './passwd.srt'
	if ( ( fpsrt= fopen("./passwd.srt", "w") ) == NULL)
		{ perror("./passwd.srt: "); return 3; }
        


        
	// write account records in ascending order
	for (i=0; i < nbusr+1; i++){
		printf("acct[%d]=%s", i, SortTab[SortIdx[i]]) ;
		if (fputs(SortTab[SortIdx[i]], fpsrt) < 0)
			{ perror("./passwd.srt:  "); return 4; } 
	}
        
	if ( fclose(fpsrt)!= 0)
   			{perror(" fpsrt  "); return 5;}

        	
	return 0;
}