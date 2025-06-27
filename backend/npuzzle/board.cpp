#include "../include/defines.hpp"
#include "../include/board.hpp"

Board::Board(size_t rows, size_t columns)
    : columns_size(columns), rows_size(rows)

{
    srand(static_cast<unsigned int>(time(0)));

    real_board.resize(rows_size, vector<size_t>(columns_size, 0));
    goal_board.resize(rows_size, vector<size_t>(columns_size, 0));

    read_goal_board();
    read_real_board();
}

Board::~Board()
{
}

void Board::read_goal_board()
{
    cout << "Deseja inserir o tabuleiro objetivo? (s/n): ";
    char choice;
    cin >> choice;

    if (choice != 's' && choice != 'S')
    {
        // Preenche o tabuleiro objetivo com valores padrão
        for (size_t i = 0; i < rows_size; ++i)
        {
            cout << "Linha " << i + 1 << ": ";
            for (size_t j = 0; j < columns_size; ++j)
            {
                if (i == rows_size - 1 && j == columns_size - 1)
                {
                    cout << "0 "; // Espaço vazio
                    goal_board[i][j] = 0;
                    continue;
                }
                cout << (i * columns_size + j + 1) << " ";
                goal_board[i][j] = i * columns_size + j + 1;
            }
            cout << endl;
        }
        return;
    }

    else
        cout << "Digite o tabuleiro objetivo (linha por linha, use 0 para o espaço vazio):" << endl;

    for (size_t i = 0; i < rows_size; ++i)
    {
        for (size_t j = 0; j < columns_size; ++j)
        {
            cin >> goal_board[i][j];
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
        // Preenche o tabuleiro real com valores aleatórios
        vector<size_t> numbers;

        for (size_t i = 0; i < rows_size * columns_size; ++i)
        {
            numbers.push_back(i);
        }

        for (size_t i = 0; i < rows_size * columns_size; ++i)
        {
            size_t j = rand() % (rows_size * columns_size);
            swap(numbers[i], numbers[j]);
        }

        for (size_t i = 0; i < rows_size; ++i)
        {
            for (size_t j = 0; j < columns_size; ++j)
            {
                if (numbers[i * columns_size + j] == 0)
                {
                    empty_space_row = i;
                    empty_space_column = j;
                }
                real_board[i][j] = numbers[i * columns_size + j];
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
                if (i == rows_size - 1 && j == columns_size - 1)
                {
                    real_board[i][j] = 0;
                    empty_space_row = i;
                    empty_space_column = j;
                    continue;
                }
                cin >> real_board[i][j];
            }
        }
    }
}

bool Board::end_game() const
{
    return real_board == goal_board;
}

void Board::print_board(const vector<vector<size_t>> &b) const
{
    for (const auto &row : b)
    {
        for (const auto &cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool Board::move(char direction)
{
    switch (direction)
    {
    case 'u':
    case 'U':

        if (empty_space_row == 0)
        {
            cout << "Movimento inválido! O espaço vazio já está na parte superior." << endl;
            return false;
        }

        swap(real_board[empty_space_row][empty_space_column], real_board[empty_space_row - 1][empty_space_column]);
        empty_space_row--;
        break;

    case 'd':
    case 'D':

        if (empty_space_row == rows_size - 1)
        {
            cout << "Movimento inválido! O espaço vazio já está na parte inferior." << endl;
            return false;
        }

        swap(real_board[empty_space_row][empty_space_column], real_board[empty_space_row + 1][empty_space_column]);
        empty_space_row++;
        break;

    case 'l':
    case 'L':

        if (empty_space_column == 0)
        {
            cout << "Movimento inválido! O espaço vazio já está na parte esquerda." << endl;
            return false;
        }

        swap(real_board[empty_space_row][empty_space_column], real_board[empty_space_row][empty_space_column - 1]);
        empty_space_column--;
        break;

    case 'r':
    case 'R':

        if (empty_space_column == columns_size - 1)
        {
            cout << "Movimento inválido! O espaço vazio já está na parte direita." << endl;
            return false;
        }

        swap(real_board[empty_space_row][empty_space_column], real_board[empty_space_row][empty_space_column + 1]);
        empty_space_column++;
        break;

    default:
        cout << "Direção inválida!" << endl;
        return false;
    }
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