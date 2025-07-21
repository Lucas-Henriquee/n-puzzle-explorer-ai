#pragma once

#include "board.hpp"
double calculate_heuristic(const Board &board, const int &heuristic_choice);
double calculate_misplaced_tiles(const Board &board);
double calculate_euclidean_distance(const Board &board);
