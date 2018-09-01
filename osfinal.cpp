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
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
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
int lsfile(string c,int inde)
{    //clear();
    coun=inde;
    struct dirent *de;  
    DIR *dr = opendir(c.c_str());
    if (dr == NULL)  
    {
        printf("Could not open current directory" );
        return 0;
    }
   unsigned long i=0;
   
   int co = scandir(c.c_str(), &lis, NULL, alphasort);
   
     if( co < 0 ){
         perror("Couldn't open the directory");
         exit(1);
     }
     //coun=co;
     struct stat fileStat;
    for( int i=inde; i<inde+10;i++){
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
    s1=string(lis[i]->d_name)+" "+to_string(si)+" "+s1+" "+string(pw->pw_name)+" "+string(gr->gr_name)+" "+(string)bf;
     
     {  
        //goback(1,10);
        cout<<s1<<endl;
     }
     
     fflush(stdout);
     }}
    
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
 y=coun-1;
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
            y=y-1;
}
else if(ch==66)
{           
            //pos();
            printf("\033[%dB",1);
            fflush(stdout);
            if(y==coun)
            {
            clearScreen();    
            lsfile(p,inde+1);
            fflush(stdout);
            y=coun;
            }
           else{ y=y+1;}

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
            lsfile(p,0);
             y=coun-1;
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
            lsfile(p,0);
            y=coun-1;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            fo.pop();
            }
       
    }
      }

else if(ch==0x0A)
        {
            string s=lis[y]->d_name;
             if(s.compare("..")==0){
            clearScreen();
             back.push(p);
             size_t found = p.find_last_of("/\\");
             p=p.substr(0,found);
            lsfile(p,0);
             y=coun-1;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            }
            else if(s.back()=='.')
            {
           //cout<<p;    
            clearScreen();
             back.push(p);
            lsfile(p,0);
            y=coun-1;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            }
            else
            {
            clearScreen();
            back.push(p);
            p=p+'/';
            p=p+lis[y]->d_name;
            lsfile(p,0);
            y=coun-1;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            }
            
        }
else if(ch=='h'||ch=='H')
{
            clearScreen();
            p=home;
            lsfile(p,0);
            y=coun-1;
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
             lsfile(p,0);
             y=coun-1;
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
            lsfile(p,0);
            y=coun-1;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
            break;
}
else
{       
    
        printf("\033[%dA",1);
        vector<string> vv; string word = "";
        int l=f.length();int nowo;
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
        else {vv.push_back(word); word = "";}
           
           }
        fflush(stdout);
        if(vv[0]=="snapshot")
         {
                int fdDest;
                string e=p+"/"+vv[2];
                if((fdDest=open(e.c_str(),O_CREAT|O_TRUNC|O_WRONLY,0664)) <0 )
                         {
                            cout<<"BAD OPEN @@%s\n"<<vv[2];
                            
                         } 
                string g=p+"/"+vv[1];         
                listAllFiles(g,fdDest);
                close(fdDest);

         }
         else if(vv[0]=="search")
         {
            string st=vv[1];
            clearScreen();
            tcsetattr(0, TCSANOW, &initial2);
            se(p,st);
            ch=readch();
             //fflush(stdout);
            if(ch==8||ch==127){
                cout<<"cool1";
             clearScreen();
             lsfile(p,0);
             y=coun-1;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
         }
             cout<<"cool12";
            break;
         }
         else if(vv[0]=="copy")
         {
						 struct stat s;
						if( stat(vv[1].c_str(),&s) == 0 )
						{
						    if(s.st_mode & S_IFDIR )
						    {
						        copyDir(vv[1],vv[2]);
						    }
						    else if( s.st_mode & S_IFREG )
						    {
						        
						           for(int i=1;i<nowo-2;i++)
						           {
						           	copyFile((string)vv[i],vv[nowo-1]);
						           }
						       
						    }
  }
         }
          else if(vv[0]=="move")
         {

         }
         else if(vv[0]=="rename")
         {
         	int result= rename(vv[1].c_str(),vv[2].c_str());
         	clearScreen();    
            lsfile(home,0);
            y=coun-1;
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

         }
         else if(vv[0]=="delete_file")
         {
            del(vv[1]);
            fflush(stdout);
         }
         else if(vv[0]=="delete_dir")
         {
            del(vv[1]);
            fflush(stdout);
         }
         else if(vv[0]=="goto")
         {
             if(vv[1]=="/")
             {
            clearScreen();    
            lsfile(home,0);
            p=home;
            y=coun-1;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
             }
             else if(vv[1]==".")
             {
            clearScreen();    
            lsfile(p,0);
            y=coun-1;
             printf("\033[%d;1H\n",y);
             fflush(stdout);
             }
             else
             {
            p=p+"/"+vv[1];
            clearScreen();
            lsfile(p,0);
            y=coun-1;
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
//     
//         // if(vv[0]=="snapshot")
//         //  {
//         //         // int fdDest;
//         //         // string e=p+"/"+vv[2];
//         //         // if((fdDest=open(e.c_str(),O_CREAT|O_TRUNC|O_WRONLY,0664)) <0 )
//         //         //          {
//         //         //             cout<<"BAD OPEN @@%s\n"<<vv[2];
                            
//         //         //          } 
//         //         //  string g=p+"/"+vv[1];         
//         //         // listAllFiles(g,fdDest);
//         //         // close(fdDest);

//         //  }
        

      
      
//         fflush(stdout);
//        }
//        else if(ch!=27)
//            {
//            //printf("cool5555");
//             f=f+ch;


//            }
//        else 
//            {
//             //ch=readch();
//             //if(ch==10)
//             //{
//             tcsetattr(0, TCSANOW, &initial2);
//             clearScreen();
//             lsfile(p,0);
//             y=coun+1;
//             cout<<p<<endl;
//             fflush(stdout);
//             break;
//            }
   

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