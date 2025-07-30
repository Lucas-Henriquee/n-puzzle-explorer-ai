#pragma once

#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/statistics.hpp"

void BacktrackingSearch(Board board, unordered_set<vector<size_t>, VectorHash> &visited, vector<State *> &closedList, size_t &nodes_expanded, size_t &nodes_visited, size_t &total_branching, size_t &id, bool &found, State *parent);
SearchStatistics BacktrackingStarter(Board initialBoard);