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

int Game::undo(void) {
    if (stack_step.empty()) return -1;
    if (stack_step.size() == 1) {
        _t_step step = stack_step.top();

//        a = step.y + 0;
//        b = step.x + 0;

        return -1;
    }

    _t_step step = stack_step.top();
    stack_step.pop();

//    cout << step.y << " " << step.x << endl;

    stringstream ss(step.map);
    string line;

    a = step.y + 1;
    b = step.x + 3;

    int temp_row, temp_col;

    int row = 0;

    game_map = newwin(12, 14, 10, 7);
    wborder(game_map, '|', '|', '-', '-', '+', '+', '+', '+');

    while (getline(ss, line, '\n')) {
        int lineLength = line.length();
        for (int col = 0; col < lineLength; ++col) {
            temp_row = row + 1;
            temp_col = col + 3;

            if (line[col] == '#') {
                map_arr[temp_row][temp_col] = WALL;
                wattron(game_map, COLOR_PAIR(1));
                mvwprintw(game_map, temp_row, temp_col, "#");
                wattroff(game_map, COLOR_PAIR(1));
            } else if (line[col] == '$') {
                map_arr[temp_row][temp_col] = BOX;
                mvwprintw(game_map, temp_row, temp_col, "$");
            } else if (line[col] == ' ') {
                map_arr[temp_row][temp_col] = SPACE;
                mvwprintw(game_map, temp_row, temp_col, " ");
            } else if (line[col] == '.') {
                map_arr[temp_row][temp_col] = GOAL;
                mvwprintw(game_map, temp_row, temp_col, ".");
            } else if (line[col] == '@') {
                mvwprintw(game_map, temp_row, temp_col, "@");
            }
        }
        row++;
    }

    mvwprintw(game_map, a, b, "@");
    wrefresh(game_map);
//    cout << a << "-" << b << endl;

    return 1;
}

void Game::push_step(void) {
    _t_step step = {getStrMap(), a, b};
    stack_step.push(step);
}

void Game::newGame(int map[][10]) {
    game_map = newwin(12, 14, 10, 7);
    wborder(game_map, '|', '|', '-', '-', '+', '+', '+', '+');
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j] == 1) {
                wattron(game_map, COLOR_PAIR(1));
                mvwprintw(game_map, i + 1, j + 3, "#");
                wattroff(game_map, COLOR_PAIR(1));
            } else if (map[i][j] == 2) mvwprintw(game_map, i + 1, j + 3, "$");
            else if (map[i][j] == 3) mvwprintw(game_map, i + 1, j + 3, ".");
            else mvwprintw(game_map, i + 1, j + 3, " ");
        }
    }
    mvwprintw(game_map, a, b, "@");
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
                mvwprintw(game_map, a - 2, b, "$");
                map[up2][b - 3] = BOX_ON_GOAL;
                map[up][b - 3] = SPACE;
            } else {
                s.pushUp();
                mvwprintw(game_map, a - 2, b, "$");
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
                mvwprintw(game_map, a - 2, b, "$");
                map[up2][b - 3] = BOX_ON_GOAL;
                map[up][b - 3] = GOAL;
            } else {
                s.pushUp();
                mvwprintw(game_map, a - 2, b, "$");
                map[up2][b - 3] = BOX;
                map[up][b - 3] = GOAL;
            }
        }

    }
    if (map[a - 1][b - 3] == GOAL) mvwprintw(game_map, a, b, ".");
    else if (map[a - 1][b - 3] == SPACE) mvwprintw(game_map, a, b, " ");
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
                mvwprintw(game_map, a + 2, b, "$");
                map[down2][b - 3] = BOX_ON_GOAL;
                map[down][b - 3] = SPACE;
            } else {
                s.pushUp();
                mvwprintw(game_map, a + 2, b, "$");
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
                mvwprintw(game_map, a + 2, b, "$");
                map[down2][b - 3] = BOX_ON_GOAL;
                map[down][b - 3] = GOAL;
            } else {
                s.pushUp();
                mvwprintw(game_map, a + 2, b, "$");
                map[down2][b - 3] = BOX;
                map[down][b - 3] = GOAL;
            }
        }

    }

    if (map[a - 1][b - 3] == GOAL) mvwprintw(game_map, a, b, ".");
    else if (map[a - 1][b - 3] == SPACE) mvwprintw(game_map, a, b, " ");
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
                mvwprintw(game_map, a, b - 2, "$");
                map[a - 1][left2] = BOX_ON_GOAL;
                map[a - 1][left] = SPACE;
            } else {
                s.pushUp();
                mvwprintw(game_map, a, b - 2, "$");
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
                mvwprintw(game_map, a, b - 2, "$");
                map[a - 1][left2] = BOX_ON_GOAL;
                map[a - 1][left] = GOAL;
            } else {
                s.pushUp();
                mvwprintw(game_map, a, b - 2, "$");
                map[a - 1][left2] = BOX;
                map[a - 1][left] = GOAL;
            }
        }

    }
    if (map[a - 1][b - 3] == GOAL) mvwprintw(game_map, a, b, ".");
    else if (map[a - 1][b - 3] == SPACE) mvwprintw(game_map, a, b, " ");
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
                mvwprintw(game_map, a, b + 2, "$");
                map[a - 1][right2] = BOX_ON_GOAL;
                map[a - 1][right] = SPACE;
            } else {
                s.pushUp();
                mvwprintw(game_map, a, b + 2, "$");
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
                mvwprintw(game_map, a, b + 2, "$");
                map[a - 1][right2] = BOX_ON_GOAL;
                map[a - 1][right] = GOAL;
            } else {
                s.pushUp();
                mvwprintw(game_map, a, b + 2, "$");
                map[a - 1][right2] = BOX;
                map[a - 1][right] = GOAL;
            }
        }

    }
    if (map[a - 1][b - 3] == GOAL) mvwprintw(game_map, a, b, ".");
    else if (map[a - 1][b - 3] == SPACE) mvwprintw(game_map, a, b, " ");
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

void Game::lifeRefresh() {
    s.lifeDown();
    mvwprintw(win_life, 2, 3, "%d", s.getLife());
    wrefresh(win_life);
}

int Game::getLife() {
    return s.getLife();
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
    wborder(win_level, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(win_level, 1, 1, "Level");
    win_push = newwin(4, 7, 4, 10);
    wborder(win_push, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(win_push, 1, 1, "Push");
    mvwprintw(win_push, 2, 3, "%d", s.getPush());
    win_step = newwin(4, 7, 4, 18);
    wborder(win_step, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(win_step, 1, 1, "Step");
    mvwprintw(win_step, 2, 3, "%d", s.getStep());
    win_life = newwin(4, 7, 22, 10);
    wborder(win_life, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(win_life, 1, 1, "Life");
    mvwprintw(win_life, 2, 3, "%d", s.getLife());
    refresh();
    wrefresh(win_life);
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

void Game::gameOver() {
    win_over = newwin(40, 27, 0, 0);
    wattron(win_over, COLOR_PAIR(2));
    wborder(win_over, '*', '*', '*', '*', '*', '*', '*', '*');
    mvwprintw(win_over, 5, 9, "GAME OVER!");
    mvwprintw(win_over, 20, 7, "PRESS ANY KEY");
    mvwprintw(win_over, 22, 8, "TO EXIT GAME");
    wattroff(win_over, COLOR_PAIR(2));
    refresh();
    wrefresh(win_over);
    getch();
}