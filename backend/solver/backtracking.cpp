#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/state.hpp"
#include "../include/board_utils.hpp"
#include "../include/backtracking.hpp"

// Variáveis globais de estatísticas
size_t nodes_expanded = 0;
size_t nodes_visited = 0;
size_t total_branching = 0;

// Conjunto para rastrear estados visitados
unordered_set<vector<size_t>, VectorHash> visited;

// Caminho encontrado
vector<State *> solution_path;

// Função recursiva de backtracking
bool backtrack(State *currentState, size_t &id, chrono::steady_clock::time_point start_time)
{
    nodes_expanded++;

    // Verifica se o estado atual é a solução
    if (currentState->get_board().end_game())
    {
        // Reconstrói o caminho até o estado inicial
        solution_path.clear();
        State *s = currentState;

        // Percorre os estados pais do estado atual até o estado inicial
        while (s != nullptr)
        {
            solution_path.push_back(s);
            s = s->get_parent();
        }

        reverse(solution_path.begin(), solution_path.end());

        auto end_time = chrono::steady_clock::now();
        chrono::duration<double> elapsed = end_time - start_time;

        cout << "Solução encontrada (Backtracking)!\n\n";

        for (auto *state : solution_path)
        {
            state->get_board().print_board(state->get_board().real_board);
            cout << "Custo: " << state->get_cost() << ", Profundidade: " << state->get_depth() << endl;
        }

        cout << "\nEstatísticas:\n";
        cout << "Profundidade da solução: " << currentState->get_depth() << endl;
        cout << "Custo da solução: " << currentState->get_cost() << endl;
        cout << "Número de nós expandidos: " << nodes_expanded << endl;
        cout << "Número de nós visitados: " << nodes_visited << endl;
        cout << "Fator médio de ramificação: " << (nodes_expanded > 0 ? (double)total_branching / nodes_expanded : 0) << endl;
        cout << "Tempo de execução: " << elapsed.count() << " s\n";

        return true;
    }

    size_t successors_this_node = 0;

    for (char dir : {'U', 'D', 'L', 'R'})
    {
        Board newBoard = currentState->get_board();

        // Tenta mover o espaço vazio na direção especificada
        if (newBoard.move(dir))
        {
            // Achata o tabuleiro para comparação
            auto flat = flatten_board(newBoard.real_board);

            // Pula para evitar loops em nós visitados
            if (visited.count(flat))
                continue;

            visited.insert(flat);
            nodes_visited++;

            // Cria um novo estado sucessor
            State *successor = new State(id++, currentState->get_cost() + 1, currentState->get_depth() + 1, currentState, newBoard);

            successors_this_node++;

            // Chamada recursiva para explorar esse sucessor
            if (backtrack(successor, id, start_time))
                return true;

            // Remove o estado visitado caso não seja solução
            visited.erase(flat);
        }
    }

    // Atualiza o total de ramificações para cálculo do fator médio de ramificação
    total_branching += successors_this_node;

    return false;
}

void BacktrackingSearch(Board initialBoard)
{
    nodes_expanded = 0;    // Reseta o contador de nós expandidos
    nodes_visited = 0;     // Reseta o contador de nós visitados
    total_branching = 0;   // Reseta o total de ramificações
    visited.clear();       // Limpa o conjunto de estados visitados
    solution_path.clear(); // Limpa o caminho da solução

    auto start_time = chrono::steady_clock::now();

    // Cria um estado inicial com o tabuleiro inicial
    size_t id = 0;

    auto flat = flatten_board(initialBoard.real_board);

    visited.insert(flat);
    nodes_visited++;

    // Cria o estado inicial com ID 0, custo 0, profundidade 0 e sem pai
    State *initialState = new State(id++, 0, 0, nullptr, initialBoard);

    // Inicia a busca por backtracking
    bool found = backtrack(initialState, id, start_time);

    if (!found)
    {
        auto end_time = chrono::steady_clock::now();
        chrono::duration<double> elapsed = end_time - start_time;

        cout << "Solução não encontrada (Backtracking).\n";
        cout << "Número de nós expandidos: " << nodes_expanded << endl;
        cout << "Número de nós visitados: " << nodes_visited << endl;
        cout << "Fator médio de ramificação: " << (nodes_expanded > 0 ? (double)total_branching / nodes_expanded : 0) << endl;
        cout << "Tempo de execução: " << elapsed.count() << " s\n";
    }
}