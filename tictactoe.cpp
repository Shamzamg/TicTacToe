#include <iostream>
#include <stdlib.h>
#include <math.h> 

using namespace std;

const char EMPTY = '-';
char grid[3][3] = {{EMPTY, EMPTY, EMPTY},{EMPTY, EMPTY, EMPTY},{EMPTY, EMPTY, EMPTY}};
char player;
char computer;
char winnerPlayer = '-';
int index_i, index_j;

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

void checkWinner(char winner){
    if(winner == player){
        cout << "You won ! " << endl;
    }
    else if (winner == computer){
        cout << "The computer won !" << endl;
    }
    else{
        cout << "The game is a draw !" << endl;
    }
}


char winner(string condition){
    char winner = NULL;

    for(int i=0;i<3;i++){
        //horizontal
        if(grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[2][0] != EMPTY){
            if(condition == "verifMode")
                checkWinner(grid[i][0]);
            return grid[i][0];
        }
        //vertical
        if(grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[2][0] != EMPTY){
            if(condition == "verifMode")
                checkWinner(grid[0][i]);
            return grid[0][i];
        }
    }

    //diagonal
    if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[2][0] != EMPTY){
        if(condition == "verifMode")
            checkWinner(grid[0][0]);
        return grid[0][0];
    }

    if(grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] && grid[2][0] != EMPTY){
        if(condition == "verifMode")
            checkWinner(grid[2][0]);
        return grid[2][0];
    }

    if(boardFull()){
        if(condition == "verifMode")
            checkWinner('-');
        return 'draw';
    }

    return winner;
}

int minimax(bool tag){
    int minValue = -9999;
    int maxValue = 9999;
    int i,j,value = 1;

    switch(winner("minimaxMode")){

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

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(grid[i][j] == EMPTY){
                if(minValue > maxValue)
                    if(tag){
                        grid[i][j] = 'X';
                        value = minimax(false);
                    }
                    else{
                        grid[i][j] = 'O';
                        value = minimax(true);
                    }
                grid[i][j] = EMPTY;
                score[i][j] = value;
            }
        }
    }

    if(tag){
        maxValue = -9999;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(score[i][j] > maxValue && score[i][j] != EMPTY){
                    maxValue = score[i][j];
                    index_i = i;
                    index_j = j; 
                }
            }
        }
        return maxValue;
    }

    else{
        minValue = 9999;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(score[i][j] < maxValue && score[i][j] != EMPTY){
                    minValue = score[i][j];
                    index_i = i;
                    index_j = j; 
                }
            }
        }
        return minValue;
    }

}

bool gameEnd() {
    if(winner("verifMode") != NULL){
        showGrid();
        return true;
    }
    return false;
}

bool applyMove(int move, char currentPlayer) {
    if(move < 1 || move > 9) {
        cout << "The move you chose was not in 1-9 range" << endl;
        return false;
    }

    //non-elegant way to convert (1-9) to (1-3)x(1-3)
    int i = ceil(move/3);
    int j = ((move % 3) - 1)%3;

    if(grid[i][j] == EMPTY) grid[i][j] = currentPlayer;
    else {
        cout << "The move you chose was already taken" << endl;
        return false;
    }
    return true;
}

void choosePlayer(){

    cout << "Choose between circle or cross (type O for the circle and X for the cross)" << endl;
    cin >> player;

    if(player == 'O'){
        computer = 'X';
    }
    else{
        computer = 'O';
    }

}

void play() {

    choosePlayer();

    while(!gameEnd()) {
        //the player then plays
        int move;
        do {
            showGrid();
            cout << "Choose your move (integer 1-9)" << endl;
            cin >> move;
            if(cin.fail()) { // Solution temporaire pour empêcher une boucle infinie si l'utilisateur entre un charactère.
                cin.clear();
                cin.ignore(1);
                move = -1;
            }
        } while(!applyMove(move, player)); // Tant que le choix de la case n'est pas bon.

        //on verifie si la partie est finie
        if(gameEnd()){
            break;
        }

        //the computer plays
        minimax(true);
        grid[index_i][index_j] = computer;

    }
}

int main() {

    play();

    return 0;
}