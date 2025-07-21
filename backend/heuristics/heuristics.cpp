#include <iostream>
#include "../include/board.hpp"
#include "../include/heuristics.hpp"

using namespace std;
// Heurísticas usadas nos algoritmos

double calculate_heuristic(const Board &board, const string &heuristic_name)
{
    if (heuristic_name == "manhattan")
    {
        // return calculate_manhattan_distance(board);
    }
    else if (heuristic_name == "euclidean")
    {
        // return calculate_euclidean_distance(board);
    }
    else if (heuristic_name == "misplaced_tiles")
    {
        return calculate_misplaced_tiles(board);
    }
    else if (heuristic_name == "hamming")
    {
        // return calculate_hamming_distance(board);
    }
    else if (heuristic_name == "linear_conflict")
    {
        // return calculate_linear_conflict(board);
    }
    else if (heuristic_name == "zero")
    {
        // return 0.0; // Heurística zero
    }
    else
    {
        cerr << "Heuristic not recognized: " << heuristic_name << endl;
        return -1; // Indica erro
    }
    return -1; // Indica erro se nenhuma heurística for reconhecida
}

double calculate_misplaced_tiles(const Board &board)
{
    size_t misplaced_tiles = 0;
    for (size_t i = 0; i < board.get_rows(); ++i)
    {
        for (size_t j = 0; j < board.get_cols(); ++j)
        {
            if (board.real_board[board.index(i, j)] != 0 && board.real_board[board.index(i, j)] != board.goal_board[board.index(i, j)])
            {
                ++misplaced_tiles;
            }
        }
    }
    return static_cast<double>(misplaced_tiles);
}