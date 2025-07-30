#pragma once

#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/statistics.hpp"

SearchStatistics GreedySearch(Board board, const int &heuristic_choice);