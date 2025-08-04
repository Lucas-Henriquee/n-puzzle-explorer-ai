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
#include "../include/state.hpp"

#include "crow/json.h"
#include "../include/defines.hpp"

void define_routes(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/solve").methods("POST"_method)([](const crow::request &req)
                                                     {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Requisição JSON inválida");

        std::string algorithm = body["algorithm"].s();
        std::string heuristic_str = body.has("heuristic") ? std::string(body["heuristic"].s()) : std::string("");

        int heuristic_choice = -1;

        if (heuristic_str == "Manhattan") {
            heuristic_choice = 1;
        } else if (heuristic_str == "Euclidean") {
            heuristic_choice = 2;
        } else if (heuristic_str == "Misplaced") {
            heuristic_choice = 3;
        } else if (heuristic_str == "Linear") {
            heuristic_choice = 4;
        } else if (heuristic_str == "Permutation") {
            heuristic_choice = 5;
        } else if (heuristic_str == "Weighted") {
            heuristic_choice = 6;
        } else if (!heuristic_str.empty()) {
            return crow::response(400, "Heurística inválida: " + heuristic_str);
        }

        // Extrai tabuleiro inicial
        std::vector<size_t> initial;
        size_t n = body["initial"].size();
        size_t m = body["initial"][0].size();
        for (const auto &row : body["initial"]) {
            for (const auto &val : row) {
                initial.push_back(val.i());
            }
        }

        // Extrai tabuleiro objetivo
        std::vector<size_t> goal;
        for (const auto &row : body["goal"]) {
            for (const auto &val : row) {
                goal.push_back(val.i());
            }
        }

        size_t empty_pos = find(initial.begin(), initial.end(), 0) - initial.begin();
        Board board(n, m, initial, goal, empty_pos / m, empty_pos % m);

        SearchStatistics stats;
        auto start = std::chrono::high_resolution_clock::now();
        
        if (algorithm == "Backtracking") {
            stats = BacktrackingStarter(board);
        } else if (algorithm == "BFS") {
            stats = BreadthFirstSearch(board);
        } else if (algorithm == "DFS") {
            stats = DepthFirstSearch(board);
        } else if (algorithm == "Order") {
            stats = OrderSearch(board);
        } else if (algorithm == "Greedy") {
            stats = GreedySearch(board, heuristic_choice);
        } else if (algorithm == "A*") {
            stats = AStarSearch(board, heuristic_choice);
        } else if (algorithm == "IDA*") {
            stats = IDAStarter(board, heuristic_choice);
        } else {
            return crow::response(400, "Algoritmo inválido: " + algorithm);
        }
        // print_statistics(stats);
        
        auto end = std::chrono::high_resolution_clock::now();
        stats.elapsed_time = std::chrono::duration<double>(end - start).count();
        
        crow::json::wvalue result;
        result["stats"]["closed_list"] = stats.closed_list;
        result["stats"]["solution_found"] = stats.solution_found;
        result["stats"]["tempo_ms"] = stats.elapsed_time * 1000;
        result["stats"]["nos_visitados"] = stats.nodes_visited;
        result["stats"]["profundidade"] = stats.solution_depth;
        
        result["solution"] = crow::json::wvalue::list();
        
        size_t k = 0;
        for (auto state : stats.solution_path) {
            crow::json::wvalue matrix;
            size_t rows = state->get_board().get_rows();
            size_t columns = state->get_board().get_cols(); 
            for (size_t i = 0; i < rows; i++) {
                crow::json::wvalue row;
                for (size_t j = 0; j < columns; j++) {
                    row[j] = state->get_board().real_board[i * columns + j];
                }
                matrix[i] = std::move(row);
            }
            result["solution"][k++] = std::move(matrix);
        }
        
        return crow::response(result); });
    }