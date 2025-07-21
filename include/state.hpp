#pragma once

#include "../include/defines.hpp"
#include "board.hpp"

class State
{
private:
    size_t id;     // Identificador do estado
    double cost;   // Custo do estado
    double heuristic_value; // Valor da heurística do estado
    size_t depth;  // Profundidade do estado
    Board board;   // Tabuleiro associado ao estado
    State *parent; // Ponteiro para o estado pai
    State *next;   // Ponteiro para o próximo estado na lista
    State *prev;   // Ponteiro para o estado anterior na lista
public:
    State(size_t id, double cost, double heuristic_value, size_t depth, State *parent = nullptr, Board board = Board(3, 3))
        : id(id), cost(cost), heuristic_value(heuristic_value), depth(depth), board(board), parent(parent), next(nullptr), prev(nullptr) {}

    size_t get_id() const { return id; }             // Método para obter o ID do estado
    double get_cost() const { return cost; }         // Método para obter o custo do estado
    double get_heuristic_value() const { return heuristic_value; } // Método para obter o valor da heurística do estado
    double get_total_cost() const { return cost + heuristic_value; } // Método para obter o custo total (custo + heurística)
    size_t get_depth() const { return depth; }       // Método para obter a profundidade do estado
    State *get_parent() const { return parent; }     // Método para obter o estado pai
    State *get_next() const { return next; }         // Método para obter o próximo estado
    State *get_prev() const { return prev; }         // Método para obter o estado anterior
    const Board &get_board() const { return board; } // Método para obter o tabuleiro associado ao estado

    void set_next(State *next_state) { next = next_state; } // Método para definir o próximo estado
    void set_prev(State *prev_state) { prev = prev_state; } // Método para definir o estado anterior
};