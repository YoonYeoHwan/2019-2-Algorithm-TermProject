#include "map.h"
#include "score.h"
#include <string.h>
#include <iostream>
#include <ncurses.h>
#include <stack>

typedef struct STEP {
    std::string map;
    int y;
    int x;
} _t_step;

enum {
    SPACE, WALL, BOX, GOAL, OUT, BOX_ON_GOAL
};

class Game {
private:
    score s;
    mapArray m;
    WINDOW *game_map;
    WINDOW *win_push;
    WINDOW *win_level;
    WINDOW *win_step;
    WINDOW *win_clear;
    WINDOW *win_end;
    std::stack <_t_step> stack_step;
    int map_arr[10][10];
    int a;
    int b;
    int goalCount;
public:
    Game() {
        initscr();
        keypad(stdscr, TRUE);
        curs_set(0);
        noecho();
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_WHITE);
        init_pair(2, COLOR_RED, COLOR_WHITE);
        init_pair(3, COLOR_CYAN, COLOR_WHITE);
        init_pair(4, COLOR_RED, COLOR_RED);
        init_pair(5, COLOR_GREEN, COLOR_GREEN);
        init_pair(6, COLOR_WHITE, COLOR_BLACK);

        resize_term(40, 27);
        attron(COLOR_PAIR(2));
        border('*', '*', '*', '*', '*', '*', '*', '*');
        mvprintw(2, 7, "push box game");
        mvprintw(9, 7, "F1 is restart");
        attroff(COLOR_PAIR(2));

        win_level = newwin(4, 7, 4, 2);
        wborder(win_level, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        mvwprintw(win_level, 1, 1, "Level");
        mvwprintw(win_level, 2, 3, "1");
        win_push = newwin(4, 7, 4, 10);
        wborder(win_push, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        mvwprintw(win_push, 1, 1, "Push");
        mvwprintw(win_push, 2, 3, "0");
        win_step = newwin(4, 7, 4, 18);
        wborder(win_step, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        mvwprintw(win_step, 1, 1, "Step");
        mvwprintw(win_step, 2, 3, "0");

        refresh();
        wrefresh(win_level);
        wrefresh(win_push);
        wrefresh(win_step);
    }

    void push_step(void);

    void setMap(int level);

    void newGame(int map[][10]);

    void moveUP(int map[][10]);

    void moveDOWN(int map[][10]);

    void moveRIGHT(int map[][10]);

    void moveLEFT(int map[][10]);

    bool finishGame();

    void stepRefresh(WINDOW *win, int step);

    void pushRefresh(WINDOW *win, int push);

    int (*getMap())[10];

    std::string getStrMap();

    void clearMap();

    void reloadMap();

    void ending();

    void print_usermode();
};