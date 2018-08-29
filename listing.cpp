/*                               
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/

/*ls module file */

#include "listing.h"

vector<string>files;

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
            cout<<"\t"<<string(pw->pw_name)<<"\t"<<string(gr->gr_name)<<"\t"<<(int)fileStat.st_size<<"\t"<<string(ctime(&fileStat.st_mtime)).substr(4,12)<<"\t"<<string(*itr);

        } 

        else
        {
            perror("stat method failed");
        }
      
        printf("\n");
    }

return count;
}


int dir_enter(int pos,char *path)
{
	int lines;
    char abs[PATH_MAX],name[PATH_MAX];
    strcpy(abs,path);
    strcat(abs,"/");
    strcpy(name,files[pos].c_str());
    strcat(abs,name);
    lines = getdir(abs);
    resetcursor();
    return lines;
}