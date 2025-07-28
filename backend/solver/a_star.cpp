#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/greedy.hpp"
#include "../include/heuristics.hpp"
#include "../include/list.hpp"
#include "../include/state.hpp"
#include "../include/statistics.hpp"
#include "../include/board_utils.hpp"

void AStarSearch(Board board, const int &heuristic_choice)
{
    size_t id = 0;              // Inicializa o ID do estado
    size_t nodes_expanded = 0;  // Contador de nós expandidos
    size_t nodes_visited = 0;   // Contador de nós visitados
    size_t total_branching = 0; // Contador do total de ramificações

    unordered_set<vector<size_t>, VectorHash> visited; // Conjunto para armazenar estados visitados
    unordered_set<vector<size_t>, VectorHash> closed;  // Conjunto para armazenar estados fechados
    vector<State *> closedList;                        // Lista para armazenar estados fechados

    List openList(true); // Lista de estados abertos

    auto start_time = chrono::steady_clock::now(); // Marca o tempo de início da busca

    double heuristic_value = calculate_heuristic(board, heuristic_choice); // Calcula o valor da heurística inicial

    State *initialState = new State(id++, 0, heuristic_value, 0, nullptr, board); // Estado inicial

    openList.add(initialState); // Adiciona o estado inicial à lista aberta

    visited.insert(board.real_board); // Adiciona o estado inicial ao conjunto de visitados
    nodes_visited++;                  // Incrementa o contador de nós visitados

    bool found = false;            // Variável para indicar se a solução foi encontrada
    vector<State *> solution_path; // Vetor para armazenar o caminho da solução

    while (openList.is_not_empty())
    {
        State *currentState = openList.get_lower_cost(); // Obtém o estado atual

        openList.remove(currentState);                       // Remove o estado atual da lista aberta
        closed.insert(currentState->get_board().real_board); // Adiciona o estado atual ao conjunto de fechados

        closedList.push_back(currentState);

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
                if (visited.count(newBoard.real_board) || closed.count(newBoard.real_board))
                    continue;

                visited.insert(newBoard.real_board);
                nodes_visited++;

                heuristic_value = calculate_heuristic(newBoard, heuristic_choice);
                State *successor = new State(id++, currentState->get_cost() + 1, heuristic_value, currentState->get_depth() + 1, currentState, newBoard);

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
    stats.algorithm_name = "A Star (A*)";
    stats.heuristic_name = "";
    stats.elapsed_time = elapsed.count();
    stats.nodes_expanded = nodes_expanded;
    stats.nodes_visited = nodes_visited;
    stats.total_branching = total_branching;
    stats.solution_found = found;
    stats.closed_list = closedList;

    if (found)
    {
        stats.solution_cost = solution_path.back()->get_cost();
        stats.solution_depth = solution_path.back()->get_depth();
        stats.solution_path = solution_path;
    }

    print_statistics(stats);
}