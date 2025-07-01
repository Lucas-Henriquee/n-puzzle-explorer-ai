#pragma once

#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"

bool backtrack_iterative(State *initialState, size_t &id, size_t &nodes_expanded, size_t &nodes_visited, size_t &total_branching, unordered_set<vector<size_t>, VectorHash> &visited, vector<State *> &solution_path);
void BacktrackingSearch(Board initialBoard);
bool is_ancestor(State *node, const vector<size_t> &candidate_board);