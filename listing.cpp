/*                               
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/

/*ls module file */

#include "listing.h"

vector<string> files;
stack<string> enter;
stack<string> lft;
stack<string> rght;
struct winsize w;
static string temp;
static char abst[PATH_MAX];
static int lines;

void debug()
{
     printf("\033[21;1H" );
     cout<<"enter:"<<enter.top()<<" "<<enter.size();
     resetcursor();
}

void debug1()
{
    printf("\033[22;1H" );
    if(lft.size() != 0)
    {
        cout<<"\nleft:"<<lft.top()<<" "<<lft.size();
    }
    resetcursor();
}

void debug2()
{
     printf("\033[23;1H" );
     if(rght.size() != 0)
    {
        cout<<"\nright:"<<rght.top()<<" "<<rght.size();
    }
    resetcursor();
     
}

//clear and reset terminal
void blank()
{
    printf("\033c" );
}

//reset cursor to top left position
void resetcursor()
{
    printf("\033[1;1H" );
}


//get directory information    
int getdir (char *arr)
{
	blank();
	files.clear();
    int count=0;
    
    DIR *dp;
    struct dirent *dirp;

    /* file stat, username and groupname */
    struct stat fileStat; 
    struct passwd *pw;
    struct group  *gr;
    char str[PATH_MAX];

    //strcpy(path,"/bin");
	//try to open specified directory 
    if((dp  = opendir(arr)) == NULL) 
    {
        cout << "Error(" << errno << ") opening " << arr << endl;
        return errno;
    }

    //pushing all file names into vector
    while ((dirp = readdir(dp)) != NULL) 
    {
       count++;
       files.push_back(string(dirp->d_name));       
    }

    //sort file name in lex order
    sort(files.begin(),files.end());
    
    vector<string>::iterator itr;

    for(itr=files.begin();itr!=files.end();++itr)  

    {   
       strcpy(str,arr);
       strcat(str,"/");
       strcat(str,(*itr).c_str());
       if (!stat(str, &fileStat)) 
        { 
            //convert uid and gid to uname,gname
            pw=getpwuid(fileStat.st_uid);
            gr=getgrgid(fileStat.st_gid);

            //print permissions
            printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-"),printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

            //output file properties
            cout<<"\t"<<(string(pw->pw_name)).substr(0,7)<<"\t"<<(string(gr->gr_name)).substr(0,7)<<"\t"<<(int)fileStat.st_size<<"\t"<<string(ctime(&fileStat.st_mtime)).substr(4,12)<<"\t"<<string(*itr);

        } 

        else
        {
            perror("stat method failed");
        }
      
        printf("\n");
    }

resetcursor();
return count;
}

int dir_enter(int pos)
{
      
    if(enter.size() == 1)
    {
        if(files[pos] == ".")
        {
            return -1;
        }
        else if(files[pos] == "..")
        {
            resetcursor();
            return -2;
        }
        else
        {   
            temp = enter.top();
            lft.push(temp);
            temp+="/";
            temp+=files[pos].c_str();
            enter.push(temp);
            strcpy(abst,temp.c_str());
            lines = getdir(abst);
        }

     }

     else
     {
        if(files[pos] == ".")
        {
            return -1;
        }

        else if(files[pos] == "..")
        {
            enter.pop();
            temp = enter.top();
            strcpy(abst,temp.c_str());
            lines = getdir(abst);

        }

        else
        {
            lft.push(temp);
            temp = enter.top();
            temp+="/";
            temp+=files[pos].c_str();
            enter.push(temp);
            strcpy(abst,temp.c_str());
            lines = getdir(abst);
        }

     }
     /*debug();
     debug1();
     debug2();*/
    return lines;
}

int left_enter()
{
  rght.push(enter.top());  
  temp = lft.top();
  lft.pop();
  if(enter.size() > 1)
    enter.pop();
  strcpy(abst,temp.c_str());
  lines = getdir(abst);
  /*debug();
  debug1();
  debug2();*/
  return lines; 
}

int right_enter()
{
  lft.push(enter.top());
  enter.push(rght.top());
  temp = rght.top();
  rght.pop();
  strcpy(abst,temp.c_str());
  lines = getdir(abst);
  /*debug();
  debug1();
  debug2();*/
  return lines; 
}

int backspace()
{
    lft.push(enter.top());
    enter.pop();
    temp = enter.top();
    strcpy(abst,temp.c_str());
    lines = getdir(abst);
    return lines; 
}

int command_mode()
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("\033[%d;1H",w.ws_row);
    printf("\033[30;");
    printf("47m");
    printf("Command Line:");
    printf("\033[0m");
    return 1;
}

