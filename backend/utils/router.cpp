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
    CROW_ROUTE(app, "/solve").methods("POST"_method)
    ([](const crow::request &req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Requisição JSON inválida");

        // Extrai o tabuleiro enviado
        vector<size_t> initial;
        for (const auto &row : body["initial"]) {
            for (const auto &val : row) {
                initial.push_back(val.i());
            }
        }

        vector<size_t> goal = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 0
        };

        size_t n = 3, m = 3;
        size_t empty_pos = find(initial.begin(), initial.end(), 0) - initial.begin();
        Board board(n, m, initial, goal, empty_pos / m, empty_pos % m);

        SearchStatistics stats;
        auto start = chrono::high_resolution_clock::now();

        stats = OrderSearch(board);

        auto end = chrono::high_resolution_clock::now();
        stats.elapsed_time = chrono::duration<double>(end - start).count();

        crow::json::wvalue result;
        result["stats"]["tempo_ms"] = stats.elapsed_time * 1000;
        result["stats"]["nos_visitados"] = stats.nodes_visited;
        result["stats"]["profundidade"] = stats.solution_depth;

        result["solution"] = crow::json::wvalue::list();

        size_t k = 0;
        for (auto state : stats.solution_path) {
            crow::json::wvalue matrix;
            size_t side = sqrt(state->get_board().real_board.size());
            for (size_t i = 0; i < side; i++) {
                crow::json::wvalue row;
                for (size_t j = 0; j < side; j++) {
                    row[j] = state->get_board().real_board[i * side + j];
                }
                matrix[i] = std::move(row);
            }
            result["solution"][k++] = std::move(matrix);
        }

        return crow::response(result);
    });
}



