//ROLL NUMBER:- 2018201003
//NAME :- VARUN GUPTA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <bits/stdc++.h>
#include "alldef.h"
using namespace std;
// void listAllFiles(string dirName,int x);

// int main(int ac, char *av[])
// {
//   int fdDest;
// if ( (fdDest=open(av[2],O_CREAT|O_TRUNC|O_WRONLY,0664)) <0 )
//          {
//             printf("BAD OPEN @@%s\n",av[2]);
            
//          }	
// listAllFiles(string(av[1]),fdDest);
// close(fdDest);
// return 0;
// }
void listAllFiles(string dirName,int fdDest) 
{ 
  DIR *dirp = opendir( dirName.c_str() ); 
  DIR *dirp2 = opendir( dirName.c_str() ); 
  
  if (dirp) 
  { 
    struct dirent *dp = NULL; 
    while ( (dp = readdir(dirp)) != NULL ) 
    { 
        string file( dp->d_name ); 
        if ( file == "." || file == ".." )    // skip these 
          continue; 
        if ( dp->d_type & DT_DIR ) 
        { 
        } 
        else 
        { 
          string c=file+"\t";
        	size_t l=c.length();
        	write(fdDest,c.c_str(),l);
        } 
    }
            string c="\n";
        	  size_t l=c.length();
        	  write(fdDest,c.c_str(),l);
            closedir( dirp ); 
}
    if (dirp2) 
  { 
  	struct dirent *ddir = NULL; 
    
    while ( (ddir = readdir(dirp2)) != NULL ) 
    { 
        std::string file( ddir->d_name ); 

        if ( file == "." || file == ".." )    // skip these 
          continue; 

        if ( ddir->d_type & DT_DIR ) 
        { 
          
         string filePath = dirName + "/" + file; 
         string c=filePath+"\n";
         size_t l=c.length();
         write(fdDest,c.c_str(),l);
         listAllFiles(filePath,fdDest); 
         c="\n";
         l=c.length();
         write(fdDest,c.c_str(),l);
        } 
       
    } 
closedir( dirp2);
}
}