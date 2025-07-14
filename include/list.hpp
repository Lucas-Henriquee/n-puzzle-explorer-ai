#pragma once

#include "../include/defines.hpp"
#include "state.hpp"

class List
{
private:
    size_t size;  // Tamanho da lista
    State *head;  // Ponteiro para o primeiro elemento da lista
    State *tail;  // Ponteiro para o último elemento da lista
    State *lower; // Ponteiro para o estado com o menor custo na lista
    bool use_cost; // Flag para indicar se a lista deve usar custo para ordenação
public:
    List(bool use_cost) : size(0), head(nullptr), tail(nullptr), lower(nullptr), use_cost(use_cost) {}
    ~List();

    size_t get_size() const { return size; }        // Método para obter o tamanho da lista
    State *get_head() const { return head; }        // Método para obter o primeiro elemento da lista
    State *get_tail() const { return tail; }        // Método para obter o último elemento
    State *get_lower_cost() const { return lower; } // Método para obter o estado com o menor custo na lista

    bool is_not_empty() const { return size > 0; } // Método para verificar se a lista não está vazia
    void add(State *state);                        // Método para adicionar um estado à lista
    void remove(State *state);                     // Método para remover um estado da lista
};