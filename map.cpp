#include <fstream>
#include <iostream>
#include <stdarg.h>
#include <sstream>
#include <string>
#include "map.h"

using namespace std;

std::string format_string(const std::string fmt, ...) {
    int size = ((int) fmt.size()) * 2;
    std::string buffer;
    va_list ap;
    while (1) {
        buffer.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *) buffer.data(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {
            buffer.resize(n);
            return buffer;
        }
        if (n > -1) size = n + 1; else size *= 2;
    }
    return buffer;
}

void mapArray::set_map(int map_arr[][10], int level, int &a, int &b, int &goalCount) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            map_arr[i][j] = 0;
        }
    }

    ifstream input;
    string line;
    std::string filename = format_string("./mapFile/level%d.txt", level);
    input.open(filename);

    getline(input, line);
    istringstream is(line);
    is >> a >> b;
    a += 1;
    b += 3;

    goalCount = 0;
    for (int r = 0; getline(input, line); r++) {
        istringstream is(line);
        int n;

        int c = 0;
        while (is >> n) {
            map_arr[r][c++] = n;
            goalCount += n == 3;
        }
    }
}

