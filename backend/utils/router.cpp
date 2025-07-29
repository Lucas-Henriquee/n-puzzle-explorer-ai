// Define rotas Crow (modo web)

#include "crow/app.h"
#include "../include/router.hpp"
#include "../include/board.hpp"
#include "../include/heuristics.hpp"
#include "../include/backtracking.hpp"
#include "../include/order.hpp"
#include "../include/bfs.hpp"
#include "../include/dfs.hpp"
#include "../include/a_star.hpp"
#include "../include/ida_star.hpp"
#include "../include/greedy.hpp"
#include "../include/statistics.hpp"

#include "crow/json.h"
#include "../include/defines.hpp"

void define_routes(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/solve").methods("POST"_method)([](const crow::request &req)
                                                     {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Requisição JSON inválida");

        // size_t n = body["n"].i();
        // size_t m = body["m"].i();
        // string algorithm = body["algorithm"].s();
        // int heuristic_id = body["heuristic"].i();

        // vector<size_t> initial, goal;

        // for (auto &val : body["initial_board"]) initial.push_back(val.i());
        // for (auto &val : body["goal_board"]) goal.push_back(val.i());

        // size_t empty_pos = find(initial.begin(), initial.end(), 0) - initial.begin();
        // size_t empty_row = empty_pos / m;
        // size_t empty_col = empty_pos % m;

        // Board board(n, m, initial, goal, empty_row, empty_col);

        // SearchStatistics stats;

        // auto start = chrono::high_resolution_clock::now();

        // if (algorithm == "backtracking")
        //     stats = BacktrackingStarter(board);
        // else if (algorithm == "bfs")
        //     stats = BreadthFirstSearch(board);
        // else if (algorithm == "dfs")
        //     stats = DepthFirstSearch(board);
        // else if (algorithm == "ordered")
        //     stats = OrderSearch(board);
        // else if (algorithm == "greedy")
        //     stats = GreedySearch(board, heuristic_id);
        // else if (algorithm == "a_star")
        //     stats = AStarSearch(board, heuristic_id);
        // else if (algorithm == "ida_star")
        //     stats = IDAStarter(board, heuristic_id);
        // else
        //     return crow::response(400, "Algoritmo inválido");

        // auto end = chrono::high_resolution_clock::now();
        // stats.elapsed_time = chrono::duration<double>(end - start).count();

        // crow::json::wvalue result;
        // result["solution_found"] = stats.solution_found;
        // result["solution_cost"] = stats.solution_cost;
        // result["solution_depth"] = stats.solution_depth;
        // result["nodes_expanded"] = stats.nodes_expanded;
        // result["nodes_visited"] = stats.nodes_visited;
        // result["avg_branching_factor"] = stats.avg_branching_factor;
        // result["elapsed_time"] = stats.elapsed_time;
        // result["algorithm"] = stats.algorithm_name;
        // result["heuristic"] = stats.heuristic_name;

        // // Caminho da solução (vetor de matrizes lineares)
        // result["path"] = crow::json::wvalue::list();
        // for (auto state : stats.solution_path) {
        //     crow::json::wvalue flat_board;
        //     for (auto val : state->board) flat_board.push_back(val);
        //     result["path"].push_back(flat_board);
        // }

        //return crow::response(result);
        return crow::response("Teste reponse para o servidor Crow funcionando!"); });
}
