//
// Created by Gihyeon Yang on 2019/11/29.
//

#include "solver.h"
#include "game.h"

#define MOVE_COST 1
#define PUSH_COST 1

using namespace std;

int heuristics(const _t_state &cur_state) {
    queue <_t_state> valid_moves;

    vector <pair<int, int> > boxes;
    vector <vector<char> > level_map;

    stringstream ss(cur_state.state_str);
    string line;

    int score = 0, row = 0;
    while (getline(ss, line, '\n')) {
        vector<char> temp;
        level_map.push_back(temp);
        int lineLength = line.length();
        for (int col = 0; col < lineLength; ++col) {
            if (line[col] == '$') {
                boxes.push_back(make_pair(col, row));
            }
            level_map[row].push_back(line[col]);
        }
        row++;
    }

    for (pair<int, int> box : boxes) {
        bool n_wall = false;
        bool e_wall = false;
        bool s_wall = false;
        bool w_wall = false;
        bool in_corner = false;

        int cur_box_y = box.second;
        int cur_box_x = box.first;

        if (level_map[cur_box_y - 1][cur_box_x] == '#')
            n_wall = true;
        if (level_map[cur_box_y][cur_box_x + 1] == '#')
            e_wall = true;
        if (level_map[cur_box_y + 1][cur_box_x] == '#')
            s_wall = true;
        if (level_map[cur_box_y][cur_box_x - 1] == '#')
            w_wall = true;

        in_corner = (n_wall && e_wall) ||
                    (n_wall && w_wall) ||
                    (s_wall && e_wall) ||
                    (s_wall && w_wall);

        if (in_corner) {
            score += 1000;
        } else {
            if (n_wall) {
                bool safe = false;
                bool corner_e = false;
                bool corner_w = false;
                int level_map_size = level_map[cur_box_y].size();
                for (int i = cur_box_x + 1; i < level_map_size; i++) {
                    if ((level_map[cur_box_y][i] == '.') ||
                        (level_map[cur_box_y][i] == '*') ||
                        (level_map[cur_box_y][i] == '+') ||
                        (level_map[cur_box_y - 1][i] != '#')) {
                        safe = true;
                        break;
                    }

                    if ((level_map[cur_box_y][i] == '#') &&
                        (level_map[cur_box_y - 1][i] == '#')) {
                        corner_e = true;
                        break;
                    }
                }

                for (int i = cur_box_x - 1; i >= 0; i--) {
                    if ((level_map[cur_box_y][i] == '.') ||
                        (level_map[cur_box_y][i] == '*') ||
                        (level_map[cur_box_y][i] == '+') ||
                        (level_map[cur_box_y - 1][i] != '#')) {
                        safe = true;
                        break;
                    }

                    if ((level_map[cur_box_y][i] == '#') &&
                        (level_map[cur_box_y - 1][i] == '#')) {
                        corner_w = true;
                        break;
                    }
                }

                if (!safe && corner_e && corner_w) {
                    score += 1000;
                }
            }

            if (e_wall) {
                bool safe = false;
                bool corner_n = false;
                bool corner_s = false;

                for (int i = cur_box_y - 1; i >= 0; i--) {
                    if ((level_map[i][cur_box_x] == '.') ||
                        (level_map[i][cur_box_x] == '*') ||
                        (level_map[i][cur_box_x] == '+') ||
                        (level_map[i][cur_box_x + 1] != '#')) {
                        safe = true;
                        break;
                    }

                    if ((level_map[i][cur_box_x] == '#') &&
                        (level_map[i][cur_box_x + 1] == '#')) {
                        corner_n = true;
                        break;
                    }
                }

                int level_map_size = level_map.size();
                for (int i = cur_box_y + 1; i < level_map_size; i++) {
                    if ((level_map[i][cur_box_x] == '.') ||
                        (level_map[i][cur_box_x] == '*') ||
                        (level_map[i][cur_box_x] == '+') ||
                        (level_map[i][cur_box_x + 1] != '#')) {
                        safe = true;
                        break;
                    }

                    if ((level_map[i][cur_box_x] == '#') &&
                        (level_map[i][cur_box_x + 1] == '#')) {
                        corner_s = true;
                        break;
                    }
                }

                if (!safe && corner_n && corner_s) {
                    score += 1000;
                }
            }

            if (s_wall) {
                bool safe = false;
                bool corner_e = false;
                bool corner_w = false;

                int level_map_size = level_map[cur_box_y].size();
                for (int i = cur_box_x + 1; i < level_map_size; i++) {
                    if ((level_map[cur_box_y][i] == '.') ||
                        (level_map[cur_box_y][i] == '*') ||
                        (level_map[cur_box_y][i] == '+') ||
                        (level_map[cur_box_y + 1][i] != '#')) {
                        safe = true;
                        break;
                    }

                    if ((level_map[cur_box_y][i] == '#') &&
                        (level_map[cur_box_y + 1][i] == '#')) {
                        corner_e = true;
                        break;
                    }
                }

                for (int i = cur_box_x - 1; i >= 0; i--) {
                    if ((level_map[cur_box_y][i] == '.') ||
                        (level_map[cur_box_y][i] == '*') ||
                        (level_map[cur_box_y][i] == '+') ||
                        (level_map[cur_box_y + 1][i] != '#')) {
                        safe = true;
                        break;
                    }

                    if ((level_map[cur_box_y][i] == '#') &&
                        (level_map[cur_box_y + 1][i] == '#')) {
                        corner_w = true;
                        break;
                    }
                }

                if (!safe && corner_e && corner_w) {
                    score += 1000;
                }
            }

            if (w_wall) {
                bool safe = false;
                bool corner_n = false;
                bool corner_s = false;

                for (int i = cur_box_y - 1; i >= 0; i--) {
                    if ((level_map[i][cur_box_x] == '.') ||
                        (level_map[i][cur_box_x] == '*') ||
                        (level_map[i][cur_box_x] == '+') ||
                        (level_map[i][cur_box_x - 1] != '#')) {
                        safe = true;
                        break;
                    }

                    if ((level_map[i][cur_box_x] == '#') &&
                        (level_map[i][cur_box_x - 1] == '#')) {
                        corner_n = true;
                        break;
                    }
                }

                int level_map_size = level_map.size();
                for (int i = cur_box_y + 1; i < level_map_size; i++) {
                    if ((level_map[i][cur_box_x] == '.') ||
                        (level_map[i][cur_box_x] == '*') ||
                        (level_map[i][cur_box_x] == '+') ||
                        (level_map[i][cur_box_x - 1] != '#')) {
                        safe = true;
                        break;
                    }

                    if ((level_map[i][cur_box_x] == '#') &&
                        (level_map[i][cur_box_x - 1] == '#')) {
                        corner_s = true;
                        break;
                    }
                }

                if (!safe && corner_n && corner_s) {
                    score += 1000;
                }
            }
        }
    }

    return score;
}

