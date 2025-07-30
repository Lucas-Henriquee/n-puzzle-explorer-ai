#pragma once

#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/board_utils.hpp"
#include "../include/state.hpp"
#include "../include/statistics.hpp"

double IDAStarSearch(Board board, const int &heuristic_choice, double baseline,
                     unordered_set<vector<size_t>, VectorHash> &visited,
                     vector<State *> &closedList, size_t &nodes_expanded, size_t &nodes_visited, size_t &total_branching, size_t &id,bool &found, State *parent);

SearchStatistics IDAStarter(Board board, const int &heuristic_choice);