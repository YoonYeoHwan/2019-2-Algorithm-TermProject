#include "user.h"
#include "solver.h"
#include "ncurses.h"
#include <iostream>

enum MODE {
    USER = 0,
    AUTO
} _t_mode;

MODE init_game(void) {
    WINDOW *win_start;

    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);

    win_start = newwin(40, 27, 0, 0);
    wattron(win_start, COLOR_PAIR(2));
    wborder(win_start, '*', '*', '*', '*', '*', '*', '*', '*');
    wattroff(win_start, COLOR_PAIR(2));
    wattron(win_start, COLOR_PAIR(2));
    mvwprintw(win_start, 4, 7, "PUSH BOX GAME");
    mvwprintw(win_start, 11, 7, "PRESS \"u\" KEY");
    mvwprintw(win_start, 13, 5, "TO START USER MODE");
    mvwprintw(win_start, 17, 7, "PRESS \"s\" KEY");
    mvwprintw(win_start, 19, 4, "TO START SOLVER MODE");
    wattroff(win_start, COLOR_PAIR(2));
    refresh();
    wrefresh(win_start);

    while(1) {
        int inputKey = getch();
        if (inputKey == 'u') return USER;
        else if (inputKey == 's') return AUTO;
    }
    delwin(win_start);
}