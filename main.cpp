#include "main.h"
#include <iostream>

#define LEVEL 11

int main() {
    // 0 : USER
    // 1 : AUTO (Solver)
    MODE command = init_game();

    if (command == USER) {
        user_mode_game(LEVEL);
    } else if (command == AUTO) {
        for (int level = 1; level <= LEVEL; level++) {
            auto_mode_game(level);
        }
    }
    return 0;
}
