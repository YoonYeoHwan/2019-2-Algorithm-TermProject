#include "user.h"

enum MODE {
    USER = 0,
    AUTO
} _t_mode;

MODE init_game(void) {
    return USER;
}