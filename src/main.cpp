#include "../include/defines.hpp"
#include "../include/board.hpp"
#include "../include/bfs.hpp"
#include "../include/dfs.hpp"
#include "../include/backtracking.hpp"
#include "../include/order.hpp"

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

    int choice;
    cin >> choice;

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
    default:
        cout << "Opção inválida!\n";
    }

    return 0;
}
