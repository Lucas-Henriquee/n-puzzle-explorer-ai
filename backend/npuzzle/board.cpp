// Representação do tabuleiro
#include <vector>
#include <iostream>
#include <cstdlib> // Para usar std::rand() e std::srand()
#include <ctime>   // Para usar std::time() para inicializar o gerador de números aleatórios

using namespace std;



class Board
{
private:
    size_t empty_space_row; // Linha do espaço vazio
    size_t empty_space_column; // Coluna do espaço vazio
    size_t columns_size; // Tamanho da coluna
    size_t rows_size; // Tamanho da linha
    void read_goal_board(); // Método para ler o tabuleiro objetivo
    void read_real_board(); // Método para ler o tabuleiro real
    bool end_game(); // Método para verificar se o jogo terminou
public:
    Board(size_t rows = 3, size_t columns = 3);
    ~Board();
    void print_board(vector<vector<size_t>>& b); // Método para imprimir o tabuleiro
    bool move(char direction); // Método para mover o espaço vazio no tabuleiro
    vector<vector<size_t>> real_board; // Representa o tabuleiro real
    vector<vector<size_t>> goal_board; // Representa o tabuleiro objetivo
};

bool Board::end_game()
{
    for (size_t i = 0; i < rows_size; ++i)
    {
        for (size_t j = 0; j < columns_size; ++j)
        {
            if (real_board[i][j] != goal_board[i][j])
            {
                return false; // O jogo não terminou
            }
        }
    }
    return true; // O jogo terminou
}

Board::Board(size_t rows, size_t columns)
    : rows_size(rows), columns_size(columns)
{
    srand(static_cast<unsigned int>(time(0))); // Inicializa o gerador de números aleatórios
    // Inicializa o tabuleiro real e o tabuleiro objetivo
    rows_size = 3; // Exemplo de tamanho de linha
    columns_size = 3; // Exemplo de tamanho de coluna
    real_board.resize(rows_size, vector<size_t>(columns_size, 0));
    goal_board.resize(rows_size, vector<size_t>(columns_size, 0));

    // Preenche o tabuleiro objetivo com o input do usuário
    read_goal_board();

    // Preenche o tabuleiro real com o input do usuário
    read_real_board();

    while (true)
    {
        cout << "Tabuleiro real:" << endl;
        print_board(real_board);
        cout << "Digite a direção do movimento (u/d/l/r): ";
        char direction;
        cin >> direction;

        if (move(direction)) {
            cout << "Movimento realizado com sucesso!" << endl;
        }

        // Verifica se o tabuleiro real é igual ao tabuleiro objetivo
        if (end_game()) {
            cout << "Parabéns! Você alcançou o tabuleiro objetivo!" << endl;
            break;
        }
    }
    
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
                if (i == rows_size - 1 && j == columns_size - 1) {
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
        // Preenche o tabuleiro real com valores aleatóros
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
                if(numbers[i * columns_size + j] == 0) {
                    empty_space_row = i; // Armazena a posição do espaço vazio
                    empty_space_column = j; // Armazena a posição do espaço vazio
                }
                real_board[i][j] = numbers[i * columns_size + j];
            }
        }
        
    }
    else{
        cout << "Digite o tabuleiro real (linha por linha, use 0 para o espaço vazio):" << endl;
        for (size_t i = 0; i < rows_size; ++i)
        {
            for (size_t j = 0; j < columns_size; ++j)
            {
                if( i == rows_size - 1 && j == columns_size - 1) {
                    real_board[i][j] = 0; // Espaço vazio
                    empty_space_row = i; // Armazena a posição do espaço vazio
                    empty_space_column = j; // Armazena a posição do espaço vazio
                    continue;
                }
                cin >> real_board[i][j];
            }
        }
    }
}

Board::~Board()
{
}


void Board::print_board(vector<vector<size_t>>& b) 
{
    for (const auto& row : b)
    {
        for (const auto& cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() 
{
    Board T = Board(); // Cria um tabuleiro 3x3
    cout << "Tabuleiro objetivo:" << endl;
    T.print_board(T.goal_board);
    cout << "Tabuleiro real:" << endl;
    T.print_board(T.real_board);
    return 0;
}

bool Board::move(char direction) 
{
    switch (direction)
    {
    case 'u':
    case 'U':
        if (empty_space_row == 0) {
            cout << "Movimento inválido! O espaço vazio já está na parte superior." << endl;
            return false;
        }
        swap(real_board[empty_space_row][empty_space_column], real_board[empty_space_row - 1][empty_space_column]);
        empty_space_row--; // Atualiza a posição do espaço vazio
        break;
    case 'd':
    case 'D':
        if (empty_space_row == rows_size - 1) {
            cout << "Movimento inválido! O espaço vazio já está na parte inferior." << endl;
            return false;
        }
        swap(real_board[empty_space_row][empty_space_column], real_board[empty_space_row + 1][empty_space_column]);
        empty_space_row++; // Atualiza a posição do espaço vazio
        break;
        
    case 'l':
    case 'L':
        if( empty_space_column == 0) {
            cout << "Movimento inválido! O espaço vazio já está na parte esquerda." << endl;
            return false;
        }
        swap(real_board[empty_space_row][empty_space_column], real_board[empty_space_row][empty_space_column - 1]);
        empty_space_column--; // Atualiza a posição do espaço vazio
        // Move o espaço vazio para a esquerda
        break;
        
    case 'r':
    case 'R':
        if (empty_space_column == columns_size - 1) {
            cout << "Movimento inválido! O espaço vazio já está na parte direita." << endl;
            return false;
        }
        swap(real_board[empty_space_row][empty_space_column], real_board[empty_space_row][empty_space_column + 1]);
        empty_space_column++; // Atualiza a posição do espaço vazio
        // Move o espaço vazio para a direita
        break;    
    default:
        cout << "Direção inválida!" << endl;
        return false;     
    }
    return true; // Movimento realizado com sucesso
}