#ifndef BACKTRACKING_HPP
#define BACKTRACKING_HPP

#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/state.hpp"

bool backtrack(State *currentState, size_t &id, std::chrono::steady_clock::time_point start_time);
void BacktrackingSearch(Board initialBoard);

#endif // BACKTRACKING_HPP