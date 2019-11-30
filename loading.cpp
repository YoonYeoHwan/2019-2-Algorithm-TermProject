#include <iostream>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

int main()
{
    initscr();
    curs_set(0);


    int a = 5; int b = 10;
    int n = 1;

    while (1) {   

        mvprintw(10, 5, "Loading . . .");        
        
        if (n%8 == 1){
            mvaddch(a, b++, ' ');
            mvaddch(a, b, '#');
            mvaddch(a, b+1, '#');
        }
        else if (n%8 == 2) {
            mvaddch(a, b++, ' ');
            mvaddch(a, b, '#');
            mvaddch(a+1, b, '#');
        }
        else if (n%8 == 3) {
            mvaddch(a++, b, ' ');
            mvaddch(a, b, '#');
            mvaddch(a+1, b, '#');
        }
        else if (n%8 == 4) {
            mvaddch(a++, b, ' ');
            mvaddch(a, b, '#');
            mvaddch(a, b-1, '#');
        }
        else if (n%8 == 5) {
            mvaddch(a, b--, ' ');
            mvaddch(a, b, '#');
            mvaddch(a, b-1, '#');
        }
        else if (n%8 == 6) {
            mvaddch(a, b--, ' ');
            mvaddch(a, b, '#');
            mvaddch(a-1, b, '#');
        }        
        else if (n%8 == 7) {
            mvaddch(a--, b, ' ');
            mvaddch(a, b, '#');
            mvaddch(a-1, b, '#');
        }
        else if (n%8 == 0) {
            mvaddch(a--, b, ' ');
            mvaddch(a, b, '#');
            mvaddch(a, b+1, '#');
        }
        
        refresh();
        usleep(100000);

        n++;
    }
    getch();
    endwin();
}
