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
// void search(string p,string sea);
// int fdDest;
// void clearScreen()
// {
//   const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
//   write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
// }
// int main(int ac, char *av[])
// {
//  char cwd[10000];
// if (getcwd(cwd,sizeof(cwd)) != NULL) {
//       p=cwd;
//    } else {
//        perror("getcwd() error");
//        return 1;
//    } 
// clearScreen();
// search(p,string(av[1]));
// return 0;
// }
void se(string pp,string sea) 
{ 
  DIR *dirp = opendir(pp.c_str()); 
  DIR *dirp2 = opendir(pp.c_str()); 
  if ( dirp ) 
  { 
    struct dirent *dp = NULL; 
    while ( (dp = readdir(dirp)) != NULL ) 
    { 
        std::string file( dp->d_name ); 

        if ( file == "." || file == ".." )    // skip these 
          continue; 

        if ( dp->d_type & DT_DIR ) 
        { 
          
        } 
        else 
        { 
          string c;
          // size_t found = file.find_last_of(".");
          // c=file.substr(0,found);
          //cout<<file<<" "<<sea<<endl;
        	 if(file==sea)
           {
            c=pp+"/"+file;
            cout<<file<<"\t"<<c<<endl;
             fflush(stdout);

           }
        	 
        } 
    }
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
          
         string filePath =pp+"/"+ddir->d_name;
         
         se(filePath,sea); 
         
        } 
       
    } 
closedir( dirp2); 
}
}