/*                               
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/

/* main control file */

#include "listing.h"
#include "keypress.h"

bool mode_flag = false;
int main()
{	
    char path[PATH_MAX];
    int d;
	blank();
	
	// list files and directories
    if (getcwd(path, sizeof(path)) != NULL) 
    {
        d=getdir(path);
        string tmp(path);
        enter.push(tmp);
        resetcursor();
    }

    else 
    {
       perror("getcwd() error");
       return 1;
    }
  
  
    //call keypress module
    int c,t,down_count = 1; 
    while (1) 
    {
       if(mode_flag == false)
       {
            c = kbget();

            if (c == QUIT)
            { 
                blank();
                break;
            }
            
            else if (c == UP && down_count > 1)
            {
                up(1);      
                down_count--;
            }

            else if (c == DOWN && down_count < d) 
            {
                down_count++;
                down(1);
       
            }

            else if (c == ENTER) 
            {
                t = dir_enter(down_count-1);
                d=(t>=0)?t:d;
                down_count=1;
                resetcursor();
            }

            else if (c == LEFT) 
            {
                if(lft.size() == 0)
                    continue;
                else
                    d = left_enter();
                resetcursor();
            }

            else if (c == RIGHT) 
            {
                if(rght.size() == 0)
                    continue;
                else
                    d = right_enter();
                resetcursor();
            }

            else if (c == HOME) 
            {
                    
                if(enter.size() == 1)
                    continue;
                else
                {
                    lft.push(enter.top());
                    enter.push(path);
                    d = getdir(path);
                }
                resetcursor();
            }

            else if(c == BACKSPACE)
            {  
                if(enter.size() <= 1)
                    continue;
                else 
                    d = backspace();
                resetcursor();
            }

            else if(c == COLON)
            {
               mode_flag = true;   
            }
       
       else continue; 
    }

    else
    {
        t = command_mode();
        d = (t> 0)?t:d;
        mode_flag = false;
        down_count=1;
        resetcursor();
    }

    }

	return 0;
}
