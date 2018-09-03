/*                               
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/

#ifndef _KEYPRESS_H_

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <limits.h>

/* Escape sequence handling in non-canonical mode */
#define forward(x) 		printf("\033[%dC", (x))
#define backward(x) 	printf("\033[%dD", (x))
#define up(x) 			printf("\033[%dA", (x))
#define down(x) 		printf("\033[%dB", (x))
#define QUIT 			'q' || c == 'Q'
#define ESCAPE  		0x001b
#define ENTER   		0x000a
#define UP      		0x0105
#define DOWN    		0x0106
#define LEFT    		0x0107
#define RIGHT   		0x0108
#define BACKSPACE		127
#define HOME    		'h' || c == 'H'
#define COLON			58

int gett(void);
int kbhit(void);
int kbesc(void);
int kbget(void);
	
#endif