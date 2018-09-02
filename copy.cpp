#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#include<string.h>
#include <fcntl.h>
#include <string>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include<bits/stdc++.h>
#include "alldef.h"
using namespace std;

// int main(int ac, char *av[])
// {
//   string a=(string)av[1];
//   string b=(string)av[ac-1];
//   struct stat s;
// if( stat(a.c_str(),&s) == 0 )
// {
//     if( s.st_mode & S_IFDIR )
//     {
//         //cout<<"@@@@";
//         copyDir(a,b);
//     }
//     else if( s.st_mode & S_IFREG )
//     {
        
//            for(int i=1;i<ac-1;i++)
//            {
//            	copyFile((string)av[i],b);
//            }
       
//     }
//   }
//   return 0;
// }
int copyFile(string a,string b)
{
umask(0);
 int fdSrc,fdDest;
 struct stat s;string na=a;
  size_t found=a.find("/");
  //na=a;
  if (found!=std::string::npos)
  {
  	         size_t found = a.find_last_of("/\\");
             na=a.substr(found+1,a.length()-1);
  }
  else
  {
    na=a;
  }
 b=b+"/"+na;
 //cout<<"@@"<<b<<"na->"<<na<<endl;
if( stat(a.c_str(),&s) == 0 ){
if ( (fdDest=open(b.c_str(),O_CREAT|O_TRUNC|O_WRONLY,(s.st_mode &S_IRWXU)|(s.st_mode &S_IRWXG)|(s.st_mode &S_IRWXO))) <0 )
         {
            printf("BAD OPEN @@%s\n",b.c_str());
            return 1;
         }
         else
         {
         	cout<<b<<" opened";
         }
if ( (fdSrc=open(a.c_str(),O_RDONLY))<0 )
         {
            printf("BAD OPEN %s\n",a.c_str());
            return 1;
        }
        else
        {
            cout<<a<<" opened";
        }
        char c;
 while (read(fdSrc,&c,1)==1)
         {
         	  //cout<<c;
            write(fdDest,&c,1);
         }
         close(fdSrc);
         close(fdDest);  
  return 0;                      
}
}
int copyDir(string source, string destination)
{
    
    struct dirent *de;  
    //cout<<source<<"----"<<destination<<endl;
    
    DIR *dr = opendir(source.c_str());
    if (dr == NULL)  
    {
        printf("Could not open current directory" );
        return 0;
    }
   unsigned long i=0;
   struct dirent **lis;
   int co = scandir(source.c_str(), &lis, NULL, alphasort);
   
     if( co < 0 ){
         perror("Couldn't open the directory");
         exit(1);
     }
    // cout<<co<<"@@@";
     struct stat st;
    for(int i=0; i<co;i++)
            {
    struct stat s;
if( stat(lis[i]->d_name,&s) == 0 && lis[i]->d_name!="." && lis[i]->d_name!="..")
{
    if( s.st_mode & S_IFDIR )
    {
//         char cwd[10000];string curr;
// if (getcwd(cwd,sizeof(cwd)) != NULL) {
//       curr=cwd;
//    } else {
//        perror("getcwd() error");
//        return 1;
//    }
//         //destination=destination+string(lis[i]->d_name);
//         string c;
//                        int fd;
//                       if(destination[0]=='~')
//                        {
//                            size_t found = destination.find("~");
//                            string kk=destination.substr(found+1);
//                            c=curr+"/"+kk;
//                        }
//                        else
//                        {
//                         c=curr+"/"+destination;
//                        }
//                       int g= mkdir(c.c_str(),S_IRUSR|S_IWUSR|S_IXUSR);
//         copyDir(string(lis[i]->d_name),destination);
    }
    if( s.st_mode & S_IFREG )
    {
        
           
           	copyFile(string(lis[i]->d_name),destination);
           
       
    }
 } }
     closedir(dr);  

    }
      
 