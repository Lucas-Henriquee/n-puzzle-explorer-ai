#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/list.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/bfs.hpp"
#include "../include/statistics.hpp"

// Implementação da Busca em Largura (BFS)
void BreadthFirstSearch(Board board)
{
    size_t id = 0;              // Inicializa o ID do estado
    size_t nodes_expanded = 0;  // Contador de nós expandidos
    size_t nodes_visited = 0;   // Contador de nós visitados
    size_t total_branching = 0; // Contador do total de ramificações

    unordered_set<vector<size_t>, VectorHash> visited; // Conjunto para armazenar estados visitados
    unordered_set<vector<size_t>, VectorHash> closed;  // Conjunto para armazenar estados fechados

    List openList; // Lista de estados abertos

    auto start_time = chrono::steady_clock::now(); // Marca o tempo de início da busca

    State *initialState = new State(id++, 0, 0, nullptr, board); // Estado inicial

    openList.add(initialState); // Adiciona o estado inicial à lista aberta

    visited.insert(flatten_board(board.real_board)); // Adiciona o estado inicial ao conjunto de visitados
    nodes_visited++;                                 // Incrementa o contador de nós visitados

    bool found = false;            // Variável para indicar se a solução foi encontrada
    vector<State *> solution_path; // Vetor para armazenar o caminho da solução

    while (openList.is_not_empty())
    {
        State *currentState = openList.get_head(); // Obtém o estado atual

        openList.remove(currentState);                                      // Remove o estado atual da lista aberta
        closed.insert(flatten_board(currentState->get_board().real_board)); // Adiciona o estado atual ao conjunto de fechados

        nodes_expanded++;

        // Verifica se o estado atual é a solução
        if (currentState->get_board().end_game())
        {
            found = true;

            // Reconstrução do caminho
            for (State *s = currentState; s != nullptr; s = s->get_parent())
                solution_path.push_back(s);

            reverse(solution_path.begin(), solution_path.end());

            break;
        }

        size_t successors_this_node = 0;

        // Gera os sucessores do estado atual e os adiciona à lista aberta
        for (char direction : {'U', 'D', 'L', 'R'})
        {
            Board newBoard = currentState->get_board(); // Cria uma cópia do tabuleiro atual

            if (newBoard.move(direction))
            {
                auto flat = flatten_board(newBoard.real_board);

                if (visited.count(flat) || closed.count(flat))
                    continue;

                visited.insert(flat);
                nodes_visited++;

                State *successor = new State(id++, currentState->get_cost() + 1, currentState->get_depth() + 1, currentState, newBoard);

                openList.add(successor);
                successors_this_node++;
            }
        }

        total_branching += successors_this_node;
    }

    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    // Monta as estatísticas
    SearchStatistics stats;
    stats.algorithm_name = "Breadth-First Search (BFS)";
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

// State *successor = new State(id, currentState->get_cost() + 1, currentState->get_depth() + 1, currentState, newBoard);
// id++; // Incrementa o ID para o próximo sucessor
// // Verifica se o sucessor já está na lista fechada
// bool alreadyInClosedList = false;
// State *closedState = closedList.get_head();
// while (closedState != nullptr)
// {
//     if (closedState->get_board().real_board == successor->get_board().real_board)
//     {                               // TODO: Atualizar essa igualdade para reduzir custo computacional
//         alreadyInClosedList = true; // O sucessor já está na lista fechada
//         break;
//     }
//     closedState = closedState->get_next(); // Avança para o próximo estado na lista
// }
// if (alreadyInClosedList)
// {
//     delete successor; // Libera a memória do sucessor se já estiver na lista fechada
//     continue;         // Pula para o próximo sucessor
// }
// // Verifica se o sucessor já está na lista aberta
// bool alreadyInOpenList = false;
// State *openState = openList.get_head();
// while (openState != nullptr)
// {
//     if (openState->get_board().real_board == successor->get_board().real_board)
//     {                             // TODO: Atualizar essa igualdade para reduzir custo computacional
//         alreadyInOpenList = true; // O sucessor já está na lista aberta
//         break;
//     }
// }
// if (alreadyInOpenList)
// {
//     delete successor; // Libera a memória do sucessor se já estiver na lista aberta
//     continue;         // Pula para o próximo sucessor
// }
// openList.add(successor); // Adiciona o sucessor à lista aberta
//             }
//         }
//     }
// }