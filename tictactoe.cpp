#include <iostream>
#include <stdlib.h>
#include <math.h> 

using namespace std;

const char EMPTY = '-';
char grid[3][3] = {{EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}};
char player = EMPTY;

void showGrid() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool gameEnd() {
    int count = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(grid[i][j] == player) count++;
        }
    }
    return count == 9;
}

bool play(int move, char currentPlayer){
    if(move < 1 || move > 9){
        cout << "The move you chose was not in 1-9 range" << endl;
        return false;
    }

    int i = ceil(move/3);
    int j = ((move % 3) - 1)%3;

    //cout << i << " " << j  << " "<< endl;

    if(grid[i][j] == EMPTY) grid[i][j] = currentPlayer;

    else{
        cout << "The move you chose was already taken" << endl;
        return false;
    }
    return true;
}

void play(){
    while(!gameEnd()){
        int move;
        do {
            showGrid();
            cout << "Choose your move (integer 1-9)" << endl;
            cin >> move;
        } while(!play(move, player)); // Tant que le choix de la case n'est pas bon.
    }
    cout << "The game ended, the winner is ..." << endl;
}

int main(){

    cout << "Choose between circle or cross (type O for the circle and X for the cross)" << endl;
    cin >> player;

    play();

    return 0;
}