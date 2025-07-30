#pragma once

#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/statistics.hpp"

SearchStatistics AStarSearch(Board board, const int &heuristic_choice);