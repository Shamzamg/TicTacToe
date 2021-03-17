#include <iostream>
#include <stdlib.h>
#include <math.h> 

using namespace std;

const char EMPTY = '-';
char grid[3][3] = {{EMPTY, EMPTY, EMPTY},{EMPTY, EMPTY, EMPTY},{EMPTY, EMPTY, EMPTY}};
char player = 'O';
char winnerPlayer = '-';
int index;

void showGrid() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool boardFull(){
    int count = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(grid[i][j] != EMPTY) count++;
        }
    }
    return count == 9;
}

char winner(){
    char winner = NULL;

    for(int i=0;i<3;i++){
        //horizontal
        if(grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]){
            return grid[i][0];
        }
        //vertical
        if(grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]){
            return grid[0][i];
        }
    }

    //diagonal
    if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]){
        return grid[0][0];
    }

    if(grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2]){
        return grid[2][0];
    }

    if(boardFull()){
        return 'draw';
    }

    return winner;
}

int minimax(bool tag){
    int minValue = -9999;
    int maxValue = 9999;
    int i,j,value = 1;

    switch(winner()){

        case 'O':
            if('O' == player){
                return 10;
            }
            return -10;

        case 'X':
            if('X' == player){
                return 10;
            }
            return -10;

        case 'draw':
            return 0;

        //if we go there, winner() returns NULL meaning there are no winners at the moment
        default:
            break;
    }

    int score[3][3] = {{EMPTY, EMPTY, EMPTY},{EMPTY, EMPTY, EMPTY},{EMPTY, EMPTY, EMPTY}};

}

bool gameEnd() {
    int count = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(grid[i][j] != EMPTY) count++;
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