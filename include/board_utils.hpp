#pragma once

#include "../include/defines.hpp"
#include "../include/state.hpp"

struct VectorHash
{
    size_t operator()(const vector<size_t> &vec) const;
};

bool is_ancestor(State *parent, const vector<size_t> &board);