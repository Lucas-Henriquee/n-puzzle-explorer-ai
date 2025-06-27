#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/list.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/order.hpp"

// Função que realiza a Busca Ordenada
void OrderSearch(Board board)
{
    size_t id = 0;              // ID único para cada estado gerado
    size_t nodes_expanded = 0;  // Contador de nós expandidos
    size_t nodes_visited = 0;   // Contador de nós visitados
    size_t total_branching = 0; // Soma total do número de sucessores gerados

    List openList; // Lista de estados abertos
    // List closedList = List();                                  // Lista de estados fechados
    unordered_set<vector<size_t>, VectorHash> closedSet; // Conjunto de estados já visitados para evitar repetições

    // Cria o estado inicial a partir do tabuleiro dado
    State *initialState = new State(id++, 0, 0, nullptr, board);

    openList.add(initialState); // Adiciona o estado inicial à lista aberta para expansão
    nodes_visited++;

    auto start_time = chrono::steady_clock::now();

    while (openList.is_not_empty())
    {
        // Pega o estado de menor custo da lista aberta
        State *currentState = openList.get_lower_cost();

        openList.remove(currentState); // Remove o estado escolhido da lista aberta para expandir
        nodes_expanded++;

        // Achata o tabuleiro do estado atual
        auto flat = flatten_board(currentState->get_board().real_board);

        // Se este estado já foi expandido antes, libera a memória
        if (closedSet.count(flat))
        {
            delete currentState;
            continue;
        }

        // Marca o estado atual como visitado
        closedSet.insert(flat);

        // Verifica se o estado atual é o objetivo do problema
        if (currentState->get_board().end_game())
        {
            auto end_time = chrono::steady_clock::now();
            chrono::duration<double> elapsed = end_time - start_time;

            cout << "Solução encontrada (Busca Ordenada)!\n\n";

            vector<State *> path;

            for (State *s = currentState; s != nullptr; s = s->get_parent())
                path.push_back(s);

            reverse(path.begin(), path.end());

            for (auto *s : path)
            {
                s->get_board().print_board(s->get_board().real_board);
                cout << "Custo: " << s->get_cost() << ", Profundidade: " << s->get_depth() << endl;
            }

            cout << "\nEstatísticas:\n";
            cout << "Profundidade da solução: " << currentState->get_depth() << endl;
            cout << "Custo da solução: " << currentState->get_cost() << endl;
            cout << "Nós expandidos: " << nodes_expanded << endl;
            cout << "Nós visitados: " << nodes_visited << endl;
            cout << "Fator médio de ramificação: " << (nodes_expanded > 0 ? (double)total_branching / nodes_expanded : 0) << endl;
            cout << "Tempo de execução: " << elapsed.count() << " s\n";

            return;
        }

        size_t successors_this_node = 0; // Contador de sucessores gerados a partir do estado atual

        for (char direction : {'U', 'D', 'L', 'R'})
        {
            Board newBoard = currentState->get_board(); // Cópia do tabuleiro atual para tentar movimento

            if (newBoard.move(direction)) // Se o movimento for válido
            {
                /*
                {
                    State *successor = new State(id, currentState->get_cost() + 1, currentState->get_depth() + 1, currentState, newBoard);
                    id++; // Incrementa o ID para o próximo sucessor
                    // Verifica se o sucessor já está na lista fechada
                    bool alreadyInClosedList = false;
                    State *closedState = closedList.get_head();
                    while (closedState != nullptr)
                    {
                        if (closedState->get_board().real_board == successor->get_board().real_board)
                        {
                            alreadyInClosedList = true; // O sucessor já está na lista fechada
                            break;
                        }
                        closedState = closedState->get_next(); // Avança para o próximo estado na lista
                    }
                    if (alreadyInClosedList)
                    {
                        delete successor; // Libera a memória do sucessor se já estiver na lista fechada
                        continue;         // Pula para o próximo sucessor
                    }
                    // Verifica se o sucessor já está na lista aberta
                    bool alreadyInOpenList = false;
                    State *openState = openList.get_head();
                    while (openState != nullptr)
                    {
                        if (openState->get_board().real_board == successor->get_board().real_board)
                        {
                            alreadyInOpenList = true; // O sucessor já está na lista aberta
                            break;
                        }
                    }
                    if (alreadyInOpenList)
                    {
                        delete successor; // Libera a memória do sucessor se já estiver na lista aberta
                        continue;         // Pula para o próximo sucessor
                    }
                    openList.add(successor); // Adiciona o sucessor à lista aberta
                }
                */

                // Achata o tabuleiro do sucessor para verificar se já foi visitado
                auto flatSucc = flatten_board(newBoard.real_board);

                // Ignora sucessores já visitados
                if (closedSet.count(flatSucc))
                    continue;

                bool alreadyInOpenList = false;

                State *openState = openList.get_head();

                while (openState != nullptr)
                {
                    if (flatten_board(openState->get_board().real_board) == flatSucc)
                    {
                        alreadyInOpenList = true;
                        break;
                    }
                    openState = openState->get_next();
                }

                if (alreadyInOpenList)
                    continue;

                // Cria o novo estado sucessor com custo e profundidade incrementados em 1
                State *successor = new State(id++, currentState->get_cost() + 1, currentState->get_depth() + 1, currentState, newBoard);

                openList.add(successor); // Adiciona sucessor na lista aberta

                nodes_visited++;
                successors_this_node++;
            }
        }

        total_branching += successors_this_node; // Atualiza total de ramificações com o número gerado neste nó

        delete currentState;
    }

    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    cout << "Solução não encontrada (Busca Ordenada).\n";
    cout << "Nós expandidos: " << nodes_expanded << endl;
    cout << "Nós visitados: " << nodes_visited << endl;
    cout << "Fator médio de ramificação: " << (nodes_expanded > 0 ? (double)total_branching / nodes_expanded : 0) << endl;
    cout << "Tempo de execução: " << elapsed.count() << " s\n";
}