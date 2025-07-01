#pragma once

#include "../include/defines.hpp"
#include "../include/state.hpp"

struct SearchStatistics
{
    bool solution_found = false;
    size_t solution_cost = 0;
    size_t solution_depth = 0;
    size_t nodes_expanded = 0;
    size_t nodes_visited = 0;
    size_t total_branching = 0;
    double avg_branching_factor = 0.0;
    double elapsed_time = 0.0;
    string algorithm_name;
    string heuristic_name;
    vector<State *> solution_path;
    vector<State *> closed_list;
};

void print_solution_path(const vector<State *> &path);
void print_closed_list(const vector<State *> &closed_list);
void print_statistics(const SearchStatistics &stats);