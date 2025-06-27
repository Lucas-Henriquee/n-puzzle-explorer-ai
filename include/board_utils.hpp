#ifndef BOARD_UTILS_HPP
#define BOARD_UTILS_HPP

#include "../include/defines.hpp"

struct VectorHash
{
    size_t operator()(const vector<size_t> &vec) const;
};

vector<size_t> flatten_board(const vector<vector<size_t>> &board);

#endif // BOARD_UTILS_HPP