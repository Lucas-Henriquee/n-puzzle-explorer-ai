#pragma once

#include "../include/defines.hpp"

struct VectorHash
{
    size_t operator()(const vector<size_t> &vec) const;
};