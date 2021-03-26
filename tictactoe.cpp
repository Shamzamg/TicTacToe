#include<iostream>

using namespace std;

int index1; //index of where the minimax algorithm will play
bool game = true; //used for the main loop
char grid[3][3] = {{'_','_','_'},{'_','_','_'},{'_','_','_'}}; //empty grid at first

//returns true if the grid is full, false elseway
bool gridFull()
{
    for(int i=0;i<3;i++){
        for(int j=0; j<3;j++){
            if(grid[i][j] != 'X'){
                if(grid[i][j] != 'O'){
                    return false;
                }
            }
        }
    }
    return true;
}

bool isEmpty(char gridItem){
    return gridItem == '_';
}

//display the grid
void showGrid()
{
    for(int i=1;i<=9;i++){
        if((i-1)%3==0) cout << endl;
        cout << grid[(i-1)/3][(i-1)%3] << " ";
    }
    cout << endl << endl;
}

//get the winner depending on an integer
int getWinner(char winner){
    if(winner == 'O') return 1;
    if(winner == 'X') return 2;
}


//returns a number depending on the state of the game 
int gameEnd(){
    int winner = 999;

    for(int i=0;i<3;i++){
        //horizontal
        if(grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && !(isEmpty(grid[i][0]))){
            return getWinner(grid[i][0]);
        }
        //vertical
        if(grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && !(isEmpty(grid[0][i]))){
            return getWinner(grid[0][i]);
        }
    }

    //diagonal
    if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && !(isEmpty(grid[2][2]))){
        return getWinner(grid[0][0]);
    }

    if(grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] && !(isEmpty(grid[2][0]))){
        return getWinner(grid[2][0]);
    }

    //means it is a draw
    if(gridFull()){
        return 3;
    }

    return winner;
}

//the minimax function
int minimax(bool isMaximizing)
{

    int maxValue = -9999;
    int minValue = 9999;
    int i,j,value = 1;

    switch(gameEnd()){
        case 1:
            return -100;
        case 2:
            return 100;
        case 0:
            return 0;
        default:
            break;
    }

    int score[3][3] = {{1,1,1},{1,1,1},{1,1,1}};//1 means empty

    for(i=1;i<=9;i++)
        {
                if(isEmpty(grid[(i-1)/3][(i-1)%3]))
            {
                if(minValue > maxValue) 
                {
                    if(isMaximizing)
                {
                    grid[(i-1)/3][(i-1)%3] = 'X';
                    value = minimax(false);
                }
                else
                {
                    grid[(i-1)/3][(i-1)%3] = 'O';
                    value = minimax(true);
                }
                grid[(i-1)/3][(i-1)%3] = '_';
                score[(i-1)/3][(i-1)%3] = value;
                }
            }
        }

    if(isMaximizing){
        maxValue = -9999;
        for(j=1;j<=9;j++){
            if(score[(j-1)/3][(j-1)%3] > maxValue && score[(j-1)/3][(j-1)%3] != 1)
            {
                maxValue = score[(j-1)/3][(j-1)%3];
                index1 = j;
            }
        }
        return maxValue;
    }
    else{
        minValue = 9999;
        for(j=1;j<=9;j++)
        {
            if(score[(j-1)/3][(j-1)%3] < minValue && score[(j-1)/3][(j-1)%3] != 1)
            {
                minValue = score[(j-1)/3][(j-1)%3];
                index1 = j;
            }
        }
        return minValue;
    }
}

//called to check whether a move is incorrect or not
bool moveIncorrect(char move){
    if(move < 1 || move > 9) {
        cout << "The move you chose was not in 1-9 range" << endl;
        return true;
    }
    return false;
}

//try to make a move and returns a boolean
bool makeMove(char player, int move){
    if(isEmpty(grid[(move-1)/3][(move-1)%3])){
        grid[(move-1)/3][(move-1)%3] = player;
        return true;
    }
    cout << "The move is invalid !" << endl;
    return false;
}

//ask user to play
void userPlay(){
    int move;

    do{
        cout<<endl<<"Enter the move:";
        cin>>move;
    } while(!makeMove('O', move));

    showGrid();
}

//is called once at the beginning to know whether the computer plays first or not
void firstMove(){
   int move,choice;

    //check if input is right
    do {
        cout << "You: 'O'        Computer: 'X' " << endl;
        cout << "Press : 1 to play first;  2 for the computer first: " << endl;
        cin >> choice;
        if(cin.fail()) { // check to avoid while loops and errors
            cin.clear();
            cin.ignore(1);
            choice = -1;
        }
    } while(!(choice == 1 || choice == 2)); // while the input is incorrect

   if(choice == 1)
   {
        do{  
            showGrid();
            cout << "Enter the move (1-9):" << endl;
            cin >> move;

        } while(moveIncorrect(move));

        if(isEmpty(grid[(move-1)/3][(move-1)%3])){
            grid[(move-1)/3][(move-1)%3] = 'O';
            showGrid();
        }

   }
}

//Check if the game finished
void checkGameEnd(){
    switch(gameEnd()){
        case 1:
            game = false;
            cout << "You won ! " << endl;
            break;
        case 2:
            game = false;
            cout << "Computer won !" << endl;
            break;
        case 3:
            game = false;
            cout << "Draw ! " << endl;
            break;
        default:
            break;
    }
}

void play(){
    firstMove();

    while(game)
    {
        //The computer plays
        cout << "Computer is playing: " << endl;

        minimax(true);
        makeMove('X', index1);

        showGrid();

        //Check if the game ended after the computer played
        checkGameEnd();

        if(!game) break;

        //The user plays
        userPlay();

        checkGameEnd();
    }
}

int main()
{
    play();

    return 0;
}