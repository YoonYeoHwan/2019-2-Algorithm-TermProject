#include "main.h"
#include <iostream>

int main() {
    // 0 : USER
    // 1 : AUTO (Solver)
    MODE command = init_game();

    if (command == USER) {
        user_mode_game();
    } else if (command == AUTO) {
        for(int i=1;i<=10;i++) {
            auto_mode_game(i);
        }
    }
    return 0;
}
