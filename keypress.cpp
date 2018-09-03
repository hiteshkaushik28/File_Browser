/*                               
    AUTHOR: HITESH KAUSHIK 
    ROLL NO: 2018201057 
    COPYRIGHT (C) HITESH KAUSHIK PG-1
*/

#include "keypress.h"

struct termios term, oterm;

int gett(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

int kbhit(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    if (c != -1) ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}

int kbesc(void)
{
    int c;

    if (!kbhit()) return ESCAPE;
    c = gett();
    if (c == '[') {
        switch (gett()) {
            case 'A':
                c = UP;
                break;
            case 'B':
                c = DOWN;
                break;
            case 'C':
                c = RIGHT;
                break;
            case 'D':
                c = LEFT;
                break;
            default:
                c = 0;
                break;
        }
    }
    else {
        c = 0;
    }
    if (c == 0) while (kbhit()) gett();
    return c;
}

int kbget(void)
{
    int c;

    c = gett();
    return (c == ESCAPE) ? kbesc() : c;
}

