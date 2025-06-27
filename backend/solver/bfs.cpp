#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/list.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/bfs.hpp"

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

    while (openList.is_not_empty())
    {
        // Enquanto houver estados na lista aberta
        State *currentState = openList.get_head(); // Obtém o estado atual

        openList.remove(currentState);                                      // Remove o estado atual da lista aberta
        closed.insert(flatten_board(currentState->get_board().real_board)); // Adiciona o estado atual ao conjunto de fechados

        nodes_expanded++; // Incrementa o contador de nós expandidos

        // Verifica se o estado atual é a solução
        if (currentState->get_board().end_game())
        {
            auto end_time = chrono::steady_clock::now();
            chrono::duration<double> elapsed = end_time - start_time;

            cout << "Solução encontrada!" << endl;

            // Reconstrução do caminho
            vector<State *> path;

            // Percorre os estados pais do estado atual até o estado inicial
            for (State *s = currentState; s != nullptr; s = s->get_parent())
                path.push_back(s);

            reverse(path.begin(), path.end());

            cout << "Caminho da solução (do estado inicial ao final):" << endl;

            for (auto *s : path)
            {
                s->get_board().print_board(s->get_board().real_board);
                cout << "Custo: " << s->get_cost() << ", Profundidade: " << s->get_depth() << endl;
            }

            cout << "Estatísticas:\n";
            cout << "Profundidade da solução: " << currentState->get_depth() << endl;
            cout << "Custo da solução: " << currentState->get_cost() << endl;
            cout << "Nós expandidos: " << nodes_expanded << endl;
            cout << "Nós visitados: " << nodes_visited << endl;
            cout << "Fator de ramificação médio: " << (nodes_expanded > 0 ? (double)total_branching / nodes_expanded : 0) << endl;
            cout << "Tempo de execução: " << elapsed.count() << " s\n";

            return;
        }

        size_t sucessors_this_node = 0; // Contador de sucessores deste nó

        // Gera os sucessores do estado atual e os adiciona à lista aberta
        for (char direction : {'U', 'D', 'L', 'R'})
        {
            Board newBoard = currentState->get_board(); // Cria uma cópia do tabuleiro atual

            // Tenta mover o espaço vazio na direção especificada
            if (newBoard.move(direction))
            {

                auto flat = flatten_board(newBoard.real_board); // Achata o tabuleiro para comparação

                // Verifica se o sucessor já foi visitado ou está na lista fechada
                if (visited.count(flat) || closed.count(flat))
                    continue;

                visited.insert(flat); // Adiciona o sucessor ao conjunto de visitados
                nodes_visited++;      // Incrementa o contador de nós visitados

                // Cria um novo estado sucessor
                State *successor = new State(id++, currentState->get_cost() + 1, currentState->get_depth() + 1, currentState, newBoard);

                openList.add(successor); // Adiciona o sucessor à lista aberta
                sucessors_this_node++;   // Incrementa o contador de sucessores deste nó
            }
        }

        total_branching += sucessors_this_node; // Atualiza o total de ramificações
    }

    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;

    cout << "Solução não encontrada." << endl;
    cout << "Estatísticas:" << endl;
    cout << "Número total de nós expandidos: " << nodes_expanded << endl;
    cout << "Número total de nós visitados: " << nodes_visited << endl;
    cout << "Média do fator de ramificação: " << (nodes_expanded > 0 ? (double)total_branching / nodes_expanded : 0) << endl;
    cout << "Tempo de execução: " << elapsed_seconds.count() << " segundos" << endl;
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