#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <bits/stdc++.h>
using namespace std;
//void listAllFiles(string dirName) ;
int fdDest;
int main(int ac, char *av[])
{
	char cwd[10000];string p;string c;
if (getcwd(cwd,sizeof(cwd)) != NULL) {
      p=cwd;
   } else {
       perror("getcwd() error");
       return 1;
   }
   if(string(av[2])==".")   {
   	c=p+"/"+(string)av[1];
   }
  else{ c=(string)av[2]+"/"+(string)av[1];}
if ( (fdDest=open(c.c_str(),O_CREAT|O_TRUNC|O_WRONLY,0664)) <0 )
         {
            printf("BAD OPEN @@%s\n",av[2]);
            
         }	
close(fdDest);
return 0;
}

     

    