#ifndef BACKTRACKING_HPP
#define BACKTRACKING_HPP

#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"

bool backtrack(State *currentState, size_t &id, size_t &nodes_expanded, size_t &nodes_visited, size_t &total_branching, unordered_set<vector<size_t>, VectorHash> &visited, vector<State *> &solution_path, chrono::steady_clock::time_point start_time);
void BacktrackingSearch(Board initialBoard);

#endif // BACKTRACKING_HPP