queue <_t_state> gen_valid_states(const _t_state &cur_state) {
    queue <_t_state> valid_moves;

    vector <vector<char> > new_level_map;
    _t_state new_state;

    stringstream ss(cur_state.state_str);
    string line;

    bool found = false;
    char box_move;
    _t_player player;
    int row = 0;

    vector <vector<char> > level_map;
    while (getline(ss, line, '\n')) {
        vector<char> temp;
        level_map.push_back(temp);

        int lineLength = line.length();
        for (int col = 0; col < lineLength; ++col) {
            if (!found) {
                if (line[col] == '@' | line[col] == '+') {
                    player.state = line[col];
                    player.x = col;
                    player.y = row;
                    found = true;
                }
            }
            level_map[row].push_back(line[col]);
        }
        row++;
    }

    if (!found) return valid_moves;

    _t_moves moves[4] = {
            {"u", -1, 0},
            {"d", 1,  0},
            {"l", 0,  -1},
            {"r", 0,  1},
    };

    for (_t_moves move : moves) {
        char next = level_map[player.y + move.y][player.x + move.x];

        if (next == '#') continue;

        new_level_map = level_map;
        new_level_map[player.y + move.y][player.x + move.x] = '@';
        new_level_map[player.y][player.x] = (player.state == '@') ? ' ' : '.';

        if (next == '$' ||
            next == '*') {
            box_move = new_level_map[player.y + move.y * 2][player.x + move.x * 2];

            if (box_move == '#' ||
                box_move == '$' ||
                box_move == '*') {
                continue;
            } else if (box_move == ' ' ||
                       box_move == '.') {
                new_level_map[player.y + move.y * 2][player.x + move.x * 2] = box_move == ' ' ?
                                                                              '$' : '*';
            } else {
                break;
            }
        }

        new_state = cur_state;
        new_state.state_str = "";
        int new_level_map_size = new_level_map.size();
        for (int i = 0; i < new_level_map_size; ++i) {
            vector<char> temp = new_level_map[i];;

            for (vector<char>::iterator itr = temp.begin();
                 itr != temp.end(); itr++) {
                new_state.state_str.push_back(*itr);
            }
            new_state.state_str.append("\n");
        }

        new_state.move_list.append(move.log);

        if (next == '$' ||
            next == '*') {
            new_state.pushes++;
            new_state.total_cost += PUSH_COST;
        } else {
            new_state.moves++;
            new_state.total_cost += MOVE_COST;
        }

        new_state.h_score = heuristics(new_state);
        new_state.h_score += new_state.total_cost;

        valid_moves.push(new_state);
    }

    return valid_moves;
}

#define MODE 2

