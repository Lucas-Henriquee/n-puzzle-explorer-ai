#include "../include/board.hpp"
#include "../include/heuristics.hpp"
#include "../include/defines.hpp"

double heuristic(const Board &board, const int &heuristic_choice)
{
    switch (heuristic_choice)
    {
    case 1:
        return manhattan(board);
    case 2:
        return euclidean(board);
    case 3:
        return misplaced_tiles(board);
    case 4:
        return linear_conflict(board);
    case 5:
        return permutation_cycles(board);
    case 6:
        return weighted_sum(board);
    default:
        cerr << "Heuristic not recognized: " << heuristic_choice << endl;
        return -1; // Indica erro
    }
}

double manhattan(const Board &board)
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

double euclidean(const Board &board)
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
                if (i < goal_row)
                {
                    dx = static_cast<double>(goal_row - i);
                }
                else
                {
                    dx = static_cast<double>(i - goal_row);
                }
                if (j < goal_col)
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

double misplaced_tiles(const Board &board)
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

double linear_conflict(const Board &board)
{
    size_t rows = board.get_rows();
    size_t cols = board.get_cols();
    int linear_conflict = 0;

    // Conflitos em linhas
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j1 = 0; j1 < cols; ++j1)
        {
            size_t tile1 = board.real_board[board.index(i, j1)];
            if (tile1 == 0) continue;

            size_t goal_idx1 = find(board.goal_board.begin(), board.goal_board.end(), tile1) - board.goal_board.begin();
            size_t goal_row1 = goal_idx1 / cols;
            size_t goal_col1 = goal_idx1 % cols;

            if (goal_row1 != i) continue;

            for (size_t j2 = j1 + 1; j2 < cols; ++j2)
            {
                size_t tile2 = board.real_board[board.index(i, j2)];
                if (tile2 == 0) continue;

                size_t goal_idx2 = find(board.goal_board.begin(), board.goal_board.end(), tile2) - board.goal_board.begin();
                size_t goal_row2 = goal_idx2 / cols;
                size_t goal_col2 = goal_idx2 % cols;

                if (goal_row2 != i) continue;

                if (goal_col1 > goal_col2)
                {
                    ++linear_conflict;
                }
            }
        }
    }

    // Conflitos em colunas
    for (size_t j = 0; j < cols; ++j)
    {
        for (size_t i1 = 0; i1 < rows; ++i1)
        {
            size_t tile1 = board.real_board[board.index(i1, j)];
            if (tile1 == 0) continue;

            size_t goal_idx1 = find(board.goal_board.begin(), board.goal_board.end(), tile1) - board.goal_board.begin();
            size_t goal_row1 = goal_idx1 / cols;
            size_t goal_col1 = goal_idx1 % cols;

            if (goal_col1 != j) continue;

            for (size_t i2 = i1 + 1; i2 < rows; ++i2)
            {
                size_t tile2 = board.real_board[board.index(i2, j)];
                if (tile2 == 0) continue;

                size_t goal_idx2 = find(board.goal_board.begin(), board.goal_board.end(), tile2) - board.goal_board.begin();
                size_t goal_row2 = goal_idx2 / cols;
                size_t goal_col2 = goal_idx2 % cols;

                if (goal_col2 != j) continue;

                if (goal_row1 > goal_row2)
                {
                    ++linear_conflict;
                }
            }
        }
    }

    return manhattan(board) + 2 * linear_conflict;
}

double permutation_cycles(const Board &board) {
    std::unordered_map<int, int> goal_position;
    for (size_t i = 0; i < board.goal_board.size(); ++i) {
        if (board.goal_board[i] != 0)  // Ignora o espaço vazio
            goal_position[board.goal_board[i]] = i;
    }

    std::vector<bool> visited(board.real_board.size(), false);
    double cycles = 0;

    for (size_t i = 0; i < board.real_board.size(); ++i) {
        if (visited[i] || board.real_board[i] == 0 || board.real_board[i] == board.goal_board[i])
            continue;

        size_t j = i;
        while (!visited[j] && board.real_board[j] != 0) {
            visited[j] = true;
            j = goal_position[board.real_board[j]];
        }
        ++cycles;
    }

    return 0.8 * cycles + 0.2 * manhattan(board);
}

double weighted_sum(const Board &board)
{
    return 0.6 * manhattan(board) + 0.4 * misplaced_tiles(board);
}