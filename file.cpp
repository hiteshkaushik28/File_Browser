/*                               
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/

/* This is the main control file */

#include "listing.h"
#include "keypress.h"

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
    }

    else 
    {
       perror("getcwd() error");
       return 1;
    }

    // reset cursor to 1st line and 1st column
    resetcursor();

    //call keypress module
    int c,down_count = 1; 
    while (1) 
    {
        c = kbget();
        if (c == QUIT)
        { 
            blank();
            break;
        }
        
        else if (c == RIGHT) 
            backward(1);
                
        else if (c == LEFT) 
            forward(1);

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
            d = dir_enter(down_count-1,path);
        }

        else continue; 
    }
    

	return 0;
}
