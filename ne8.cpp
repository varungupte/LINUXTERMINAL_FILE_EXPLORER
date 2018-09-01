#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#include<string.h>
#include <string>
#include<bits/stdc++.h>
using namespace std;
stack<string> back;
stack<string> fo;
#define clear() printf("\033[H\033[J")
static struct termios initial_settings, new_settings;
struct dirent **lis;
static int peek_character = -1;
char dn[100][100];
void init_keyboard();
void close_keyboard();
int kbhit();
int readch();
int coun=0;
int y;
string p;
string getString(char x)
{
    string s(1, x);
    return s;   
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
int lsfile(string c)
{    //clear();
    coun=0;

    //get current firectory

    /*char cwd[10000];
   if (getcwd(cwd,sizeof(cwd)) != NULL) {
      p=cwd;
      //cout<<cwd<<" "<<k;
   } else {
       perror("getcwd() error");
       return 1;
   }*/

   //end of current directory

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
     coun=co;
    for( int i=0; i<co;i++){
            printf("%s %d\n",lis[i]->d_name,i);
     }
    
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
lsfile(p);
 y=coun;
 //p=getcwd(cwd, sizeof(cwd);
while(ch != 'q') {
//printf("\n");
//sleep(1);
if(kbhit()) {
ch = readch();
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
            
            printf("\033[%dB",1);
            fflush(stdout);
            y=y+1;
}
else if(ch==68)
      {
        if(!back.empty()) 
             {
            clearScreen();
            fo.push(p);
            p=back.top();
            lsfile(p);
            cout<<p<<endl;
            fflush(stdout);
            y=coun+1;
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
            lsfile(p);
            cout<<p<<endl;
            fflush(stdout);
            y=coun+1;
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
            lsfile(p);
            cout<<p<<endl;
            fflush(stdout);
            y=coun+1;
            }
            else if(s.back()=='.')
            {
           //cout<<p;    
            clearScreen();
             back.push(p);
            lsfile(p);
            cout<<p<<endl;
            fflush(stdout);
            y=coun+1;
            }
            else
            {
            clearScreen();
            back.push(p);
            p=p+'/';
            p=p+lis[y]->d_name;
            lsfile(p);
            cout<<p<<endl;
            fflush(stdout);
            y=coun+1;
            }
            
        }
else if(ch=='h'||ch=='H')
{
            clearScreen();
            p=home;
            lsfile(p);
            cout<<p<<endl;
            fflush(stdout);
            y=coun+1;
}
else if(ch==8||ch==127)
{
             string s=lis[y]->d_name;
             if(p.compare(home)!=0)
             {
             size_t found = p.find_last_of("/\\");
             p=p.substr(0,found);
             clearScreen();
             lsfile(p);
             cout<<p<<endl;
             fflush(stdout);
             y=coun+1;
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