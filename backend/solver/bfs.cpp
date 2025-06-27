#include <iostream>
#include <vector>
#include "../npuzzle/board.cpp"
#include "../npuzzle/list.cpp"
#include "../npuzzle/state.cpp"

using namespace std;

void BreadthFirstSearch(Board board) {
    size_t id = 0; // Inicializa o ID do estado
    List openList = List(); // Lista de estados abertos
    List closedList = List(); // Lista de estados fechados
    State* initialState = new State(id, 0, 0, nullptr, board); // Estado inicial
    id++; // Incrementa o ID para o próximo estado
    openList.add(initialState); // Adiciona o estado inicial à lista aberta
    while (openList.is_not_empty()) { // Enquanto houver estados na lista aberta
        State* currentState = openList.get_head(); // Obtém o estado atual
        openList.remove(currentState); // Remove o estado atual da lista aberta
        closedList.add(currentState); // Adiciona o estado atual à lista fechada

        if (currentState->get_depth() > 10000) { // Verifica se o estado atual é o objetivo
            cout << "Solução encontrada!" << endl;
            return; // Encerra a busca se a solução for encontrada
        }

        // Gera os sucessores do estado atual e os adiciona à lista aberta
        for (char direction : {'U', 'D', 'L', 'R'}) {
            Board newBoard = currentState->get_board(); // Cria uma cópia do tabuleiro atual
            if (newBoard.move(direction)) { // Tenta mover na direção especificada
                State* successor = new State(id, currentState->get_cost() + 1, currentState->get_depth() + 1, currentState, newBoard);
                id++; // Incrementa o ID para o próximo sucessor
                // Verifica se o sucessor já está na lista fechada
                bool alreadyInClosedList = false;
                State* closedState = closedList.get_head();
                while (closedState != nullptr) {
                    if (closedState->get_board().real_board == successor->get_board().real_board) { // TODO: Atualizar essa igualdade para reduzir custo computacional
                        alreadyInClosedList = true; // O sucessor já está na lista fechada
                        break;
                    }
                    closedState = closedState->get_next(); // Avança para o próximo estado na lista
                }
                if (alreadyInClosedList) {
                    delete successor; // Libera a memória do sucessor se já estiver na lista fechada
                    continue; // Pula para o próximo sucessor
                }
                // Verifica se o sucessor já está na lista aberta
                bool alreadyInOpenList = false;
                State* openState = openList.get_head();
                while (openState != nullptr) {
                    if (openState->get_board().real_board == successor->get_board().real_board) { // TODO: Atualizar essa igualdade para reduzir custo computacional
                        alreadyInOpenList = true; // O sucessor já está na lista aberta
                        break;
                    }
                }
                if(alreadyInOpenList){
                    delete successor; // Libera a memória do sucessor se já estiver na lista aberta
                    continue; // Pula para o próximo sucessor
                }
                openList.add(successor); // Adiciona o sucessor à lista aberta
            }
        }
    }
}