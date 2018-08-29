/*  
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/
#ifndef LISTING_H
#define LISTING_H
// Headers
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <bits/stdc++.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iomanip>
#include <vector>

using namespace std;

/* Global data structure for file names */
extern vector<string>files;
extern char enter[PATH_MAX];

/* Function Declarations */
void blank();
void resetcursor();
int getdir(char *);
int dir_enter(int,char *);

#endif



