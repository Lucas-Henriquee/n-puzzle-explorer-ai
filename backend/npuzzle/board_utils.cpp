#include "board_utils.hpp"
#include "../include/defines.hpp"

// Função de Hash
size_t VectorHash::operator()(const vector<size_t> &vec) const
{
    size_t seed = vec.size();
    for (auto val : vec)
    {
        seed ^= std::hash<size_t>{}(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}