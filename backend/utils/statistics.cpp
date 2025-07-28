#include "../include/defines.hpp"
#include "../include/statistics.hpp"

void print_solution_path(const vector<State *> &path)
{
    if (path.empty())
    {
        cout << "Nenhum caminho de solução disponível.\n";
        return;
    }

    cout << "===== Caminho da Solução =====\n";
    for (auto *state : path)
    {
        state->get_board().print_board(state->get_board().real_board);
        cout << "ID: " << state->get_id()
             << ", Custo: " << state->get_cost()
             << ", Profundidade: " << state->get_depth()
             << endl;
        cout << "-----------------------------\n";
    }
    cout << "==============================\n";
}

void print_closed_list(const vector<State *> &closed_list)
{
    if (closed_list.empty())
    {
        cout << "Nenhum estado fechado.\n";
        return;
    }

    cout << "\n===== Estados Fechados =====\n";
    for (auto *state : closed_list)
    {
        state->get_board().print_board(state->get_board().real_board);
        cout << "ID: " << state->get_id()
             << ", Custo: " << state->get_cost()
             << ", Profundidade: " << state->get_depth()
             << endl;
        cout << "-----------------------------\n";
    }
    cout << "=============================\n";
}

void print_statistics(const SearchStatistics &stats)
{
    cout << "\n========== Estatísticas ==========\n";

    if (stats.solution_found)
    {
        cout << "Solução encontrada usando: " << stats.algorithm_name << endl;
        if (!stats.heuristic_name.empty())
            cout << "Heurística utilizada: " << stats.heuristic_name << endl;

        cout << "\nProfundidade da solução: " << stats.solution_depth << endl;
        cout << "Custo da solução: " << stats.solution_cost << endl;

        // print_solution_path(stats.solution_path);
    }

    else
    {
        cout << "Solução não encontrada usando: " << stats.algorithm_name << endl;
    }

    cout << "\nNós expandidos: " << stats.nodes_expanded << endl;
    cout << "Nós visitados: " << stats.nodes_visited << endl;

    double avg_bf = (stats.nodes_expanded > 0) ? static_cast<double>(stats.total_branching) / stats.nodes_expanded : 0.0;
    cout << "Fator médio de ramificação: " << avg_bf << endl;

    cout << "Tempo de execução: " << stats.elapsed_time << " s\n";

    // print_closed_list(stats.closed_list);

    cout << "===================================\n";
}