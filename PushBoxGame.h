#include "map.h"
#include "score.h"
#include <string.h>
#include <ncurses.h>

enum {
    Space, Wall, Box, Goal, Out, BoxOnGoal
};


class PushBoxGame {
private:
    score s;
    mapArray m;
    WINDOW *game_map;
    WINDOW *win_push;
    WINDOW *win_level;
    WINDOW *win_step;
    WINDOW *win_start;
    WINDOW *win_clear;
    WINDOW *win_end;
    WINDOW *win_life;
    WINDOW *win_over;
    int map_arr[10][10];
    int a;
    int b;
    int goalCount;
public:
    PushBoxGame() {
        initscr();
        keypad(stdscr, TRUE);
        curs_set(0);
        noecho();
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_WHITE);
        init_pair(2, COLOR_RED, COLOR_WHITE);

        win_start = newwin(27, 27, 0, 0);
        wattron(win_start, COLOR_PAIR(2));
        wborder(win_start, '*', '*', '*', '*', '*', '*', '*', '*');
        wattroff(win_start, COLOR_PAIR(2));
        wattron(win_start, COLOR_PAIR(2));
        mvwprintw(win_start, 4, 7, "PUSH BOX GAME");
        mvwprintw(win_start, 12, 7, "PRESS ANY KEY");
        mvwprintw(win_start, 14, 7, "TO START GAME");
        wattroff(win_start, COLOR_PAIR(2));
        refresh();
        wrefresh(win_start);
        getch();
        delwin(win_start);

        resize_term(27, 27);
        attron(COLOR_PAIR(2));
        border('*', '*', '*', '*', '*', '*', '*', '*');
        mvprintw(2, 7, "push box game");
        mvprintw(9, 7, "F1 is restart");
        attroff(COLOR_PAIR(2));

        win_level = newwin(4, 7, 4, 2);
        wborder(win_level, '|', '|', '-', '-', '+', '+', '+', '+');
        mvwprintw(win_level, 1, 1, "Level");
        mvwprintw(win_level, 2, 3, "1");
        win_push = newwin(4, 7, 4, 10);
        wborder(win_push, '|', '|', '-', '-', '+', '+', '+', '+');
        mvwprintw(win_push, 1, 1, "Push");
        mvwprintw(win_push, 2, 3, "0");
        win_step = newwin(4, 7, 4, 18);
        wborder(win_step, '|', '|', '-', '-', '+', '+', '+', '+');
        mvwprintw(win_step, 1, 1, "Step");
        mvwprintw(win_step, 2, 3, "0");
        win_life = newwin(4, 7, 22, 10);
        wborder(win_life, '|', '|', '-', '-', '+', '+', '+', '+');
        mvwprintw(win_life, 1, 1, "Life");
        mvwprintw(win_life, 2, 3, "3");
        refresh();
        wrefresh(win_level);
        wrefresh(win_push);
        wrefresh(win_step);
        wrefresh(win_life);
    }

    void setMap(int level);

    void newGame(int map[][10]);

    void moveUP(int map[][10]);

    void moveDOWN(int map[][10]);

    void moveRIGHT(int map[][10]);

    void moveLEFT(int map[][10]);

    bool finishGame();

    void stepRefresh(WINDOW *win, int step);

    void pushRefresh(WINDOW *win, int push);

    void lifeRefresh();

    int getlife();

    int (*getMap())[10];

    void clearMap();

    void reloadMap();

    void ending();

    void gameover();
};