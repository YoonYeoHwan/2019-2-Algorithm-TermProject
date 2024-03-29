#include <ncurses.h>
#include "game.h"
#include "map.h"
#include <sstream>

using namespace std;

int (*Game::getMap())[10] {
    return map_arr;
}

void Game::setMap(int level) {
    m.set_map(map_arr, level, a, b, goalCount);
#ifndef DEBUG_AUTO
    mvwprintw(win_level, 2, 3, "%d", level);
    wrefresh(win_level);
#endif
}

std::string Game::getStrMap(void) {
    string str_map = "";

    int y = a - 1;
    int x = b - 3;

    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            if (y == row && x == col) {
                str_map += "@";
            } else {
                switch (this->map_arr[row][col]) {
                    case SPACE:
                        str_map += " ";
                        break;
                    case WALL:
                        str_map += "#";
                        break;
                    case BOX:
                        str_map += "$";
                        break;
                    case GOAL:
                        str_map += ".";
                        break;
                    case 4:
                        str_map += "#";
                        break;
                    default:
                        break;
                }
            }
        }
        str_map += "\n";
    }

    return str_map;
}

void Game::push_step(void) {
    _t_step step = {getStrMap(), a, b};
    stack_step.push(step);
}

void Game::newGame(int map[][10]) {
    game_map = newwin(12, 14, 10, 7);
    wborder(game_map, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j] == 1) {
                wattron(game_map, COLOR_PAIR(1));
                mvwprintw(game_map, i + 1, j + 3, "#");
                wattroff(game_map, COLOR_PAIR(1));
            } else if (map[i][j] == 2) {
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, i + 1, j + 3, "$");
                wattroff(game_map, COLOR_PAIR(5));
            } else if (map[i][j] == 3) {
                mvwprintw(game_map, i + 1, j + 3, ".");
            } else mvwprintw(game_map, i + 1, j + 3, " ");
        }
    }
    mvwprintw(game_map, a, b, "@");

    // print_usermode();

    wrefresh(game_map);
}

void Game::moveUP(int map[][10]) {
    int up = a - 2;
    int up2 = a - 3;
    if (map[up][b - 3] == WALL) return;
    else if (map[up][b - 3] == BOX) {
        if (map[up2][b - 3] == WALL) return;
        else if (map[up2][b - 3] == BOX || map[up2][b - 3] == BOX_ON_GOAL) return;
        else {
            if (map[up2][b - 3] == GOAL) {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a - 2, b, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[up2][b - 3] = BOX_ON_GOAL;
                map[up][b - 3] = SPACE;
            } else {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a - 2, b, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[up2][b - 3] = BOX;
                map[up][b - 3] = SPACE;
            }
        }
    } else if (map[up][b - 3] == BOX_ON_GOAL) {
        if (map[up2][b - 3] == WALL) return;
        else if (map[up2][b - 3] == BOX || map[up2][b - 3] == BOX_ON_GOAL) return;
        else {
            if (map[up2][b - 3] == GOAL) {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a - 2, b, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[up2][b - 3] = BOX_ON_GOAL;
                map[up][b - 3] = GOAL;
            } else {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a - 2, b, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[up2][b - 3] = BOX;
                map[up][b - 3] = GOAL;
            }
        }

    }
    if (map[a - 1][b - 3] == GOAL) mvwprintw(game_map, a, b, ".");
    else if (map[a - 1][b - 3] == SPACE) mvwprintw(game_map, a, b, " ");

    if (map[up2][b - 3] == BOX_ON_GOAL) {
        wattron(game_map, COLOR_PAIR(6));
        mvwprintw(game_map, a - 2, b, "$");
        wattroff(game_map, COLOR_PAIR(6));
    }

    a--;
    s.stepUp();
    mvwprintw(game_map, a, b, "@");
    stepRefresh(win_step, s.getStep());
    pushRefresh(win_push, s.getPush());
    wrefresh(game_map);

    this->push_step();
}

