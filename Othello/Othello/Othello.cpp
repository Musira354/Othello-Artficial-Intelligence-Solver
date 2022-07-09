// Othello.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

int rowSize = 8;
int colSize = 8;
int POSSIBLEMOVE[2];


using namespace std;

struct Coordinates
{
    double x, y;

    Coordinates(double paramx, double paramy) : x(paramx), y(paramy) {}
};


std::vector<Coordinates> firstPlayerMoves;
std::vector<Coordinates> secondPlayerMoves;

void pushMoves(int x, int y, int player);
bool possibleMoveUp(int  board[8][8], int player,  int position[2]);
bool possibleMoveDown(int  board[8][8], int player,  int position[2]);
bool possibleMoveRight(int  board[8][8], int player,  int position[2]);
bool possibleMoveLeft(int  board[8][8], int player,  int position[2]);
bool possibleMoveRightDownDigonal(int  board[8][8], int player,  int position[2]);
bool possibleMoveLeftDownDigonal(int  board[8][8], int player, int position[2]);
bool possibleMoveLeftUpDigonal(int  board[8][8], int player,  int position[2]);
bool possibleMoveRightUpDigonal(int  board[8][8], int player,  int position[2]);


bool makeMoveDown(int board[8][8],int player,int position[2]);
bool makeMoveUp(int board[8][8],int player,int position[2]);
bool makeMoveRight(int board[8][8],int player,int position[2]);
bool makeMoveLeft(int board[8][8], int player, int position[2]);
bool makeMoveLeftUpDigonal(int board[8][8], int player, int position[2]);
bool makeMoveRightUpDigonal(int board[8][8], int player, int position[2]);
bool makeMoveLeftDownDigonal(int board[8][8], int player, int position[2]);
bool makeMoveRightDownDigonal(int board[8][8],int player,int position[2]);

bool isTouchingBoundary(int x);

void intializeBoardValues(int b[8][8]) {

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            b[i][j] = 0;
        }
    }
    
    int row = (rowSize-1) / 2, col = (colSize-1) / 2;
    b[row][col] = 1;
    b[row+1][col] = 2;
    b[row][col+1] = 2;
    b[row+1][col+1] = 1;

}

void removeSuggestions(int board[8][8]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 3) {
                board[i][j] = 0;
            }
        }
    }
}

void printBoard(int b[8][8]) {

    char player1 = 'X';
    char player2 = 'O';

    cout << "         0    1     2     3     4     5     6     7"<<endl;
    cout << "      -----------------------------------------------"<<endl;

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {

            if (j == 0) { 
                if (b[i][j] == 1) {
                    cout << "   " << i << "  |  " << player1 << " |";
                }
                else if (b[i][j] == 2) {
                    cout << "   " << i << "  |  " << player2 << " |";
                }
                else if (b[i][j] == 3) {
                    cout << "   " << i << "  |  " << "*" << " |";
                }
                else if (b[i][j] == 0) {
                    cout << "   " << i << "  |  " << " " << " |";
                }
                
            }
            else {
                if (b[i][j] == 1) {
                    cout << "  " << player1 << " | ";
                }
                else if (b[i][j]==2) {
                    cout << "  " << player2 << " | ";
                }
                else if (b[i][j] == 3) {
                    cout << "  " << '*' << " | ";
                }
                else if (b[i][j] == 0) {
                    cout << "  " << " " << " | ";
                }
            }

        }
        cout <<endl<< "      -----------------------------------------------" << endl;    
    }
    cout << endl;
}

void ShiftPlayerTurn(int &player) {
    if (player == 1) {
        player = 2;
    }
    else if (player == 2) {
        player = 1;
    }
}

void makeMove(int board[8][8], int& player, int row, int col) {

    if (board[row][col] ==3) {
        board[row][col] = player;
    }
    int position[2];
    position[0] = row;
    position[1] = col;

    makeMoveDown(board, player, position);
    makeMoveUp(board, player, position);
    makeMoveRight(board, player, position);
    makeMoveLeft(board, player, position);
    makeMoveLeftUpDigonal(board, player, position);
    makeMoveRightUpDigonal(board, player, position);
    makeMoveLeftDownDigonal(board, player, position);
    makeMoveRightDownDigonal(board, player, position);

   
}

