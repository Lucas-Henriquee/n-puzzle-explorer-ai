#include "board_utils.hpp"
#include "../include/defines.hpp"
#include "../include/state.hpp"

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

bool is_ancestor(State *parent, const vector<size_t> &board)
{
    // Verifica se o estado atual é um ancestral de algum estado na árvore
    while (parent != nullptr)
    {
        for (size_t i = 0; i < board.size(); ++i)
        {
            if (parent->get_board().real_board[i] != board[i])
                break; // Se algum elemento não bate, não é um ancestral
            if (i == board.size() - 1)
                return true; // Se todos os elementos baterem, é um ancestral
        }
        parent = parent->get_parent(); // Avança para o pai do estado atual
    }
    return false; // Nenhum ancestral corresponde ao estado atual
}

size_t calculateMaxDepth(size_t n, size_t m)
{
    size_t size = n * m;
    size_t base = size - 1;
    size_t max_depth = (((base * 5) + 9) / 10) * 10;
    return max_depth;
}