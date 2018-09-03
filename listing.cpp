/*                               
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/

/*ls module file */

#include "listing.h"
#include "keypress.h"

vector<string> tokens;
vector<string> files;
stack<string> enter;
stack<string> lft;
stack<string> rght;
struct winsize w;
static string temp;
static char abst[PATH_MAX];
static int lines;

/*
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
     
}*/

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

//resetcursor();
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

void command_prompt()
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("\033[%d;1H",w.ws_row);
    printf("%c[2K", 27);
    printf("\033[30;");
    printf("47m");
    printf("Command Line: ");
    printf("\033[0m");
    printf(" ");
    fflush(stdin);   
}

int command_mode()
{
   int ret;
   command_prompt(); 
   char input[256],*tok;
    
    int ch,i=0;
    
    while((ch = kbget()) != ESCAPE)
    {
        if(ch == BACKSPACE)
        {
            if(i>0)
            {
                --i;
                const char delbuf[] = "\b \b";
                write(STDOUT_FILENO, delbuf, strlen(delbuf));
            }
        }


        else if (ch == ENTER)
        {
            i=0;
            tokens.clear();
            command_prompt();
            tok = strtok(input, " ");
            while(tok != NULL)
            {
                tokens.push_back(tok);
                tok = strtok(NULL," ");
            }

            ret = command_process();
            command_prompt();
        }
        else
        {
            input[i++] = char(ch);
            printf("%c",ch);
        }
    }

    printf("%c[2K", 27);
    return ret;
}

int command_process()
{
    char temp1[1000],temp2[1000],temp3[PATH_MAX];
   
    int l = tokens.size();
    int t = 0;

    if(strcmp((tokens[0]).c_str(),"copy") == 0)
    {
        for(unsigned int i=1;i<(l-1);++i)
        {
            getcwd(temp1, sizeof(temp1));
            strcat(temp1,"/");
            strcat(temp1,(tokens[i].c_str()));

            getcwd(temp2, sizeof(temp2));
            strcat(temp2,"/");
            strcat(temp2,(tokens[l-1].c_str()));
            strcpy(temp3,temp2);
            strcat(temp2,"/");
            strcat(temp2,(tokens[i].c_str()));            
            cp(temp1,temp2);
            t = getdir(temp3);

        }
    }
    else// if (strcmp((tokens[0]).c_str(),"goto") == 0)
    {
        getcwd(temp1, sizeof(temp1));
        strcat(temp1,"/");
        strcat(temp1,(tokens[1].c_str()));
        t = getdir(temp1);
        command_prompt();
    }
    
return t;
}

void cp(char *source,char *destination)
{
 
  int in_fd, out_fd, n_chars;
  char buf[1024];
 
  /* open files */
  if( (in_fd=open(source, O_RDONLY)) == -1 )
  {
    err("Cannot open ", source);
  }
 
 
  if( (out_fd=creat(destination, 0644)) == -1 )
  {
    err("Cannot create ", destination);
  }
 
 
  /* copy files */
  while( (n_chars = read(in_fd, buf, 1024)) > 0 )
  {
    if( write(out_fd, buf, n_chars) != n_chars )
    {
      err("Write error to ", destination);
    }
 
 
    if( n_chars == -1 )
    {
      err("Read error from ", source);
    }
  }
 
     /* close files */
    if( close(in_fd) == -1 || close(out_fd) == -1 )
    {
      err("Error closing files", "");
    }
 
}
 
 
  void err(char *s1, char *s2)
  {
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
  }
