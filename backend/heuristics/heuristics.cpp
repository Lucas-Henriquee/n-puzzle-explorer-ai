#include <iostream>
#include "../include/board.hpp"
#include "../include/heuristics.hpp"
#include "../include/defines.hpp"

using namespace std;
// Heurísticas usadas nos algoritmos

double calculate_heuristic(const Board &board, const int &heuristic_choice)
{
    if (heuristic_choice == 1)
    {
        return calculate_manhattan_distance(board);
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
        return calculate_linear_conflict(board);
    }
    else if (heuristic_choice == 5)
    {
        return calculate_manhattan_inversions(board);
    }
    else if (heuristic_choice == 6)
    {
        // return calculate_weighted_sum(board);
    }
    else
    {
        cerr << "Heuristic not recognized: " << heuristic_choice << endl;
        return -1; // Indica erro
    }
    return -1; // Indica erro se nenhuma heurística for reconhecida
}

double calculate_manhattan_distance(const Board &board)
{
    double total_distance = 0.0;
    for (size_t i = 0; i < board.get_rows(); ++i)
    {
        for (size_t j = 0; j < board.get_cols(); ++j)
        {
            size_t value = board.real_board[board.index(i, j)];
            if (value != 0) // Ignora o espaço vazio
            {
                size_t goal_index = 0;

                for (size_t k = 0; k < board.goal_board.size(); ++k)
                {
                    if (board.goal_board[k] == value)
                    {
                        goal_index = k;
                        break;
                    }
                }

                size_t goal_row = goal_index / board.get_cols();
                size_t goal_col = goal_index % board.get_cols();

                if (i < goal_row)
                {
                    total_distance += static_cast<double>(goal_row - i);
                }
                else
                {
                    total_distance += static_cast<double>(i - goal_row);
                }
                if (j < goal_col)
                {
                    total_distance += static_cast<double>(goal_col - j);
                }
                else
                {
                    total_distance += static_cast<double>(j - goal_col);
                }
            }
        }
    }
    return total_distance;
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
                size_t goal_row = (find(board.goal_board.begin(), board.goal_board.end(), value) - board.goal_board.begin()) / board.get_cols();
                size_t goal_col = (find(board.goal_board.begin(), board.goal_board.end(), value) - board.goal_board.begin()) % board.get_cols();
                double dx, dy;
                if(i < goal_row)
                {
                    dx = static_cast<double>(goal_row - i);
                }
                else
                {
                    dx = static_cast<double>(i - goal_row);
                }
                if(j < goal_col)
                {
                    dy = static_cast<double>(goal_col - j);
                }
                else
                {
                    dy = static_cast<double>(j - goal_col);
                }
                total_distance += sqrt(pow(dx, 2) + pow(dy, 2));
            }
        }
    }
    return total_distance;
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

double calculate_linear_conflict(const Board &board)
{
    double manhattan_distance = calculate_manhattan_distance(board);
    size_t linear_conflict = 0;

    for (size_t i = 0; i < board.get_rows(); ++i)
    {
        for (size_t j = 0; j < board.get_cols(); ++j)
        {
            size_t value = board.real_board[board.index(i, j)];
            if (value != 0) // Ignora o espaço vazio
            {
                size_t goal_index = find(board.goal_board.begin(), board.goal_board.end(), value) - board.goal_board.begin();
                size_t goal_row = goal_index / board.get_cols();
                size_t goal_col = goal_index % board.get_cols();

                if (goal_row == i) // Verifica conflito na linha
                {
                    for (size_t k = j + 1; k < board.get_cols(); ++k)
                    {
                        size_t other_value = board.real_board[board.index(i, k)];
                        if (other_value != 0 && (find(board.goal_board.begin(), board.goal_board.end(), other_value) - board.goal_board.begin()) / board.get_cols() == i)
                        {
                            linear_conflict++;
                        }
                    }
                }

                if (goal_col == j) // Verifica conflito na coluna
                {
                    for (size_t k = i + 1; k < board.get_rows(); ++k)
                    {
                        size_t other_value = board.real_board[board.index(k, j)];
                        if (other_value != 0 && (find(board.goal_board.begin(), board.goal_board.end(), other_value) - board.goal_board.begin()) % board.get_cols() == j)
                        {
                            linear_conflict++;
                        }
                    }
                }
            }
        }
    }
    
}

double calculate_manhattan_inversions(const Board &board)
{
    double manhattan_distance = calculate_manhattan_distance(board);
    size_t inversions = 0;
    for (size_t i = 0; i < board.real_board.size(); ++i)
    {
        if (board.real_board[i] == 0) continue; // Ignora o espaço vazio
        for (size_t j = i + 1; j < board.real_board.size(); ++j)
        {
            if (board.real_board[j] == 0) continue; // Ignora o espaço vazio
            if (board.real_board[i] > board.real_board[j])
            {
                ++inversions;
            }
        }
    }
    return static_cast<double>(manhattan_distance + inversions);
}