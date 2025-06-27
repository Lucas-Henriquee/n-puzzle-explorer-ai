#ifndef BOARD_HPP
#define BOARD_HPP

#include "../include/defines.hpp"

class Board
{
private:
    size_t empty_space_row;    // Linha do espaço vazio
    size_t empty_space_column; // Coluna do espaço vazio
    size_t columns_size;       // Tamanho da coluna
    size_t rows_size;          // Tamanho da linha

    void read_goal_board(); // Método para ler o tabuleiro objetivo
    void read_real_board(); // Método para ler o tabuleiro real

public:
    Board(size_t rows, size_t columns);
    ~Board();

    void print_board(const vector<vector<size_t>> &b) const; // Método para imprimir o tabuleiro
    bool move(char direction);                               // Método para mover o espaço vazio no tabuleiro
    void start_interactive_session();                        // Método para interação manual do jogo
    bool end_game() const;                                   // Método para verificar se o jogo terminou

    vector<vector<size_t>> real_board; // Representa o tabuleiro real
    vector<vector<size_t>> goal_board; // Representa o tabuleiro objetivo
};

#endif // BOARD_HPP