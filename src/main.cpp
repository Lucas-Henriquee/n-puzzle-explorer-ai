#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/bfs.hpp"
#include "../include/dfs.hpp"
#include "../include/backtracking.hpp"
#include "../include/order.hpp"
#include "../include/greedy.hpp"
#include "../include/heuristics.hpp"

int main()
{
    int n, m;
    cout << "Digite o número de linhas do tabuleiro: ";
    cin >> n;
    cout << "Digite o número de colunas do tabuleiro: ";
    cin >> m;

    Board initialBoard(n, m);

    cout << "Selecione o algoritmo:\n";
    cout << "1 - BFS\n";
    cout << "2 - DFS\n";
    cout << "3 - Backtracking\n";
    cout << "4 - Order\n";
    cout << "5 - Interação manual\n";
    cout << "6 - Greedy Search\n";
    cout << "7 - A* Search\n";
    cout << "8 - IDA* Search\n";

    int choice;
    cin >> choice;

    int heuristic_choice;
    string heuristic_name;

    if (choice == 6 || choice == 7 || choice == 8)
    {
        cout << "Selecione a heurística:\n";
        cout << "1 - Manhattan\n";
        cout << "2 - Euclidean\n";
        cout << "3 - Misplaced Tiles\n";
        cout << "4 - Hamming\n";
        cout << "5 - Linear Conflict\n";
        cout << "6 - Zero\n";
        cin >> heuristic_choice;

        switch (heuristic_choice)
        {
        case 1:
            heuristic_name = "manhattan";
            break;
        case 2:
            heuristic_name = "euclidean";
            break;
        case 3:
            heuristic_name = "misplaced_tiles";
            break;
        case 4:
            heuristic_name = "hamming";
            break;
        case 5:
            heuristic_name = "linear_conflict";
            break;
        case 6:
            heuristic_name = "zero";
            break;
        default:
            cout << "Heurística inválida!\n";
            return 1;
        }
    }

    switch (choice)
    {
    case 1:
        BreadthFirstSearch(initialBoard);
        break;
    case 2:
        DepthFirstSearch(initialBoard);
        break;
    case 3:
        BacktrackingSearch(initialBoard);
        break;
    case 4:
        OrderSearch(initialBoard);
        break;
    case 5:
        initialBoard.start_interactive_session();
        break;
    case 6:
        GreedySearch(initialBoard, heuristic_name);
        break;
    case 7:
        // AStarSearch(initialBoard, heuristic_name);
        cout << "A* Search ainda não implementado.\n";
        break;
    case 8:
        // IDAStarSearch(initialBoard, heuristic_name);
        cout << "IDA* Search ainda não implementado.\n";
        break;
    default:
        cout << "Opção inválida!\n";
    }

    return 0;
}
