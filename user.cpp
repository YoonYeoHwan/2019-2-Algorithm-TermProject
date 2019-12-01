//
// Created by Gihyeon Yang on 2019/11/29.
//
#include "user.h"
#include "game.h"

void user_mode_game(void) {
    // Game g;

    int level = 1;

    while (1) {
        bool checkF1 = false;
        Game g;

        if (level == 10) {
            g.ending();
            getch();
            endwin();
            break;
        }

        g.setMap(level++);
        g.newGame(g.getMap());
        g.print_usermode();

        while (true) {
            int inputKey = getch();

            if (inputKey == 'q') {
                return;
            }

            if (inputKey == KEY_F(1)) {
                g.setMap(--level);
                g.newGame(g.getMap());
                checkF1 = true;
                break;
            }
            if (inputKey == KEY_UP) {
                g.moveUP(g.getMap());
                if (g.finishGame()) {
                    checkF1 = false;
                    break;
                }
            } else if (inputKey == KEY_DOWN) {
                g.moveDOWN(g.getMap());
                if (g.finishGame()) {
                    checkF1 = false;
                    break;
                }
            } else if (inputKey == KEY_RIGHT) {
                g.moveRIGHT(g.getMap());
                if (g.finishGame()) {
                    checkF1 = false;
                    break;
                }
            } else if (inputKey == KEY_LEFT) {
                g.moveLEFT(g.getMap());
                if (g.finishGame()) {
                    checkF1 = false;
                    break;
                }
            }
        }
        if (level != 10 && !checkF1) {
            g.clearMap();
            g.reloadMap();
        }

    }

}