void playerTurn(int board[8][8], int &player, int move[2]) {
    int row = 0, col = 0;
    cout << "Player " << player << " turn!";
    cout << endl << "Enter row = ";
    cin >> row;
    cout << endl << "Enter col = ";
    cin >> col;

    makeMove(board, player, row, col);

    //store move in 
    move[0] = row; move[1] = col;
    printBoard(board);
}

void copyBoard(int copyBoard[8][8], int board[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            copyBoard[i][j] = board[i][j];
        }
    }
}

int oponent(int player) {
    if (player == 1) { return 2; }
    if (player == 2) { return 1; }
    return 0;
}

void possibleMoves(int  board[8][8], int player, int move[2],  int position[2]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == player) {
                //set position to the found player plate
                position[0] = i;
                position[1] = j;

                //checks for the possible move for the current player's plate
                if (possibleMoveUp(board, player,  position) == true) {
                    cout << "possible move at " << POSSIBLEMOVE[0] << " " << POSSIBLEMOVE[1];
                    cout << " for plate at " << i << " " << j<<endl;
                    board[POSSIBLEMOVE[0]][POSSIBLEMOVE[1]] = 3;
                    
                    //pushing the moves in the vector
                    pushMoves(POSSIBLEMOVE[0], POSSIBLEMOVE[1], player);
                 
                }

                if (possibleMoveDown(board, player,  position) == true) {
                    cout << "possible move at " << POSSIBLEMOVE[0] << " " << POSSIBLEMOVE[1];
                    cout << " for plate at " << i << " " << j<<endl;
                    board[POSSIBLEMOVE[0]][POSSIBLEMOVE[1]] = 3;

                    //pushing the moves in the vector
                    pushMoves(POSSIBLEMOVE[0], POSSIBLEMOVE[1], player);

                }
                if (possibleMoveLeft(board, player, position) == true) {
                    cout << "possible move at " << POSSIBLEMOVE[0] << " " << POSSIBLEMOVE[1];
                    cout << " for plate at " << i << " " << j << endl;
                    board[POSSIBLEMOVE[0]][POSSIBLEMOVE[1]] = 3;

                    //pushing the moves in the vector
                    pushMoves(POSSIBLEMOVE[0], POSSIBLEMOVE[1], player);

                }
                if (possibleMoveRight(board, player,  position) == true) {
                    cout << "possible move at " << POSSIBLEMOVE[0] << " " << POSSIBLEMOVE[1];
                    cout << " for plate at " << i << " " << j << endl;
                    board[POSSIBLEMOVE[0]][POSSIBLEMOVE[1]] = 3;

                    //pushing the moves in the vector
                    pushMoves(POSSIBLEMOVE[0], POSSIBLEMOVE[1], player);

                }
                if (possibleMoveRightDownDigonal(board, player, position) == true) {
                    cout << "possible move at " << POSSIBLEMOVE[0] << " " << POSSIBLEMOVE[1];
                    cout << " for plate at " << i << " " << j << endl;
                    board[POSSIBLEMOVE[0]][POSSIBLEMOVE[1]] = 3;

                    //pushing the moves in the vector
                    pushMoves(POSSIBLEMOVE[0], POSSIBLEMOVE[1], player);

                }
                if (possibleMoveLeftDownDigonal(board, player,  position) == true) {
                    cout << "possible move at " << POSSIBLEMOVE[0] << " " << POSSIBLEMOVE[1];
                    cout << " for plate at " << i << " " << j << endl;
                    board[POSSIBLEMOVE[0]][POSSIBLEMOVE[1]] = 3;

                    //pushing the moves in the vector
                    pushMoves(POSSIBLEMOVE[0], POSSIBLEMOVE[1], player);

                }if (possibleMoveRightUpDigonal(board, player,  position) == true) {
                    cout << "possible move at " << POSSIBLEMOVE[0] << " " << POSSIBLEMOVE[1];
                    cout << " for plate at " << i << " " << j << endl;
                    board[POSSIBLEMOVE[0]][POSSIBLEMOVE[1]] = 3;

                    //pushing the moves in the vector
                    pushMoves(POSSIBLEMOVE[0], POSSIBLEMOVE[1], player);

                }
                if (possibleMoveLeftUpDigonal(board, player, position) == true) {
                    cout << "possible move at " << POSSIBLEMOVE[0] << " " << POSSIBLEMOVE[1];
                    cout << " for plate at " << i << " " << j << endl;
                    board[POSSIBLEMOVE[0]][POSSIBLEMOVE[1]] = 3;

                    //pushing the moves in the vector
                    pushMoves(POSSIBLEMOVE[0], POSSIBLEMOVE[1], player);

                }
            }
            
        }
    }
    
}

