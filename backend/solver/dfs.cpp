#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/list.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/dfs.hpp"

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
            auto end_time = chrono::steady_clock::now();
            chrono::duration<double> elapsed = end_time - start_time;

            cout << "Solução encontrada (DFS)!" << endl;

            // Reconstrução do caminho da solução
            vector<State *> path;

            for (State *s = currentState; s != nullptr; s = s->get_parent())
                path.push_back(s);

            reverse(path.begin(), path.end()); // Inverte o caminho para mostrar do início ao fim

            // Imprime o caminho da solução
            for (auto *s : path)
            {
                s->get_board().print_board(s->get_board().real_board);
                cout << "Custo: " << s->get_cost() << ", Profundidade: " << s->get_depth() << endl;
            }

            // Exibe as estatísticas da busca
            cout << "\nEstatísticas:" << endl;
            cout << "Profundidade da solução: " << currentState->get_depth() << endl;
            cout << "Custo da solução: " << currentState->get_cost() << endl;
            cout << "Número total de nós expandidos: " << nodes_expanded << endl;
            cout << "Número total de nós visitados: " << nodes_visited << endl;
            cout << "Média do fator de ramificação: " << (nodes_expanded > 0 ? (double)total_branching / nodes_expanded : 0) << endl;
            cout << "Tempo de execução: " << elapsed.count() << " segundos" << endl;

            return;
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
                    continue; // Ignora estados já visitados

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

    // Se o laço termina sem encontrar a solução:
    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    cout << "Solução não encontrada (DFS)." << endl;
    cout << "Número total de nós expandidos: " << nodes_expanded << endl;
    cout << "Número total de nós visitados: " << nodes_visited << endl;
    cout << "Média do fator de ramificação: " << (nodes_expanded > 0 ? (double)total_branching / nodes_expanded : 0) << endl;
    cout << "Tempo de execução: " << elapsed.count() << " segundos" << endl;
}