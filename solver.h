//
// Created by Gihyeon Yang on 2019/11/29.
//

#ifndef INC_2019_2_ALGORITHM_TERMPROJECT_SOLVER_H

#include <sys/time.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <deque>
#include <vector>
#include <queue>
#include <set>
#include <map>

#define INC_2019_2_ALGORITHM_TERMPROJECT_SOLVER_H

typedef struct MOVES {
    std::string log;
    int y;
    int x;
} _t_moves;

typedef struct PLAYER {
    char state;
    int y;
    int x;
} _t_player;

typedef struct STATE {
    std::string state_str;
    std::string move_list;
    int moves;
    int pushes;
    int total_cost;
    int h_score;
} _t_state;

typedef struct SEARCH_STATE {
    _t_state node;
    int node_count;
    int rep_node_count;
    int fringe_node;
    int explored_count;
} _t_search_state;

int heuristics(const _t_state &cur_state);

std::queue <_t_state> gen_valid_states(const _t_state &cur_state);

_t_search_state a_start(_t_state &init_state);

void auto_mode_game(void);

#endif //INC_2019_2_ALGORITHM_TERMPROJECT_SOLVER_H
