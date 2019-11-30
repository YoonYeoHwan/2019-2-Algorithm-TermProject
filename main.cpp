#include "main.h"
#include <iostream>

int main() {
    // 0 : USER
    // 1 : AUTO (Solver)
    MODE command = init_game();

    if (command == USER) {
        user_mode_game();
    } else if (command == AUTO) {
        for (int level = 2; level <= 10; level++) {
            auto_mode_game(level);
            getch();
        }
    }
    return 0;
}
