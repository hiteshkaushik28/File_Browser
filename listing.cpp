/*  
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    REDISTRIBUTION IS PROHIBITED 
*/

#include "listing.h"

//function to display list of all files and directories in the current directory

int main()
{	
	// reset and clear terminal
	blank();
	
	// list files and directories
    getdir();

    // reset cursor to 1st line and 1st column
    resetcursor();

    return 0;
}
