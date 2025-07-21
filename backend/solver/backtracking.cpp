#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/backtracking.hpp"
#include "../include/statistics.hpp"


bool backtrack_iterative(State *initialState, size_t &id, size_t &nodes_expanded, size_t &nodes_visited, size_t &total_branching, unordered_set<vector<size_t>, VectorHash> &visited, vector<State *> &solution_path)
{
    // Strutura para armazenar o estado atual e as direções a serem exploradas
    struct StackFrame
    {
        State *state;
        vector<char> moves;
        size_t move_index;

        StackFrame(State *s) : state(s), moves({'U', 'D', 'L', 'R'}), move_index(0) {}
    };

    // Variáveis para estatísticas
    size_t iterations = 0;

    // Pilha para armazenar os frames de execução
    stack<StackFrame> stack;
    stack.push(StackFrame(initialState));

    while (!stack.empty())
    {
        iterations++;

        StackFrame &frame = stack.top();
        State *current = frame.state;

        if (current->get_board().end_game())
        {
            // Reconstrói o caminho da solução
            for (State *s = current; s != nullptr; s = s->get_parent())
                solution_path.push_back(s);

            reverse(solution_path.begin(), solution_path.end());
            cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
            return true;
        }

        char dir = frame.moves[frame.move_index++];
        Board newBoard = current->get_board();

        // Tenta mover
        if (!newBoard.move(dir))
        {
            continue; // Tenta a próxima direção
        }
        
        if (is_ancestor(current, newBoard.real_board))
            continue;

        // Se esgotou todas as direções possíveis, faz o backtrack
        if (frame.move_index >= frame.moves.size())
        {
            visited.erase(current->get_board().real_board);
            cout << "Removendo aaaaaaaaaaaaaaaaa" << endl;
            State *aux_current = current->get_parent();
            delete current;
            current = aux_current;
            stack.pop();
            continue;
        }

        
        // Cria novo estado
        State *successor = new State(id++, current->get_cost() + 1, 0, current->get_depth() + 1, current, newBoard);
        nodes_expanded++;
        total_branching++;

        // Marca como visitado
        visited.insert(newBoard.real_board);
        nodes_visited++;

        current = successor;

        // Continua para esse sucessor
        stack.push(StackFrame(current));
    }

    return false;
}

void BacktrackingSearch(Board initialBoard)
{
    size_t nodes_expanded = 0;
    size_t nodes_visited = 0;
    size_t total_branching = 0;

    unordered_set<vector<size_t>, VectorHash> visited;
    vector<State *> solution_path;

    visited.clear();
    solution_path.clear();

    auto start_time = chrono::steady_clock::now();

    size_t id = 0;
    visited.insert(initialBoard.real_board);
    nodes_visited++;

    State *initialState = new State(id++, 0, 0, 0, nullptr, initialBoard);

    bool found = backtrack_iterative(initialState, id, nodes_expanded, nodes_visited, total_branching, visited, solution_path);

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
    stats.solution_path = solution_path;

    if (found)
    {
        stats.solution_cost = solution_path.back()->get_cost();
        stats.solution_depth = solution_path.back()->get_depth();
        stats.solution_path = solution_path;
    }

    print_statistics(stats);
}