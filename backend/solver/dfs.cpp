#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/list.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/dfs.hpp"
#include "../include/statistics.hpp"

// Implementação da Busca em Profundidade (DFS)
void DepthFirstSearch(Board initialBoard)
{
    size_t id = 0;              // Identificador único para cada estado
    size_t nodes_expanded = 0;  // Contador de nós expandidos
    size_t nodes_visited = 0;   // Contador de nós visitados
    size_t total_branching = 0; // Contador do total de ramificações

    unordered_set<vector<size_t>, VectorHash> visited; // Conjunto para armazenar estados já visitados
    unordered_set<vector<size_t>, VectorHash> closed;  // Conjunto para armazenar estados fechados

    List openList; // Lista para armazenar estados abertos

    auto start_time = chrono::steady_clock::now(); // Marca o tempo de início da busca

    // Cria o estado inicial com custo 0 e profundidade 0
    State *initialState = new State(id++, 0, 0, nullptr, initialBoard);
    openList.add(initialState); // Adiciona o estado inicial à lista aberta

    visited.insert(flatten_board(initialBoard.real_board)); // Armazena o estado inicial como visitado
    nodes_visited++;

    bool found = false;
    vector<State *> solution_path;

    while (openList.is_not_empty())
    {
        State *currentState = openList.get_tail();
        openList.remove(currentState);

        // Adiciona o estado atual ao conjunto de estados fechados
        closed.insert(flatten_board(currentState->get_board().real_board));

        nodes_expanded++; // Incrementa o número de nós expandidos

        // Verifica se o estado atual é o estado objetivo
        if (currentState->get_board().end_game())
        {
            found = true;

            // Reconstrução do caminho da solução
            for (State *s = currentState; s != nullptr; s = s->get_parent())
                solution_path.push_back(s);

            reverse(solution_path.begin(), solution_path.end());
            break;
        }

        size_t successors_this_node = 0; // Contador de sucessores deste nó

        // Tenta gerar sucessores em todas as direções possíveis
        for (char dir : {'U', 'D', 'L', 'R'})
        {
            Board newBoard = currentState->get_board(); // Cria uma cópia do tabuleiro atual

            // Tenta mover o espaço vazio na direção especificada
            if (newBoard.move(dir))
            {
                auto flat = flatten_board(newBoard.real_board); // Achata o tabuleiro para comparação

                // Verifica se o estado já foi visitado ou está fechado
                if (visited.count(flat) || closed.count(flat))
                    continue;

                visited.insert(flat); // Marca o novo estado como visitado
                nodes_visited++;      // Incrementa o número de nós visitados

                // Cria o novo estado sucessor
                State *successor = new State(id++, currentState->get_cost() + 1, currentState->get_depth() + 1, currentState, newBoard);

                openList.add(successor); // Adiciona o sucessor à lista aberta
                successors_this_node++;  // Incrementa o número de sucessores gerados
            }
        }

        // Atualiza o total de ramificações para cálculo do fator médio de ramificação
        total_branching += successors_this_node;
    }

    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    SearchStatistics stats;
    stats.algorithm_name = "Depth-First Search (DFS)";
    stats.heuristic_name = "";
    stats.elapsed_time = elapsed.count();
    stats.nodes_expanded = nodes_expanded;
    stats.nodes_visited = nodes_visited;
    stats.total_branching = total_branching;
    stats.solution_found = found;

    if (found)
    {
        stats.solution_cost = solution_path.back()->get_cost();
        stats.solution_depth = solution_path.back()->get_depth();
        stats.solution_path = solution_path;
    }

    print_statistics(stats);
}