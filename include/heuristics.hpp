#pragma once

#include "board.hpp"
double calculate_heuristic(const Board &board, const string &heuristic_name);
double calculate_misplaced_tiles(const Board &board);