_t_search_state a_start(_t_state &init_state) {
    deque <_t_state> open;

#if MODE == 1
    vector <_t_state> closed;
#elif MODE == 2
    set <std::string> closed;
#else
    map <string, bool> closed;
#endif

    _t_search_state report;
    report.rep_node_count = 0;
    report.fringe_node = 0;
    report.explored_count = 1;
    report.node_count = 1;
    report.node.state_str = "NULL";

    _t_state current_state;

    open.push_back(init_state);
    while (!open.empty()) {
        current_state = open.front();
        open.pop_front();

#if MODE == 1
        closed.push_back(current_state);
#elif MODE == 2
        closed.insert(current_state.state_str);
#else
        closed.insert(make_pair(current_state.state_str, true));
#endif

//        GOAL
        if ((current_state.state_str.find_first_of('.')) == string::npos &&
            (current_state.state_str.find_first_of('+')) == string::npos &&
            (current_state.state_str.find_first_of('$')) == string::npos) {
            report.node = current_state;
            report.explored_count = closed.size();
            open.pop_front();
            break;
        }

        queue <_t_state> valid_states = gen_valid_states(current_state);

        deque<_t_state>::iterator it;
        vector<_t_state>::iterator itr;

        while (!valid_states.empty()) {
            bool already_seen = false;
            bool inserted = false;

            _t_state temp_state = valid_states.front();

            for (it = open.begin(); it != open.end(); it++) {
                if (it->state_str == temp_state.state_str) {
                    already_seen = true;
                    break;
                }
            }

#if MODE == 1
            for (itr = closed.begin(); itr != closed.end(); itr++) {
                if (itr->state_str == temp_state.state_str) {
                    already_seen = true;
                    break;
                }
            }
#elif MODE == 2
            if (closed.find(temp_state.state_str) != closed.end()) {
                already_seen = true;
            }
#else
            if (closed.find(temp_state.state_str) != closed.end()) {
                already_seen = true;
            }
#endif

            if (!already_seen) {
                report.node_count++;

                for (it = open.begin(); it != open.end(); it++) {
                    if (it->h_score > temp_state.h_score) {
                        open.insert(it, temp_state);
                        inserted = true;
                        break;
                    }
                }

                if (!inserted) open.push_back(temp_state);
            } else {
                report.rep_node_count++;
            }
            valid_states.pop();
        }
    }

    report.fringe_node = open.size();

    return report;
}

void auto_mode_game(void) {
    Game g;

    int level = 2;

    g.setMap(level);
    g.newGame(g.getMap());
    g.push_step();

//    Init state
    _t_state init_state;
    init_state.state_str = g.getStrMap();
    init_state.move_list = "";
    init_state.moves = init_state.pushes =
    init_state.total_cost = init_state.h_score = 0;

//    cout << init_state.state_str << endl;
//    cout << endl;

    timeval start, end;
    long sec, microsec;

    gettimeofday(&start, NULL);
    _t_search_state final_stat = a_start(init_state);
    gettimeofday(&end, NULL);

////    //substring used to remove ending ', ' in string
    std::cout << "  Solution: " << std::endl;
    std::cout << "    "
              << final_stat.node.move_list.substr(0, (final_stat.node.move_list.size()))
              << std::endl;
//    std::cout << "    # of nodes generated: ";
//    std::cout << final_stat.node_count << std::endl;
//    std::cout << "    # of duplicate states generated: ";
//    std::cout << final_stat.rep_node_count << std::endl;
//    std::cout << "    # of fringe nodes when termination occured: ";
//    std::cout << final_stat.fringe_node << std::endl;
//    std::cout << "    # of explored nodes: ";
//    std::cout << final_stat.explored_count << std::endl;
//    //report search algorithm runtime
    std::cout << "  Actual run time: ";
    sec = end.tv_sec - start.tv_sec;
    microsec = end.tv_usec - start.tv_usec;
    std::cout << (sec + (microsec / 1000000.0)) << " seconds" << std::endl;

    int pos = 0;
    int prev = 0;
    int length = final_stat.node.move_list.size();

//    cout << final_stat.node.move_list.size() << endl;

    // bool checkF1 = false;
    while (true) {
        int inputKey = getch();

        if (inputKey == 'q') {
            return;
        }

        prev = pos;

        if (0 <= pos && pos < length) {
            if (inputKey == KEY_RIGHT) {
                pos++;
            }
        }

        char command = final_stat.node.move_list[prev];

        switch (command) {
            case 'u':
                g.moveUP(g.getMap());
                break;
            case 'd':
                g.moveDOWN(g.getMap());
                break;
            case 'l':
                g.moveLEFT(g.getMap());
                break;
            case 'r':
                g.moveRIGHT(g.getMap());
                break;
            default:
                break;
        }

//        if (g.finishGame()) {
//            break;
//        }
    }

}