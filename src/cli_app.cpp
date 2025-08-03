#include "../include/defines.hpp"
#include "../include/cli_app.hpp"
#include "../include/board.hpp"
#include "../include/bfs.hpp"
#include "../include/dfs.hpp"
#include "../include/backtracking.hpp"
#include "../include/order.hpp"
#include "../include/greedy.hpp"
#include "../include/a_star.hpp"
#include "../include/ida_star.hpp"
#include "../include/heuristics.hpp"
#include "../include/statistics.hpp"

bool loadBoardFromFile(const string &filename, size_t &n, size_t &m, vector<size_t> &initial, vector<size_t> &goal, size_t &empty_column, size_t &empty_row)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return false;
    }

    file >> n >> m;

    goal.resize(n * m);
    for (size_t i = 0; i < n * m; ++i)
    {
        file >> goal[i];
    }

    initial.resize(n * m);
    for (size_t i = 0; i < n * m; ++i)
    {
        file >> initial[i];
        if (initial[i] == 0)
        {
            empty_row = i / m;
            empty_column = i % m;
        }
    }

    file.close();
    return true;
}

void callSolvers(Board &initialBoard, const size_t &choice, const size_t &heuristic_choice)
{
    SearchStatistics stats;

    switch (choice)
    {
    case 0:
        cout << "Saindo do programa.\n";
        return;
    case 1:
        stats = BacktrackingStarter(initialBoard);
        break;
    case 2:
        stats = OrderSearch(initialBoard);
        break;
    case 3:
        stats = BreadthFirstSearch(initialBoard);
        break;
    case 4:
        stats = DepthFirstSearch(initialBoard);
        break;
    case 5:
        stats = GreedySearch(initialBoard, heuristic_choice);
        break;
    case 6:
        stats = IDAStarter(initialBoard, heuristic_choice);
        break;
    case 7:
        stats = AStarSearch(initialBoard, heuristic_choice);
        break;
    case 8:
        initialBoard.start_interactive_session();
        break;
    default:
        cout << "Opção inválida!\n";
    }

    print_statistics(stats);
}

int runCliApp(int argc, char *argv[])
{
    size_t n, m, empty_row = 0, empty_column = 0;

    Board initialBoard;

    if (argc > 1)
    {
        vector<size_t> initial;
        vector<size_t> goal;

        if (!loadBoardFromFile(argv[1], n, m, initial, goal, empty_column, empty_row))
        {
            cerr << "Erro ao carregar o tabuleiro do arquivo." << endl;
            return 1;
        }
        initialBoard = Board(n, m, initial, goal, empty_row, empty_column);
        // initialBoard.print_board(initialBoard.real_board);
    }
    else
    {
        cout << "Digite o número de linhas do tabuleiro: ";
        cin >> n;
        cout << "Digite o número de colunas do tabuleiro: ";
        cin >> m;
        initialBoard = Board(n, m);
    }
    if(argc == 4){
        size_t choice = stoi(argv[2]);
        size_t heuristic_choice = stoi(argv[3]);
        callSolvers(initialBoard, choice, heuristic_choice);
        return 0;
    }
    size_t choice;
    do{
        cout << "Selecione o algoritmo:\n";
        cout << "1 - Backtracking\n";
        cout << "2 - Order\n";
        cout << "3 - BFS\n";
        cout << "4 - DFS\n";
        cout << "5 - Greedy Search\n";
        cout << "6 - IDA* Search\n";
        cout << "7 - A* Search\n";
        cout << "8 - Interação manual\n";
        cout << "0 - Sair\n";

        cin >> choice;

        size_t heuristic_choice = 0;
        
        if (choice == 5 || choice == 6 || choice == 7)
        {
            cout << "Selecione a heurística:\n";
            cout << "1 - Manhattan\n";
            cout << "2 - Euclidean\n";
            cout << "3 - Misplaced Tiles\n";
            cout << "4 - Linear Conflict\n";
            cout << "5 - Permutation Cycles\n";
            cout << "6 - Weighted Sum\n";
            cin >> heuristic_choice;

            switch (heuristic_choice)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                cout << "Heurística inválida!\n";
                return 1;
            }
        }

        callSolvers(initialBoard, choice, heuristic_choice);
    }while (choice != 0);

    return 0;
}