#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/backtracking.hpp"
#include "../include/statistics.hpp"

// Função principal do Backtracking
void BacktrackingStarter(Board initialBoard)
{
    size_t id = 0;
    size_t nodes_expanded = 0;
    size_t nodes_visited = 0;
    size_t total_branching = 0;

    unordered_set<vector<size_t>, VectorHash> visited;

    vector<State *> closedList;
    bool found = false;

    auto start_time = chrono::steady_clock::now();

    // Chamada inicial para a busca recursiva
    BacktrackingSearch(
        initialBoard,
        visited,
        closedList,
        nodes_expanded,
        nodes_visited,
        total_branching,
        id,
        found,
        nullptr // parent == nullptr
    );

    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    SearchStatistics stats;
    stats.algorithm_name = "Backtracking";
    stats.heuristic_name = "";
    stats.elapsed_time = elapsed.count();
    stats.nodes_expanded = nodes_expanded;
    stats.nodes_visited = nodes_visited;
    stats.total_branching = total_branching;
    stats.solution_found = found;
    stats.closed_list = closedList;

    if (found)
    {
        State *last_state = closedList.back();
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

    stats.avg_branching_factor = (stats.nodes_visited > 0) ? static_cast<double>(stats.nodes_expanded) / stats.nodes_visited : 0.0;

    print_statistics(stats);
}

// Função recursiva
void BacktrackingSearch(Board board, unordered_set<vector<size_t>, VectorHash> &visited, vector<State *> &closedList, size_t &nodes_expanded, size_t &nodes_visited, size_t &total_branching, size_t &id, bool &found, State *parent)
{
    size_t currentDepth = (parent ? parent->get_depth() + 1 : 0);

    const size_t MAX_DEPTH = calculateMaxDepth(board.get_rows(), board.get_cols());

    if (currentDepth > MAX_DEPTH) {
        return;
    }

    State *currentState = nullptr;

    // Criação do estado
    if (parent == nullptr)
    {
        currentState = new State(id++, 0, 0, 0, nullptr, board);
        visited.insert(board.real_board);
    }
    else
    {
        currentState = new State(id++, parent->get_cost() + 1, 0, parent->get_depth() + 1, parent, board);
        visited.insert(currentState->get_board().real_board);
    }

    closedList.push_back(currentState);
    nodes_expanded++;
    nodes_visited++;

    // Checa objetivo
    if (currentState->get_board().end_game())
    {
        found = true;
        return;
    }

    // Movimentos possíveis
    for (char direction : {'U', 'D', 'L', 'R'})
    {
        Board newBoard = currentState->get_board();

        if (!newBoard.move(direction))
            continue;

        // Evita ciclos simples
        if (visited.find(newBoard.real_board) != visited.end())
            continue;

        // Recursão
        BacktrackingSearch(newBoard, visited, closedList,
                           nodes_expanded, nodes_visited,
                           total_branching, id, found, currentState);

        if (found)
        {
            return;
        }

        // Desfaz a visita
        visited.erase(newBoard.real_board);
    }

    delete currentState; // Libera memória
    cout << "Profundidade maxima atingida: " << MAX_DEPTH << endl;
}