void Game::moveDOWN(int map[][10]) {
    int down = a;
    int down2 = a + 1;
    if (map[down][b - 3] == WALL) return;
    else if (map[down][b - 3] == BOX) {
        if (map[down2][b - 3] == WALL) return;
        else if (map[down2][b - 3] == BOX || map[down2][b - 3] == BOX_ON_GOAL) return;
        else {
            if (map[down2][b - 3] == GOAL) {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a + 2, b, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[down2][b - 3] = BOX_ON_GOAL;
                map[down][b - 3] = SPACE;
            } else {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a + 2, b, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[down2][b - 3] = BOX;
                map[down][b - 3] = SPACE;
            }
        }
    } else if (map[down][b - 3] == BOX_ON_GOAL) {
        if (map[down2][b - 3] == WALL) return;
        else if (map[down2][b - 3] == BOX || map[down2][b - 3] == BOX_ON_GOAL) return;
        else {
            if (map[down2][b - 3] == GOAL) {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a + 2, b, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[down2][b - 3] = BOX_ON_GOAL;
                map[down][b - 3] = GOAL;
            } else {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a + 2, b, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[down2][b - 3] = BOX;
                map[down][b - 3] = GOAL;
            }
        }

    }

    if (map[a - 1][b - 3] == GOAL) mvwprintw(game_map, a, b, ".");
    else if (map[a - 1][b - 3] == SPACE) mvwprintw(game_map, a, b, " ");

    if (map[down2][b - 3] == BOX_ON_GOAL) {
        wattron(game_map, COLOR_PAIR(6));
        mvwprintw(game_map, a + 2, b, "$");
        wattroff(game_map, COLOR_PAIR(6));
    }

    a++;
    s.stepUp();
    mvwprintw(game_map, a, b, "@");
    stepRefresh(win_step, s.getStep());
    pushRefresh(win_push, s.getPush());
    wrefresh(game_map);

    this->push_step();
}

void Game::moveLEFT(int map[][10]) {
    int left = b - 4;
    int left2 = b - 5;
    if (map[a - 1][left] == WALL) return;
    else if (map[a - 1][left] == BOX) {
        if (map[a - 1][left2] == WALL) return;
        else if (map[a - 1][left2] == BOX || map[a - 1][left2] == BOX_ON_GOAL) return;
        else {
            if (map[a - 1][left2] == GOAL) {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a, b - 2, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[a - 1][left2] = BOX_ON_GOAL;
                map[a - 1][left] = SPACE;
            } else {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a, b - 2, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[a - 1][left2] = BOX;
                map[a - 1][left] = SPACE;
            }
        }
    } else if (map[a - 1][left] == BOX_ON_GOAL) {
        if (map[a - 1][left2] == WALL) return;
        else if (map[a - 1][left2] == BOX || map[a - 1][left2] == BOX_ON_GOAL) return;
        else {
            if (map[a - 1][left2] == GOAL) {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a, b - 2, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[a - 1][left2] = BOX_ON_GOAL;
                map[a - 1][left] = GOAL;
            } else {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a, b - 2, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[a - 1][left2] = BOX;
                map[a - 1][left] = GOAL;
            }
        }

    }
    if (map[a - 1][b - 3] == GOAL) mvwprintw(game_map, a, b, ".");
    else if (map[a - 1][b - 3] == SPACE) mvwprintw(game_map, a, b, " ");

    if (map[a - 1][left2] == BOX_ON_GOAL) {
        wattron(game_map, COLOR_PAIR(6));
        mvwprintw(game_map, a, b - 2, "$");
        wattroff(game_map, COLOR_PAIR(6));
    }

    b--;
    s.stepUp();
    mvwprintw(game_map, a, b, "@");
    stepRefresh(win_step, s.getStep());
    pushRefresh(win_push, s.getPush());
    wrefresh(game_map);

    this->push_step();
}

void Game::moveRIGHT(int map[][10]) {
    int right = b - 2;
    int right2 = b - 1;
    if (map[a - 1][right] == WALL) return;
    else if (map[a - 1][right] == BOX) {
        if (map[a - 1][right2] == WALL) return;
        else if (map[a - 1][right2] == BOX || map[a - 1][right2] == BOX_ON_GOAL) return;
        else {
            if (map[a - 1][right2] == GOAL) {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a, b + 2, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[a - 1][right2] = BOX_ON_GOAL;
                map[a - 1][right] = SPACE;
            } else {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a, b + 2, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[a - 1][right2] = BOX;
                map[a - 1][right] = SPACE;
            }
        }
    } else if (map[a - 1][right] == BOX_ON_GOAL) {
        if (map[a - 1][right2] == WALL) return;
        else if (map[a - 1][right2] == BOX || map[a - 1][right2] == BOX_ON_GOAL) return;
        else {
            if (map[a - 1][right2] == GOAL) {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a, b + 2, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[a - 1][right2] = BOX_ON_GOAL;
                map[a - 1][right] = GOAL;
            } else {
                s.pushUp();
                wattron(game_map, COLOR_PAIR(5));
                mvwprintw(game_map, a, b + 2, "$");
                wattroff(game_map, COLOR_PAIR(5));
                map[a - 1][right2] = BOX;
                map[a - 1][right] = GOAL;
            }
        }

    }
    if (map[a - 1][b - 3] == GOAL) mvwprintw(game_map, a, b, ".");
    else if (map[a - 1][b - 3] == SPACE) mvwprintw(game_map, a, b, " ");

    if (map[a - 1][right2] == BOX_ON_GOAL) {
        wattron(game_map, COLOR_PAIR(6));
        mvwprintw(game_map, a, b + 2, "$");
        wattroff(game_map, COLOR_PAIR(6));
    }

    b++;
    s.stepUp();
    mvwprintw(game_map, a, b, "@");
    stepRefresh(win_step, s.getStep());
    pushRefresh(win_push, s.getPush());
    wrefresh(game_map);

    this->push_step();
}

