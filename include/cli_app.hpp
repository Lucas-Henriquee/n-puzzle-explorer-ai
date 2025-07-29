#pragma once

#include <string>
#include <vector>
#include "board.hpp"

bool loadBoardFromFile(const string &filename, size_t &n, size_t &m, vector<size_t> &initial, vector<size_t> &goal, size_t &empty_column, size_t &empty_row);

int runCliApp(int argc, char *argv[]);