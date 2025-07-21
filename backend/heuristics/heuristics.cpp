#include <iostream>
#include "../include/board.hpp"
#include "../include/heuristics.hpp"

using namespace std;
// Heurísticas usadas nos algoritmos

double calculate_heuristic(const Board &board, const int &heuristic_choice)
{
    if (heuristic_choice == 1)
    {
        // return calculate_manhattan_distance(board);
    }
    else if (heuristic_choice == 2)
    {
        return calculate_euclidean_distance(board);
    }
    else if (heuristic_choice == 3)
    {
        return calculate_misplaced_tiles(board);
    }
    else if (heuristic_choice == 4)
    {
        // return calculate_hamming_distance(board);
    }
    else if (heuristic_choice == 5)
    {
        // return calculate_linear_conflict(board);
    }
    else if (heuristic_choice == 6)
    {
        // return 0.0; // Heurística zero
    }
    else
    {
        cerr << "Heuristic not recognized: " << heuristic_choice << endl;
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

double calculate_euclidean_distance(const Board &board)
{
    double total_distance = 0.0;
    for (size_t i = 0; i < board.get_rows(); ++i)
    {
        for (size_t j = 0; j < board.get_cols(); ++j)
        {
            size_t value = board.real_board[board.index(i, j)];
            if (value != 0) // Ignora o espaço vazio
            {
                size_t goal_row = (value - 1) / board.get_cols();
                size_t goal_col = (value - 1) % board.get_cols();
                double dx = static_cast<double>(i - goal_row);
                double dy = static_cast<double>(j - goal_col);
                total_distance += sqrt(dx * dx + dy * dy);
            }
        }
    }
    return total_distance;
}