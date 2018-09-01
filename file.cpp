/*                               
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/

/* main control file */

#include "listing.h"
#include "keypress.h"


bool home_flag = false;
int main()
{	
    char path[PATH_MAX];
    int d;
	//int entry_count=0;
	// reset and clear terminal
	blank();
	
	// list files and directories
    if (getcwd(path, sizeof(path)) != NULL) 
    {
        d=getdir(path);
        string tmp(path);
        enter.push(tmp);
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
        }

        else if (c == LEFT) 
        {
                if(lft.size() == 0)
                    continue;
                else
                    d = left_enter();
        }

        else if (c == RIGHT) 
        {
                if(rght.size() == 0)
                    continue;
                else
                    d = right_enter();
        }

        else if (c == HOME) 
        {
                
                if(enter.size() == 1)
                    continue;
                else
                {
                    home_flag = true;
                    lft.push(enter.top());
                    enter.push(path);
                    d = getdir(path);
                    /*debug();
                    debug1();
                    debug2();*/
                }
        }

        else if(c == BACKSPACE)
        {  
            if(enter.size() <= 1)
                continue;
            else 
                d = backspace();
            /*debug();
            debug1();
            debug2();*/
        }

        else if(c == COLON)
        {
            command_mode();
        }

        else continue; 
    }
    

	return 0;
}
