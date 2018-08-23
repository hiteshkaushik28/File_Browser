/*  
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    REDISTRIBUTION IS PROHIBITED 
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <bits/stdc++.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
using namespace std;

// clear and reset terminal
void blank()
{
    printf("\033c" );
}

void resetcursor()
{
    printf("\033[1;1H" );
}

int getdir ()
{
    vector<string> files;// vector to store file names
    vector<string>:: iterator itr;// vector iterator

    // structures for file stats, dirent return values
    struct stat fileStat; 
    char path[256],name[20];
    DIR *dp;
    struct dirent *dirp;
    string dir=".";

    // structures to store owner and group information
    struct passwd *pw;
    struct group  *gr;


    //handling for opendir misbehave
    if((dp  = opendir(dir.c_str())) == NULL) 
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }


    //create relative path
    strcpy (path,".");
    strcat (path, "/");


    // pushing all file names into vector
    while ((dirp = readdir(dp)) != NULL) 
    {
        files.push_back(string(dirp->d_name));       
    }

    // sort file name in lex order
    sort(files.begin(),files.end()); 

    
    //traverse all files and pass them to stat
    printf("PERMISSIONS\tOWNER\tGROUP\tSIZE\t LAST MODIFIED\t\tNAME\n");
    for(itr=files.begin();itr!=files.end();++itr)  
    {
        strcpy(name,(*itr).c_str());
        strcpy(path,".");
        strcat(path,"/");
        strcat(path,name);
        if (!stat(path, &fileStat))
        {
            //convert uid and gid to uname,gname
            pw=getpwuid(fileStat.st_uid);
            gr=getgrgid(fileStat.st_gid);

            //print permissions
            printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

            //output file properties
            cout<<"\t"<<string(pw->pw_name)<<"\t"<<string(gr->gr_name)<<"\t"<<(int)fileStat.st_size<<"\t"<<string(ctime(&fileStat.st_mtime)).substr(0,19)<<"\t"<<string(name);
        } 
        else
        {
            perror("stat method failed");
        }
       
        printf("\n");
    }

return 0;
}