bool isTouchingCorner(int x, int y) {
    if ((x == 0 && y == 7) || (x == 0 && y == 0) || (x == 7 && y == 0) || (x == 7 && y == 7)) {
        return true;
    }
    return false;
}

void pushMoves(int x, int y, int player) {
    if (player == 1){
        firstPlayerMoves.push_back(Coordinates(x, y));
    }
    else if (player == 2) {
        secondPlayerMoves.push_back(Coordinates(x, y));
    }
}

void removesPushes(int player) {
    if (player == 1) {
        while (!firstPlayerMoves.empty()) {
            firstPlayerMoves.pop_back();
        }
    }
    else if (player == 2) {
        while (!secondPlayerMoves.empty()) {
            secondPlayerMoves.pop_back();
        }
    }
}

bool possibleMoveRightUpDigonal(int  board[8][8], int player,  int position[2]) {
    int row = position[0], col = position[1];

    if (board[row - 1][col + 1] == oponent(player)) {
        row--; col++;
        //move
        while (row > 0 && col<7 && board[row - 1][col+1] == oponent(player)) {
            row--; col++;
            if (isTouchingCorner(row,col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row-1 ][col+1] == 0) {
            //this means that our player can make a move here
            row--;
            col++;
            POSSIBLEMOVE[0] = row;
            POSSIBLEMOVE[1] = col;

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool makeMoveRightUpDigonal(int  board[8][8], int player, int position[2]) {
    int row = position[0], col = position[1];

    if (board[row - 1][col + 1] == oponent(player)) {
        row--; col++;
        //move
        while (row > 0 && col < 7 && board[row - 1][col + 1] == oponent(player)) {
            row--; col++;
            if (isTouchingCorner(row, col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row - 1][col + 1] == player) {
            //this means that our player can make a move here
            row--;
            col++;

            while (row < 7 && col > 0 && board[row + 1][col - 1] == oponent(player)) {
                row++; col--;
                board[row][col] = player;   //flip oponent plate to player's plate
                if (board[row][col]==player) { //if player finds it's own plate then fliping done
                    break;
                }
            }

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool possibleMoveLeftUpDigonal(int  board[8][8], int player,  int position[2]) {
    int row = position[0], col = position[1];

    if (board[row - 1][col - 1] == oponent(player)) {
        row--; col--;
        //move
        while (isTouchingCorner(row,col)==false && board[row - 1][col - 1] == oponent(player)) {
            row--; col--;
            if (isTouchingCorner(row, col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row - 1][col - 1] == 0) {
            //this means that our player can make a move here
            row--;
            col--;
            POSSIBLEMOVE[0] = row;
            POSSIBLEMOVE[1] = col;
            pushMoves(row, col, player);

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool makeMoveLeftUpDigonal(int  board[8][8], int player, int position[2]) {
    int row = position[0], col = position[1];

    if (board[row - 1][col - 1] == oponent(player)) {
        row--; col--;
        //move
        while (isTouchingCorner(row, col) == false && board[row - 1][col - 1] == oponent(player)) {
            row--; col--;
            if (isTouchingCorner(row, col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row - 1][col - 1] == player) {
            //this means that our player can make a move here
            row--;
            col--;
            while (isTouchingCorner(row, col) == false && board[row + 1][col + 1] == oponent(player)) {
                row++; col++;   //goes reverse
                board[row][col] = player;   //flip oponent plate to player's plate
              
            }

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool possibleMoveLeftDownDigonal(int  board[8][8], int player,  int position[2]) {
    int row = position[0], col = position[1];

    if (board[row + 1][col - 1] == oponent(player)) {
        row++; col--;
        //move
        while (isTouchingCorner(row, col) == false && board[row + 1][col - 1] == oponent(player)) {
            row++; col--;
            if (isTouchingCorner(row, col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row + 1][col - 1] == 0) {
            //this means that our player can make a move here

            row++;
            col--;
            POSSIBLEMOVE[0] = row;
            POSSIBLEMOVE[1] = col;
            pushMoves(row, col, player);

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool makeMoveLeftDownDigonal(int  board[8][8], int player, int position[2]) {
    int row = position[0], col = position[1];

    if (board[row + 1][col - 1] == oponent(player)) {
        row++; col--;
        //move
        while (isTouchingCorner(row, col) == false && board[row + 1][col - 1] == oponent(player)) {
            row++; col--;
            if (isTouchingCorner(row, col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row + 1][col - 1] == player) {
            //this means that our player can make a move here

            row++;
            col--;
            while (isTouchingCorner(row, col) == false && board[row - 1][col + 1] == oponent(player)) {
                row--; col++;   //goes reverse
                board[row][col] = player;   //flip oponent plate to player's plate
               
            }

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool possibleMoveRightDownDigonal(int  board[8][8], int player, int position[2]) {
    int row = position[0], col = position[1];

    if (board[row + 1][col + 1] == oponent(player)) {
        row++; col++;
        //move
        while (isTouchingCorner(row, col) == false && board[row +1][col + 1] == oponent(player)) {
            row++; col++;
            if (isTouchingCorner(row, col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row + 1][col + 1] == 0) {
            //this means that our player can make a move here

            row++;
            col++;
            POSSIBLEMOVE[0] = row;
            POSSIBLEMOVE[1] = col;
            pushMoves(row, col, player);

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool makeMoveRightDownDigonal(int  board[8][8], int player,  int position[2]) {
    int row = position[0], col = position[1];

    if (board[row + 1][col + 1] == oponent(player)) {
        row++; col++;
        //move
        while (isTouchingCorner(row, col) == false && board[row + 1][col + 1] == oponent(player)) {
            row++; col++;
            if (isTouchingCorner(row, col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row + 1][col + 1] == player) {
            //this means that our player can make a move here
            row++;
            col++;
            while (isTouchingCorner(row, col) == false && board[row - 1][col - 1] == oponent(player)) {
                row--; col--;
                board[row][col] = player;
            }

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool possibleMoveUp(int  board[8][8], int player,  int position[2]) {
    int row = position[0], col = position[1];

    if ( board[row - 1][col] == oponent(player)) {
        row--;
        //move
        while (row >0 && board[row - 1][col] == oponent(player) ) {
            row--;
            if (isTouchingBoundary(row)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row - 1][col] == 0) {
            //this means that our player can make a move here

            row--;
            POSSIBLEMOVE[0] = row;
            POSSIBLEMOVE[1] = col;
            pushMoves(row, col, player);
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool makeMoveUp(int  board[8][8], int player, int position[2]) {
    int row = position[0], col = position[1];

    if (board[row - 1][col] == oponent(player)) {
        row--;
        //move
        while (row > 0 && board[row - 1][col] == oponent(player)) {
            row--;
            if (isTouchingBoundary(row)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row - 1][col] == player) {
            //this means that our player can make a move here

            row--;
            while (!isTouchingBoundary(row) && board[row + 1][col] == oponent(player)) {
                row++;  //reversse
                board[row][col] = player;
            }
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool possibleMoveDown(int  board[8][8], int player,  int position[2]) {
    int row = position[0], col = position[1];

    if (board[row + 1][col] == oponent(player)) {
        row++;
        //move
        while (row < 7 && board[row + 1][col] == oponent(player)) {
            row++;
            if (isTouchingBoundary(row)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row + 1][col] == 0) {
            //this means that our player can make a move here

            row++;
            POSSIBLEMOVE[0] = row;
            POSSIBLEMOVE[1] = col;
            pushMoves(row, col, player);
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool makeMoveDown(int  board[8][8], int player, int position[2]) {
    int row = position[0], col = position[1];

    if (board[row + 1][col] == oponent(player)) {
        row++;
        //move
        while (isTouchingBoundary(row) && board[row + 1][col] == oponent(player)) {
            row++;
            if (isTouchingBoundary(row)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row + 1][col] == player) {
            //this means that our player can make a move here
            row++;
            while (!isTouchingBoundary(row) && board[row - 1][col] == oponent(player)) {
                row--;
                board[row][col] = player;   //flips
            }
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool possibleMoveLeft(int  board[8][8], int player,  int position[2]) {
    int row = position[0], col = position[1];

    if (board[row ][col-1] == oponent(player)) {
        col--;
        //move
        while (col > 0 && board[row][col-1] == oponent(player)) {
            col--;
            if (isTouchingBoundary(col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row][col-1] == 0) {
            //this means that our player can make a move here

            col--;
            POSSIBLEMOVE[0] = row;
            POSSIBLEMOVE[1] = col;
            pushMoves(row, col, player);

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool makeMoveLeft(int  board[8][8], int player, int position[2]) {
    int row = position[0], col = position[1];

    if (board[row][col - 1] == oponent(player)) {
        col--;
        //move
        while (col > 0 && board[row][col - 1] == oponent(player)) {
            col--;
            if (isTouchingBoundary(col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row][col - 1] == player) {
            //this means that our player can make a move here

            col--;
            while (!isTouchingBoundary(col) && board[row][col + 1] == oponent(player)) {
                col++;
                board[row][col] = player;
            }

            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool isTouchingBoundary(int x) {
    if (x == 0 || x == 7) {
        return true;
    }
   
    return false;
}

bool possibleMoveRight(int  board[8][8], int player,  int position[2]) {
    int row = position[0], col = position[1];

    if (board[row ][col + 1] == oponent(player)) {
        col++;
        //move
        while (col > 0 && board[row][col + 1] == oponent(player)) {
            col++;
            if (isTouchingBoundary(col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row][col+1] == 0) {
            //this means that our player can make a move here
            col++;
            POSSIBLEMOVE[0] = row;
            POSSIBLEMOVE[1] = col;
            pushMoves(row, col, player);
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool makeMoveRight(int  board[8][8], int player, int position[2]) {
    int row = position[0], col = position[1];

    if (board[row][col + 1] == oponent(player)) {
        col++;
        //move
        while (col > 0 && board[row][col + 1] == oponent(player)) {
            col++;
            if (isTouchingBoundary(col)) { //oponent till the edge return false no possible move
                return false;
            }
        }
        if (board[row][col + 1] == player) {
            col++;
            //flip oponents plates
            while (col > 0 && board[row][col - 1] == oponent(player)) {
                col--;  //traverse reverse to track back
                board[row][col] = player;
            }
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool isGameOver(char board[8][8]) {
   // return blackMoves.empty() && getWhiteLegalMoves(board).empty();
    return firstPlayerMoves.empty() && secondPlayerMoves.empty();
}

// go through whole board, and count pieces of passed-in player
int getScore(int board[8][8], int player) {
    int total = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (board[i][j] == player)
                total += 1;

    return total;
}

void printWinner(int board[8][8], int player) {
    int firstPlayerTotal = getScore(board,  player);
    int secondPlayerTotal = getScore(board, player);

    std::cout << "X total: " << firstPlayerTotal << '\n';
    std::cout << "O total: " << secondPlayerTotal << '\n';
    if (firstPlayerTotal == secondPlayerTotal) {
        cout << "TIE GAME\n";
        return;
    }

    std::cout << ((firstPlayerTotal > secondPlayerTotal) ? "firstPlayer" : "secondPlayer") << " wins!\n";
}

int main()
{
    int board[8][8];
    intializeBoardValues(board);
    
    bool Game = true;
    int player = 2;
    int move[2];
    int position[2];

    
    while(Game) {
        possibleMoves(board, player, move, position);
        printBoard(board);
        playerTurn(board, player, move);
        ShiftPlayerTurn(player);
        removeSuggestions(board);
        removesPushes(player);
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
