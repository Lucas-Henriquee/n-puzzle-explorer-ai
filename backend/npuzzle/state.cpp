// Estrutura de nós
#include <iostream>
#include "board.cpp" // Inclui o cabeçalho do estado

using namespace std;

class State {
    private:
        size_t id; // Identificador do estado
        size_t cost; // Custo do estado
        size_t depth; // Profundidade do estado
        Board board; // Tabuleiro associado ao estado
        State* parent; // Ponteiro para o estado pai
        State* next; // Ponteiro para o próximo estado na lista
        State* prev; // Ponteiro para o estado anterior na lista
    public:
        State(size_t id, size_t cost, size_t depth, State* parent = nullptr, Board board)
            : id(id), cost(cost), depth(depth), parent(parent), next(nullptr), prev(nullptr), board(board) {}

        size_t get_id() const { return id; } // Método para obter o ID do estado
        size_t get_cost() const { return cost; } // Método para obter o custo do estado
        size_t get_depth() const { return depth; } // Método para obter a profundidade do estado
        State* get_parent() const { return parent; } // Método para obter o estado pai
        State* get_next() const { return next; } // Método para obter o próximo estado
        State* get_prev() const { return prev; } // Método para obter o estado anterior
        Board get_board() const { return board; } // Método para obter o tabuleiro associado ao estado

        void set_next(State* next_state) { next = next_state; } // Método para definir o próximo estado
        void set_prev(State* prev_state) { prev = prev_state; } // Método para definir o estado anterior
};