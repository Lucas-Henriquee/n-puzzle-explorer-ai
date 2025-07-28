#pragma once

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
    Board(){};
    Board(size_t rows, size_t columns);
    Board(size_t rows, size_t columns, vector<size_t> real_board, vector<size_t> goal_board, size_t empty_row, size_t empty_column);
    ~Board();

    void print_board(const vector<size_t> &flat_board) const; // Método para imprimir o tabuleiro
    bool move(char direction);                                // Método para mover o espaço vazio no tabuleiro
    void start_interactive_session();                         // Método para interação manual do jogo
    bool end_game() const;                                    // Método para verificar se o jogo terminou
    size_t index(size_t i, size_t j) const;                   // Método para obter o índice linear de uma posição no tabuleiro

    vector<size_t> real_board; // Tabuleiro real do jogo
    vector<size_t> goal_board; // Tabuleiro objetivo do jogo

    size_t get_rows() const { return rows_size; }    // Método para obter o número de linhas do tabuleiro
    size_t get_cols() const { return columns_size; } // Método para obter o número de colunas do tabuleiro
};