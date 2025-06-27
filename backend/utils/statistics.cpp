#include "../include/defines.hpp"
#include "../include/statistics.hpp"

void print_solution_path(const vector<State *> &path)
{
    for (auto *state : path)
    {
        state->get_board().print_board(state->get_board().real_board);
        cout << "Custo: " << state->get_cost() << ", Profundidade: " << state->get_depth() << endl;
    }
}

void print_statistics(const SearchStatistics &stats)
{
    cout << "\n========== Estatísticas ==========\n";

    if (stats.solution_found)
    {
        cout << "Solução encontrada usando: " << stats.algorithm_name << endl;
        if (!stats.heuristic_name.empty())
            cout << "Heurística utilizada: " << stats.heuristic_name << endl;

        cout << "\nCaminho da solução:\n";
        print_solution_path(stats.solution_path);

        cout << "\nProfundidade da solução: " << stats.solution_depth << endl;
        cout << "Custo da solução: " << stats.solution_cost << endl;
    }

    else
        cout << "Solução não encontrada usando: " << stats.algorithm_name << endl;

    cout << "Nós expandidos: " << stats.nodes_expanded << endl;
    cout << "Nós visitados: " << stats.nodes_visited << endl;

    double avg_bf = (stats.nodes_expanded > 0) ? static_cast<double>(stats.total_branching) / stats.nodes_expanded : 0.0;
    cout << "Fator médio de ramificação: " << avg_bf << endl;

    cout << "Tempo de execução: " << stats.elapsed_time << " s\n";
    cout << "===================================\n";
}