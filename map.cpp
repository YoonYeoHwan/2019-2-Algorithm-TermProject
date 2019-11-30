#include <fstream>
#include <iostream>
#include "string.h"
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
    ifstream input;
    std::string filename = format_string("./mapFile/level%d.txt", level);
    input.open(filename);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            input >> map_arr[i][j];
        }
    }
    input >> goalCount >> a >> b;
}

