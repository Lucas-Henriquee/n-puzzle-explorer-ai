#include "../include/defines.hpp"
#include "../include/board.hpp"

Board::Board(size_t rows, size_t columns)
    : columns_size(columns), rows_size(rows)
{
    srand(static_cast<unsigned int>(time(0)));

    real_board.resize(rows_size * columns_size);
    goal_board.resize(rows_size * columns_size);
    
    read_goal_board();
    read_real_board();
}

Board::~Board()
{
}

size_t Board::index(size_t i, size_t j) const
{
    return i * columns_size + j;
}

void Board::read_goal_board()
{
    cout << "Deseja inserir o tabuleiro objetivo? (s/n): ";
    char choice;
    cin >> choice;

    if (choice != 's' && choice != 'S')
    {
        for (size_t i = 0; i < rows_size; ++i)
        {
            cout << "Linha " << i + 1 << ": ";
            for (size_t j = 0; j < columns_size; ++j)
            {
                size_t idx = index(i, j);
                if (i == rows_size - 1 && j == columns_size - 1)
                {
                    goal_board[idx] = 0;
                    cout << "0 ";
                }
                else
                {
                    goal_board[idx] = idx + 1;
                    cout << goal_board[idx] << " ";
                }
            }
            cout << endl;
        }
        return;
    }

    cout << "Digite o tabuleiro objetivo (linha por linha, use 0 para o espaço vazio):" << endl;
    for (size_t i = 0; i < rows_size; ++i)
    {
        for (size_t j = 0; j < columns_size; ++j)
        {
            size_t idx = index(i, j);
            cin >> goal_board[idx];
        }
    }
}

void Board::read_real_board()
{
    cout << "Deseja inserir o tabuleiro real? (s/n): ";
    char choice;
    cin >> choice;

    if (choice != 's' && choice != 'S')
    {
        vector<size_t> numbers(rows_size * columns_size);
        for (size_t i = 0; i < numbers.size(); ++i)
            numbers[i] = i;

        for (size_t i = 0; i < numbers.size(); ++i)
        {
            size_t j = rand() % numbers.size();
            swap(numbers[i], numbers[j]);
        }

        for (size_t i = 0; i < rows_size; ++i)
        {
            for (size_t j = 0; j < columns_size; ++j)
            {
                size_t idx = index(i, j);
                real_board[idx] = numbers[idx];

                if (real_board[idx] == 0)
                {
                    empty_space_row = i;
                    empty_space_column = j;
                }
            }
        }
    }
    else
    {
        cout << "Digite o tabuleiro real (linha por linha, use 0 para o espaço vazio):" << endl;
        for (size_t i = 0; i < rows_size; ++i)
        {
            for (size_t j = 0; j < columns_size; ++j)
            {
                size_t idx = index(i, j);
                cin >> real_board[idx];
                if (real_board[idx] == 0)
                {
                    empty_space_row = i;
                    empty_space_column = j;
                }
            }
        }
    }

    print_board(real_board);
}

bool Board::end_game() const
{
    return real_board == goal_board;
}

void Board::print_board(const vector<size_t> &flat_board) const
{
    for (size_t i = 0; i < rows_size; ++i)
    {
        for (size_t j = 0; j < columns_size; ++j)
        {
            cout << flat_board[index(i, j)] << " ";
        }
        cout << endl;
    }
}

bool Board::move(char direction)
{
    size_t index_current = index(empty_space_row, empty_space_column);
    size_t index_target;

    switch (direction)
    {
    case 'L':
    case 'l':
        if (empty_space_column == 0)
            return false;
        index_target = index(empty_space_row, empty_space_column - 1);
        empty_space_column--;
        break;

    case 'R':
    case 'r':
        if (empty_space_column >= columns_size - 1)
            return false;
        index_target = index(empty_space_row, empty_space_column + 1);
        empty_space_column++;
        break;

    case 'U':
    case 'u':
        if (empty_space_row == 0)
            return false;
        index_target = index(empty_space_row - 1, empty_space_column);
        empty_space_row--;
        break;

    case 'D':
    case 'd':
        if (empty_space_row >= rows_size - 1)
            return false;
        index_target = index(empty_space_row + 1, empty_space_column);
        empty_space_row++;
        break;

    default:
        return false;
    }

    swap(real_board[index_current], real_board[index_target]);
    return true;
}

void Board::start_interactive_session()
{
    while (true)
    {
        cout << "Tabuleiro real:" << endl;
        print_board(real_board);
        cout << "Digite a direção do movimento (u/d/l/r): ";
        char direction;
        cin >> direction;

        if (move(direction))
        {
            cout << "Movimento realizado com sucesso!" << endl;
        }

        if (end_game())
        {
            cout << "Parabéns! Você alcançou o tabuleiro objetivo!" << endl;
            break;
        }
    }
}