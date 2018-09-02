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
stack<string> back;
stack<string> fo;
void pos();
map<string,string> m;
//int com=0;
void gotoxy(int x,int y);
#define clear() printf("\033[H\033[J")
static struct termios initial_settings, new_settings;
//void listAllFiles(string dirName,int fdDest) ;
struct dirent **lis;
static int peek_character = -1;
char dn[100][100];
struct winsize w={0,0,0,0};
void init_keyboard();
void close_keyboard();
int kbhit();
int readch();
int coun=0;
int inde=0;
int y;
int co=0;
string p;

string getString(char x)
{
    string s(1, x);
    return s;   
}
void  pos()
{
    int fp = 0;
    fp = open("/dev/pts/0", O_RDONLY);
    if( ioctl(fp, TIOCGWINSZ, &w) == -1 ) { }
     //printf("x: %d y: %d\n", ws.ws_col, ws.ws_row);
    close(fp);
 //return ws;
    
}
int findLastIndex(string str, char x)
{
    int index = -1;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == x)
            index = i;
    return index;
}
void clearScreen()
{
  //const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  //   const char *CLEAR_SCREEN_ANSI = "\033[H\033[J";
  // write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
    printf("\033[H\033[J");
}
void goback(int x,int y)
{
printf("\033[%dA",x);
printf("\033[%dD",y);
}
void gotoxy(int x,int y)
{

int i;
for(i=0;i<x;i++)
printf("\n");
for(i=0;i<y;i++)
printf("\t");

}
int lsfile(string c,int ind)
{    //clear();
    coun=ind;
    struct dirent *de;  
    DIR *dr = opendir(c.c_str());
    if (dr == NULL)  
    {
        printf("Could not open current directory" );
        return 0;
    }
   unsigned long i=0;
   
co = scandir(c.c_str(), &lis, NULL, alphasort);
   
     if( co < 0 ){
         perror("Couldn't open the directory");
         exit(1);
     }
     //coun=co;
     struct stat fileStat;
    for( int i=inde; i<ind+15;i++){
    //printf("%s %d\n",lis[i]->d_name,i);
    if(i<co) {   
    string k;
    k=c+'/';
    coun=coun+1;
    k=k+(string)lis[i]->d_name;

    if(stat(k.c_str(),&fileStat) < 0)    
        return 1;
    long int si=fileStat.st_size;
    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group  *gr = getgrgid(fileStat.st_gid);
    string s1=((S_ISDIR(fileStat.st_mode)) ? ("d") : ("-"));
    string s2=((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    s1=s1+s2;
     s2=( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    s1=s1+s2;
     s2=( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    s1=s1+s2;
    s2=( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    s1=s1+s2;
     s2=( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    s1=s1+s2;
     s2=( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    s1=s1+s2;
     s2=( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    s1=s1+s2;
   s2=((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    s1=s1+s2;
     s2=( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    s1=s1+s2;
    s2=( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    s1=s1+s2;
    struct tm *mytm = localtime(&fileStat.st_mtime);
    char bf[100];
    strftime(bf, 18, "%I:%M:%S-%m/%d/%y", mytm);
    s1=s1+" "+string(pw->pw_name)+" "+string(gr->gr_name)+" "+to_string(si)+" "+(string)bf+" "+string(lis[i]->d_name);
    int l=s1.length();
    pos();
    int kk=w.ws_col;
    kk=kk-1;
    if(l>kk)
    {
        s1=s1.substr(0,kk);
    }
    cout<<s1<<endl;
     fflush(stdout);
     }}
    coun=coun-1;
    closedir(dr);    
    return 0;
}
void init_keyboard()
{
tcgetattr(0,&initial_settings);
new_settings = initial_settings;
new_settings.c_lflag &= ~ICANON;
new_settings.c_lflag &= ~ECHO;
new_settings.c_lflag &= ~ISIG;
new_settings.c_cc[VMIN] = 0;
new_settings.c_cc[VTIME] = 0;
tcsetattr(0, TCSANOW, &new_settings);
}
void close_keyboard()
{
tcsetattr(0, TCSANOW, &initial_settings);
}
int main()
{
int ch = 0,i=0;
string home;
init_keyboard();
clearScreen();
//string s=getString('.');
char cwd[10000];
if (getcwd(cwd,sizeof(cwd)) != NULL) {
      p=cwd;
      home=cwd;

      //cout<<cwd<<" "<<k;
   } else {
       perror("getcwd() error");
       return 1;
   }
lsfile(p,0);
 y=coun;
 printf("\033[%d;1H\n",y);
 fflush(stdout);

 //ygetcwd(cwd, sizeof(cwd);
while(ch != 'q') {
//printf("\n");
//sleep(1);
if(kbhit()) {
ch = readch();
//printf("%d",ch);
if(ch==27)
{
    ch=readch();
    ch=readch();
if(ch==65)
{
            printf("\033[%dA",1);
            fflush(stdout);
            if(y==inde&&inde!=0)
            {
            clearScreen();  
            inde=inde-1;  
            lsfile(p,inde);
            y=inde;
            printf("\033[%d;1H\n",0);
            fflush(stdout);
            }
            
            else if(y!=0)
            {
                y=y-1;
            }
        
}
else if(ch==66)
{           
            //pos();
            printf("\033[%dB",1);
            fflush(stdout);
            if(y<co||y-inde+1<=15)
            {
            if(y==coun&&y-inde+1==15)
            {
            clearScreen();    
            inde=inde+1;
            lsfile(p,inde);
            y=coun;
            printf("\033[14;1H\n");
            }
            else if(y==co-1)
            {
               printf("\033[%d;1H\n",y-inde);
               fflush(stdout);
            }
            else{
           y=y+1;}
       }
           // else
           // {
           //   printf("\033[15;1H\n",y);
           // }
            // pos();
            // int kk=w.ws_row;
            // kk=kk-1;
}
else if(ch==68)
      {
        if(!back.empty()) 
             {
            clearScreen();
            fo.push(p);
            p=back.top();
            inde=0;
            lsfile(p,inde);
             y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
             back.pop();
            }
       
    }
    else if(ch==67)
      {
        if(!fo.empty()) 
             {
            clearScreen();
            //forward.push(p);
            p=fo.top();
           inde=0;
            lsfile(p,inde);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            fo.pop();
            }
       
    }
      }

else if(ch==0x0A)
        {
            string s=lis[y]->d_name;
            inde=0;
            //string k="27"+".";
             if(s.compare("..")==0){
             clearScreen();
             back.push(p);
             size_t found = p.find_last_of("/\\");
             p=p.substr(0,found);
             inde=0;
             lsfile(p,inde);
             y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            }
            else if(s==".")
            {
            
             clearScreen();
             back.push(p);
             inde=0;
             // size_t found = p.find_last_of("/\\");
             // p=p.substr(0,found);
             lsfile(p,inde);
             y=coun;
             printf("\033[%d;1H\n",y);
             //cout<<"@@@"<<p<<" "<<y<<" ";
             fflush(stdout);
            }
            else
            {

            
            clearScreen();
            
            //p=p+'/';
            //p=p+lis[y]->d_name;
            struct stat s; 
            //k=string(lis[i]->d_name);
            string sd;
            sd=p+'/'+string(lis[y]->d_name);
         
          if( stat(sd.c_str(),&s) == 0)
          {
              
              if( s.st_mode & S_IFDIR )
              {
                        back.push(p);          
                        inde=0;
                        p=p+'/';
                        p=p+lis[y]->d_name;
                        lsfile(p,inde);
                        y=coun;
                        printf("\033[%d;1H\n",y);
                        fflush(stdout);
              
              }
              if( s.st_mode & S_IFREG )
              {         
                        //cout<<sd;
                        pid_t pid=fork();
                        if(pid==0){
                        execl("/usr/bin/xdg-open","xdg-open",lis[y]->d_name,NULL);
                        exit(0);}
                        else{
                        lsfile(p,inde);
                        y=coun;
                        printf("\033[%d;1H\n",y);
                        fflush(stdout);}
                 
              }
              
            
            
            }
            
        }}
else if(ch=='h'||ch=='H')
{
            clearScreen();
            p=home;
             inde=0;
            lsfile(p,inde);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
}
else if(ch==8||ch==127)
{
             string s=lis[y]->d_name;
             if(p.compare(home)!=0)
             {
             size_t found = p.find_last_of("/\\");
             p=p.substr(0,found);
             clearScreen();
              inde=0;
            lsfile(p,inde);
             y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
        }
} 
else if(ch==58)
{
static struct termios initial2,new2;
tcgetattr(0,&initial2);
tcsetattr(0, TCSANOW, &initial_settings);   
pos();
int kk=w.ws_row;
kk=kk-1;
printf("\033[%d;1H\n",kk);
string f;
while(true)
{
getline(cin,f);
if(f[0]==27)
{
            tcsetattr(0, TCSANOW, &initial2);
            clearScreen();
            inde=0;
            lsfile(p,inde);
            y=coun;
            printf("\033[%d;1H\n",y);
            fflush(stdout);
            break;
}
else
{       
    
        //printf("\033[%dA",2);
         clearScreen();
        lsfile(p,inde);
        y=coun;
        
        printf("\033[%d;1H\n",kk);
        fflush(stdout);
        vector<string> vv; string word = "";
        int l=f.length();int nowo=0;
        //cout<<"string is ->"<<f;
        fflush(stdout);
        for (int i = 0; i<l; i++) {
        if (f[i]!=' '&& i<l-1)
            {word = word + f[i];}
        else if(i==l-1)
        {
         word = word + f[i];  
         nowo=nowo+1; 
         vv.push_back(word);
        }
        else {vv.push_back(word); 
            nowo=nowo+1; word = "";}
           
           }
        fflush(stdout);
        if(vv[0]=="snapshot")
         {
                int fdDest;string g;
                if(vv[1]!=".")
                {
                string e=p+"/"+vv[2];

                if((fdDest=open(e.c_str(),O_CREAT|O_TRUNC|O_WRONLY,0664)) <0 )
                         {
                            //cout<<"BAD OPEN @@%s\n"<<vv[2];
                            
                         } 
               g=p+"/"+vv[1];
                }
                else
                {
                    string e=p+"/"+vv[2];

                if((fdDest=open(e.c_str(),O_CREAT|O_TRUNC|O_WRONLY,0664)) <0 )
                         {
                            //cout<<"BAD OPEN @@%s\n"<<vv[2];
                            
                         } 
              g=p;
                }         
                listAllFiles(g,fdDest);
                close(fdDest);

         }
         else if(vv[0]=="search")
         {  
            string st=vv[1];
            clearScreen();
            tcsetattr(0, TCSANOW, &initial2);
            se(p,st);
             fflush(stdout);
            read(0,&ch,1);
             //fflush(stdout);
            if(ch==8||ch==127){
             clearScreen();
              inde=0;
              lsfile(p,inde);
              y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
         }
             //cout<<"cool12";
            break;
         }
         else if(vv[0]=="copy")
         {
             //cout<<nowo;
            //copyFile((string)vv[1],vv[2]);
						//  struct stat s;
						// if( stat(vv[1].c_str(),&s) == 0 )
						//   {
						//     if(s.st_mode & S_IFDIR )
						//     {
						//         copyDir(vv[1],vv[2]);
						//     }
						//     else if( s.st_mode & S_IFREG )
						//     {
						        
						//            for(int i=1;i<=nowo-2;i++)
						//            {
      //                               cout<<vv[i]<<vv[nowo-1]<<endl;
						//            	copyFile((string)vv[i],vv[nowo-1]);
						//            }
						       
						//     }
      //                     }

            
                        struct stat s;string c;
                        if( stat(vv[1].c_str(),&s) == 0 )
                        {
                            if(s.st_mode & S_IFDIR )
                            {
                                 if(vv[2][0]=='~'&&vv[2][1]=='/')
                                   {
                                       //size_t found = vv[2].find("~");
                                       string kk=vv[2].substr(2);
                                       c=home+"/"+kk;

                                   }
                                 else
                                   {
                                    c=home+"/"+vv[2];
                                   }
                                string g=home+"/"+vv[1];
                                string kkk;
                                size_t found=vv[1].find("/");
                                if (found!=std::string::npos)
                                {
                                           size_t found = vv[1].find_last_of("/\\");
                                           kkk=vv[1].substr(found+1,vv[1].length()-1);
                                }
                                else
                                {
                                 kkk=vv[1];
                                }
                                kkk=c+"/"+kkk;
                                int gd= mkdir(kkk.c_str(),S_IRUSR|S_IWUSR|S_IXUSR);
                                //destination=kkk;
                                copyDir(g,kkk);
                               // del(vv[1]);
                          
                               // copyDir(g,c);
                            }
                            else if( s.st_mode & S_IFREG )
                            {
                                if(vv[nowo-1][0]=='~'&&vv[nowo-1][1]=='/')
                                   {
                                       size_t found = vv[nowo-1].find("~");
                                       string kk=vv[nowo-1].substr(found+1);
                                       c=home+"/"+kk;
                                   }
                           else
                           {
                            c=home+"/"+vv[nowo-1];
                           }
                           
                                   for(int i=1;i<nowo-1;i++)
                                   {string g=home+"/"+vv[i];
                                    copyFile(g,c);
                                   }
                               
                            }
         }
         clearScreen();   
             inde=0;
            lsfile(home,inde); 
            //lsfile(,0);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            printf("\033[%d;1H\n",kk);
     }
          else if(vv[0]=="move")
         {
            
            struct stat s;
                        if( stat(vv[1].c_str(),&s) == 0 )
                        {
                            if(s.st_mode & S_IFDIR )
                            {   
                                // string kkk;
                                // size_t found=vv[1].find("/");
                                // if (found!=std::string::npos)
                                // {
                                //            size_t found = vv[1].find_last_of("/\\");
                                //            kkk=vv[1].substr(found+1,vv[1].length()-1);
                                // }
                                // else
                                // {
                                //  kkk=vv[1];
                                // }
                                // kkk=vv[2]+"/"+kkk;
                                // int gd= mkdir(kkk.c_str(),S_IRUSR|S_IWUSR|S_IXUSR);
                                // //destination=kkk;
                                // copyDir(vv[1],kkk);
                                // del(vv[1]);
                                string c;
                                if(vv[2][0]=='~'&&vv[2][1]=='/')
                                   {
                                       //size_t found = vv[2].find("~");
                                       string kk=vv[2].substr(1);
                                       c=home+"/"+kk;

                                   }
                                 else
                                   {
                                    c=home+"/"+vv[2];
                                   }
                                string g=home+"/"+vv[1];
                                string kkk;
                                size_t found=vv[1].find("/");
                                if (found!=std::string::npos)
                                {
                                           size_t found = vv[1].find_last_of("/\\");
                                           kkk=vv[1].substr(found+1,vv[1].length()-1);
                                }
                                else
                                {
                                 kkk=vv[1];
                                }
                                kkk=c+"/"+kkk;
                                int gd= mkdir(kkk.c_str(),S_IRUSR|S_IWUSR|S_IXUSR);
                                //destination=kkk;
                                copyDir(g,kkk);
                                del(vv[1]);
                            }
                            else if( s.st_mode & S_IFREG )
                            {
                                
                                   for(int i=1;i<nowo-1;i++)
                                   {
                                    copyFile((string)vv[i],vv[nowo-1]);
                                    del(vv[i]);
                                   }
                               
                            }
               clearScreen();   
             inde=0;
            lsfile(home,inde); 
            //lsfile(,0);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            printf("\033[%d;1H\n",kk);             
         }
         clearScreen();   
             inde=0;
            lsfile(home,inde); 
            //lsfile(,0);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            printf("\033[%d;1H\n",kk);
         }
         else if(vv[0]=="rename")
         {
         	int result= rename(vv[1].c_str(),vv[2].c_str());
         	clearScreen();   
             inde=0;
            lsfile(home,inde); 
            //lsfile(,0);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            printf("\033[%d;1H\n",kk);
         }
         else if(vv[0]=="create_file")
         {
            string c;
            int fdDest;
            if(string(vv[2])==".")   {
                        c=p+"/"+(string)vv[1];
                       }
                       else if(vv[2][0]=='~')
                       {
                          size_t found = vv[2].find("~");
                           string kk=vv[2].substr(found+1);
                           c=p+"/"+kk+"/"+vv[1];
                       }
                       else
                       {
                        c=p+"/"+vv[2]+"/"+vv[1];
                       }

                                           // string c=(string)vv[2]+(string)vv[1];
            if ( (fdDest=open(c.c_str(),O_CREAT|O_TRUNC|O_WRONLY,0664)) <0 )
                     {
                        printf("BAD OPEN @@%s\n",vv[2].c_str());
                        
                     }  
            close(fdDest);
            clearScreen();   
             inde=0;
            lsfile(home,inde); 
            //lsfile(,0);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            printf("\033[%d;1H\n",kk);
         }
         else if(vv[0]=="create_dir")
         {  
                       string c;
                       int fdDest;
                       if(string(vv[2])==".")   {
                        c=p+"/"+(string)vv[1];
                       }
                       else if(vv[2][0]=='~')
                       {
                          size_t found = vv[2].find("~");
                           string kk=vv[2].substr(found+1);
                           c=p+"/"+kk+"/"+vv[1];
                       }
                       else
                       {
                        c=p+"/"+vv[2]+"/"+vv[1];
                       }
                      int g= mkdir(c.c_str(),S_IRUSR|S_IWUSR|S_IXUSR);
                      clearScreen();   
             inde=0;
            lsfile(home,inde); 
            //lsfile(,0);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            printf("\033[%d;1H\n",kk);

         }
         else if(vv[0]=="delete_file")
         {
            size_t found = vv[1].find("trash");
                  if (found!=std::string::npos)
                                {
                                           del(vv[1]);
                                           clearScreen();
              inde=0;
              lsfile(p,inde);
              y=coun;
              //cout<<kkk<<" "<<cc<<" "<<m[cc];
              printf("\033[%d;1H\n",kk);
            fflush(stdout);
               continue;
                                }
     string c,cc,path;
     if(vv[1][0]=='~'&&vv[1][1]=='/')
      {
                                     
       string kk=vv[1].substr(1);
        c=home+"/"+kk;
        // cc=kk;
        // path=home;
         }
         else
          {
           c=home+"/"+vv[1];
           // cc=v[1];
           }  
                                            found = c.find_last_of("/\\");
                                           cc=c.substr(found+1,vv[1].length());
                                           path=c.substr(0,found);
                                           m[cc]=path;
              string jj=home+"/trash";
              copyFile(c,jj);
              del(c);
              clearScreen();
              inde=0;
              lsfile(p,inde);
              y=coun;
              //cout<<cc<<"33"<<m[cc];
              printf("\033[%d;1H\n",kk);
            fflush(stdout);
         }
         else if(vv[0]=="delete_dir")
         {
               size_t found = vv[1].find("trash");
                  if (found!=std::string::npos)
                                {
                                           del(vv[1]);
                                           clearScreen();
              inde=0;
              lsfile(p,inde);
              y=coun;
              //cout<<kkk<<" "<<cc<<" "<<m[cc];
              printf("\033[%d;1H\n",kk);
            fflush(stdout);
               continue;
                                }


             string c,cc,path;
     if(vv[1][0]=='~'&&vv[1][1]=='/')
      {
                                     
       string kk=vv[1].substr(1);
        c=home+"/"+kk;

         }
         else
          {
           c=home+"/"+vv[1];
           }  
           string kkk;
                                found=vv[1].find("/");
                                if (found!=std::string::npos)
                                {
                                           found = vv[1].find_last_of("/\\");
                                           kkk=vv[1].substr(found+1,vv[1].length());
                                }
                                else
                                {
                                 kkk=vv[1];
                                }
                                           found = c.find_last_of("/\\");
                                           cc=c.substr(found+1,vv[1].length());
                                           path=c.substr(0,found);
                                           m[cc]=path;
                                string jj=home+"/trash/"+kkk;
                                int g= mkdir(jj.c_str(),S_IRUSR|S_IWUSR|S_IXUSR);
                                cout<<jj<<" "<<c;
              copyDir(c,jj);
              del(c);
            clearScreen();
              inde=0;
              lsfile(p,inde);
              y=coun;
              //cout<<kkk<<" "<<cc<<" "<<m[cc];
              printf("\033[%d;1H\n",kk);
            fflush(stdout);
         }
         else if(vv[0]=="restore")
         {    
             auto it = m.find(vv[1]);
             string jj=home+"/trash/"+vv[1];
              if (it != m.end())
               {
                      struct stat s;string c;
                        if( stat(jj.c_str(),&s) == 0 )
                        {
                            if(s.st_mode & S_IFDIR )
                            {
                                   string kk=m[vv[1]]+"/"+vv[1];
                               int g= mkdir(kk.c_str(),S_IRUSR|S_IWUSR|S_IXUSR);
                               copyFile(jj,kk);
                               del(jj);
                               m.erase (it);
                            }
                            else if( s.st_mode & S_IFREG )
                            { 
                               
                               copyFile(jj,m[vv[1]]);
                                   del(jj);
                                   m.erase (it);
                            }
                         }
               
               }
               clearScreen();
               inde=0;
               lsfile(p,inde);
               y=coun;
               printf("\033[%d;1H\n",kk);
               fflush(stdout);
         }
         

         else if(vv[0]=="goto")
         {
             if(vv[1]=="/")
             {
            clearScreen();    
            inde=0;
            lsfile(p,inde);
            p=home;
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
             }
             else if(vv[1]==".")
             {
            clearScreen();    
            inde=0;
            lsfile(p,inde);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
             }
             else
             {
            p=p+"/"+vv[1];
            clearScreen();
           inde=0;
            lsfile(p,inde);
            y=coun;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
              }
               tcsetattr(0, TCSANOW, &initial2);
               break;
         }
        fflush(stdout);
       }
}
}

}
}
close_keyboard();
exit(0);
}
int kbhit()
{
char ch;
int nread;
if(peek_character != -1)
return 1;
new_settings.c_cc[VMIN]=0;
tcsetattr(0, TCSANOW, &new_settings);
nread = read(0,&ch,1);
new_settings.c_cc[VMIN]=1;
tcsetattr(0, TCSANOW, &new_settings);
if(nread == 1) {
peek_character = ch;
return 1;
}
return 0;
}
int readch()
{
char ch;
if(peek_character != -1) 
{
ch = peek_character;
peek_character = -1;
return ch;
}
read(0,&ch,1);
return ch;
}