bool Game::finishGame() {
    int cnt = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map_arr[i][j] == 5) cnt++;
        }
    }
    if (goalCount == cnt) return true;
    else return false;
}

void Game::stepRefresh(WINDOW *win, int step) {
    mvwprintw(win, 2, 3, "%d", step);
    wrefresh(win_step);
}

void Game::pushRefresh(WINDOW *win, int push) {
    mvwprintw(win, 2, 3, "%d", push);
    wrefresh(win_push);
}

void Game::clearMap() {
    win_clear = newwin(40, 27, 0, 0);
    wattron(win_clear, COLOR_PAIR(2));
    wborder(win_clear, '*', '*', '*', '*', '*', '*', '*', '*');
    mvwprintw(win_clear, 5, 6, "CONGRATULATIONS!");
    mvwprintw(win_clear, 12, 8, "Stage Clear");
    mvwprintw(win_clear, 20, 7, "PRESS ANY KEY");
    mvwprintw(win_clear, 22, 5, "TO PLAY NEXT LEVEL");
    wattroff(win_clear, COLOR_PAIR(2));
    refresh();
    wrefresh(win_clear);
    delwin(win_clear);
    getch();
}

void Game::reloadMap() {
    resize_term(40, 27);
    attron(COLOR_PAIR(2));
    border('*', '*', '*', '*', '*', '*', '*', '*');
    mvprintw(2, 7, "push box game");
    attroff(COLOR_PAIR(2));
    win_level = newwin(4, 7, 4, 2);
    wborder(win_level, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    mvwprintw(win_level, 1, 1, "Level");
    win_push = newwin(4, 7, 4, 10);
    wborder(win_push, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    mvwprintw(win_push, 1, 1, "Push");
    mvwprintw(win_push, 2, 3, "%d", s.getPush());
    win_step = newwin(4, 7, 4, 18);
    wborder(win_step, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    mvwprintw(win_step, 1, 1, "Step");
    mvwprintw(win_step, 2, 3, "%d", s.getStep());
    refresh();
    wrefresh(win_push);
    wrefresh(win_step);
}

void Game::ending() {
    win_end = newwin(40, 27, 0, 0);
    wattron(win_end, COLOR_PAIR(2));
    wborder(win_end, '*', '*', '*', '*', '*', '*', '*', '*');
    mvwprintw(win_end, 5, 6, "CONGRATULATIONS!");
    mvwprintw(win_end, 6, 4, "YOU CLEAR ALL LEVEL!");
    mvwprintw(win_end, 20, 7, "PRESS ANY KEY");
    mvwprintw(win_end, 22, 8, "TO EXIT GAME");
    wattroff(win_end, COLOR_PAIR(2));
    refresh();
    wrefresh(win_end);
    getch();
}

void Game::print_usermode() {
    int y_list[] = {27, 28, 29, 30, 31, 31, 31, 30, 29, 28, 27, 27, 27, 27, 28, 29, 29, 29, 30, 31, 31, 31, 27, 27, 27,
                    28, 29, 29, 29, 30, 31, 31, 31, 27, 27, 27, 28, 28, 29, 29, 29, 30, 30, 31, 31,
                    33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35,
                    35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37};
    int x_list[] = {5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 11, 10, 9, 9, 9, 10, 11, 11, 11, 10, 9, 13, 14, 15, 13, 13, 14, 15,
                    13, 13, 14, 15, 17, 18, 19, 17, 19, 17, 18, 19, 17, 18, 17, 19,
                    5, 7, 9, 10, 11, 13, 14, 17, 18, 19, 5, 6, 7, 9, 11, 13, 15, 17, 5, 6, 7, 9, 11, 13, 15, 17, 18, 19,
                    5, 7, 9, 11, 13, 15, 17, 5, 7, 9, 10, 11, 13, 14, 17, 18, 19};

    attron(COLOR_PAIR(4));
    for (int i = 0; i < 91; i++)
        mvprintw(y_list[i] - 2, x_list[i] + 1, "#");
    attroff(COLOR_PAIR(4));
}