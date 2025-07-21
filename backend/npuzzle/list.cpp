#include "../include/list.hpp"
#include "../include/defines.hpp"

void List::add(State *state)
{
    if (head == nullptr)
    {
        head = state;  // Se a lista estiver vazia, o novo estado é o primeiro
        tail = state;  // O novo estado também é o último
        lower = state; // O novo estado é o de menor custo
        lower_heuristic = state; // O novo estado é o de menor heurística
    }

    else
    {
        tail->set_next(state); // Define o próximo do último estado como o novo estado
        state->set_prev(tail); // Define o anterior do novo estado como o último
        tail = state;          // Atualiza o último estado para o novo estado
        if (state->get_heuristic_value() < lower_heuristic->get_heuristic_value())
        {
            lower_heuristic = state; // Se o novo estado tem heurística menor, atualiza a menor heurística
        }
        if (state->get_total_cost() < lower->get_total_cost())
        {
            lower = state; // Se o novo estado tem custo menor, atualiza o menor custo
        }
    }

    size++; // Incrementa o tamanho da lista
}

void List::remove(State *state)
{
    if (state == nullptr)
        return; // Se o estado for nulo, não faz nada

    if (state == head)
    {
        head = state->get_next(); // Atualiza o primeiro elemento

        if (head != nullptr)
        {
            head->set_prev(nullptr); // Se houver um novo primeiro elemento, atualiza seu anterior
        }

        else
        {
            tail = nullptr; // Se a lista ficar vazia, atualiza o último elemento
        }
    }

    else if (state == tail)
    {
        tail = state->get_prev(); // Atualiza o último elemento

        if (tail != nullptr)
        {
            tail->set_next(nullptr); // Se houver um novo último elemento, atualiza seu próximo
        }

        else
        {
            head = nullptr; // Se a lista ficar vazia, atualiza o primeiro elemento
        }
    }

    else
    {
        State *prev_state = state->get_prev();
        State *next_state = state->get_next();

        prev_state->set_next(next_state); // Atualiza o próximo do estado anterior

        if (next_state != nullptr)
        {
            next_state->set_prev(prev_state); // Atualiza o anterior do estado seguinte
        }
    }
    if(use_cost){
        if (state == lower)
        {
            // Se o estado removido for o de menor custo, precisamos encontrar um novo menor custo
            lower = head; // Começa do início da lista
            State *current = head;

            while (current != nullptr)
            {
                if (current->get_cost() < lower->get_cost())
                {
                    lower = current; // Atualiza o menor custo se encontrar um estado com custo menor
                }
                current = current->get_next(); // Avança para o próximo estado
            }
        }
        if (state == lower_heuristic)
        {
            // Se o estado removido for o de menor heurística, precisamos encontrar um novo menor heurística
            lower_heuristic = head; // Começa do início da lista
            State *current = head;

            while (current != nullptr)
            {
                if (current->get_heuristic_value() < lower_heuristic->get_heuristic_value())
                {
                    lower_heuristic = current; // Atualiza a menor heurística se encontrar um estado com heurística menor
                }
                current = current->get_next(); // Avança para o próximo estado
            }
        }
    }
    size--; // Decrementa o tamanho da lista
}

List::~List()
{
    State *current = head;

    while (current)
    {
        State *next = current->get_next();
        delete current;
        current = next;
    }
}