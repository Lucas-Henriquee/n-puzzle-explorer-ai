#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/ida_star.hpp"
#include "../include/heuristics.hpp"
#include "../include/list.hpp"
#include "../include/state.hpp"
#include "../include/statistics.hpp"
#include "../include/board_utils.hpp"

void IDAStarter(Board board, const int &heuristic_choice)
{
    size_t id = 0;              // Inicializa o ID do estado
    size_t nodes_expanded = 0;  // Contador de nós expandidos
    size_t nodes_visited = 0;   // Contador de nós visitados
    size_t total_branching = 0; // Contador do total de ramificações

    double baseline = heuristic(board, heuristic_choice); // Calcula o valor da heurística inicial
    unordered_set<vector<size_t>, VectorHash> visited; // Conjunto para armazenar estados visitados
    unordered_set<vector<size_t>, VectorHash> closed;  // Conjunto para armazenar estados fechados
    vector<State *> closedList;                        // Lista para armazenar estados fechados
    double new_baseline;
    bool found = false;            // Variável para indicar se a solução foi encontrada
    vector<State *> solution_path; // Vetor para armazenar o caminho da solução
    auto start_time = chrono::steady_clock::now(); // Marca o tempo de início da busca
    while(true)
    {
        new_baseline = IDAStarSearch(board, heuristic_choice, baseline, visited, closedList, nodes_expanded, nodes_visited, total_branching, id, found, nullptr); // Chama a função de busca IDA*
        if(new_baseline == baseline) // Se não houve aumento do baseline
        {
            auto end_time = chrono::steady_clock::now(); // Marca o tempo de fim da busca
            chrono::duration<double> elapsed = end_time - start_time; // Calcula o tempo decorrido

            SearchStatistics stats;
            stats.algorithm_name = "IDA STAR (IDA*)";
            stats.elapsed_time = elapsed.count();
            stats.nodes_expanded = nodes_expanded;
            stats.nodes_visited = nodes_visited;
            stats.total_branching = total_branching;
            stats.solution_found = found;
            stats.closed_list = closedList;

            switch (heuristic_choice)
            {
            case 1:
                stats.heuristic_name = "Manhattan";
                break;
            case 2:
                stats.heuristic_name = "Euclidean";
                break;
            case 3:
                stats.heuristic_name = "Misplaced Tiles";
                break;
            case 4:
                stats.heuristic_name = "Linear Conflict";
                break;
            case 5:
                stats.heuristic_name = "Manhattan Inversions";
                break;
            case 6:
                stats.heuristic_name = "Weighted Sum";
                break;
            default:
                stats.heuristic_name = "Unknown Heuristic";
            }

            State *last_state = closedList.back();
            if (found)
            {
                stats.solution_cost = last_state->get_cost();
                stats.solution_depth = last_state->get_depth();
                for (State *s = last_state; s != nullptr; s = s->get_parent())
                    stats.solution_path.push_back(s);
                reverse(stats.solution_path.begin(), stats.solution_path.end());
            }
            else
            {
                stats.solution_cost = 0;
                stats.solution_depth = 0;
            }
            stats.avg_branching_factor = static_cast<double>(stats.nodes_expanded) / stats.nodes_visited;
            print_statistics(stats); // Imprime as estatísticas da busca
            return;
        }
        baseline = new_baseline; // Atualiza o baseline para o próximo ciclo
        visited.clear(); // Limpa o conjunto de visitados
        closed.clear(); // Limpa o conjunto de fechados
        closedList.clear(); // Limpa a lista de fechados
        id = 0; // Reseta o ID do estado
    }
}

double IDAStarSearch(Board board, const int &heuristic_choice, double baseline,
                     unordered_set<vector<size_t>, VectorHash> &visited,
                     vector<State *> &closedList, size_t &nodes_expanded, size_t &nodes_visited, size_t &total_branching, size_t &id,bool &found, State *parent)
{
    double lower_new_baseline = -1; // Inicializa o menor novo baseline como -1
    double new_baseline = -1; // Inicializa o novo baseline como -1
    State *currentState = nullptr; // Inicializa o estado atual como nulo
    if (parent == nullptr) // Se o estado pai for nulo, cria o estado inicial
    {
        currentState = new State(id++, 0, 0 + heuristic(board, heuristic_choice), 0, nullptr, board); // Cria o estado inicial
        visited.insert(board.real_board); // Adiciona o estado inicial ao conjunto de visitados
    }
    else{
        currentState = new State(id++, parent->get_cost() + 1, heuristic(board, heuristic_choice), parent->get_depth() + 1, parent, board); // Cria o estado atual
        visited.insert(currentState->get_board().real_board); // Adiciona o estado atual ao conjunto de visitados
    }

    closedList.push_back(currentState); // Adiciona o estado atual à lista de fechados

    nodes_expanded++; // Incrementa o contador de nós expandidos
    nodes_visited++;  // Incrementa o contador de nós visitados

    if (currentState->get_board().end_game()) // Verifica se o estado atual é a solução
    {
        found = true; // Marca que a solução foi encontrada
        return currentState->get_total_cost(); // Retorna o novo baseline
    }
    for (char direction : {'U', 'D', 'L', 'R'}) // Itera sobre as direções possíveis
    {
        Board newBoard = currentState->get_board(); // Cria uma cópia do tabuleiro atual
        if (!newBoard.move(direction)) // Tenta mover o espaço vazio na direção especificada
            continue; // Se o movimento não for válido, continua para a próxima direção

        if (visited.find(newBoard.real_board) != visited.end()) // Verifica se o sucessor já foi visitado
        {
            continue; // Continua para o próximo sucessor
        }

        if (heuristic(newBoard, heuristic_choice) + currentState->get_cost() + 1 > baseline) // Verifica se o custo total do sucessor é maior que o baseline
        {
            if (new_baseline == -1 || heuristic(newBoard, heuristic_choice) + currentState->get_cost() + 1 < new_baseline) // Se o novo baseline ainda não foi definido ou é maior que o custo do sucessor
                new_baseline = heuristic(newBoard, heuristic_choice) + currentState->get_cost() + 1; // Atualiza o novo baseline
            if (new_baseline < lower_new_baseline || lower_new_baseline == -1)
                lower_new_baseline = new_baseline;
            continue; // Continua para o próximo sucessor
        }

        new_baseline = IDAStarSearch(newBoard, heuristic_choice, baseline, visited, closedList, nodes_expanded, nodes_visited, total_branching, id, found, currentState); // Chama recursivamente a busca IDA*
        if (new_baseline < lower_new_baseline || lower_new_baseline == -1)
            lower_new_baseline = new_baseline;

        if (found) // Se a solução foi encontrada
        {
            return lower_new_baseline; // Retorna o novo baseline
        }
        total_branching++; // Incrementa o contador de ramificações
    }
    closedList.pop_back(); // Remove o estado atual da lista de fechados
    visited.erase(currentState->get_board().real_board); // Remove o estado atual do conjunto
    delete currentState; // Libera a memória do estado atual
    return lower_new_baseline; // Retorna o novo baseline
}