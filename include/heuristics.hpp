#pragma once

#include "board.hpp"
double heuristic(const Board &board, const int &heuristic_choice);

double misplaced_tiles(const Board &board);
double euclidean(const Board &board);
double manhattan(const Board &board);
double linear_conflict(const Board &board);
double permutation_cycles(const Board &board);
double weighted_sum(const Board &board);
