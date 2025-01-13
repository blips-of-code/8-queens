//---------------------------------------------------------------------

// Name: Sharmin Zaman

// Project: Programming Assignment 3 - CS 321

// Purpose: To create a program that can solve

// the queens problem

// Date: 3/8/2023

//---------------------------------------------------------------------
#include <iostream>

using namespace std;

class ChessBoard {
public:
    ChessBoard();    // 8 x 8 chessboard;
    ChessBoard(int); // n x n chessboard;
    void findSolutions();

private:
    const bool available;
    const int squares, norm;
    bool *column, *leftDiagonal, *rightDiagonal;
    int  *positionInRow, howMany, boardConfigurations;
    void putQueen(int);
    void printBoard(ostream&);
    void initializeBoard();
};

ChessBoard::ChessBoard() : available(true), squares(8), norm(squares-1) {
    initializeBoard();
}
ChessBoard::ChessBoard(int n) : available(true), squares(n), norm(squares-1) {
    initializeBoard();
}
void ChessBoard::initializeBoard() {
    register int i;
    column = new bool[squares];
    positionInRow = new int[squares];
    leftDiagonal  = new bool[squares*2 - 1];
    rightDiagonal = new bool[squares*2 - 1];
    for (i = 0; i < squares; i++)
        positionInRow[i] = -1;
    for (i = 0; i < squares; i++)
        column[i] = available;
    for (i = 0; i < squares*2 - 1; i++)
        leftDiagonal[i] = rightDiagonal[i] = available;
    howMany = 0;
    boardConfigurations = 0;
}
void ChessBoard::printBoard(ostream& out) {
    howMany++;
    for (int row = 0; row < squares; row++) { //for each row
        for (int col=0; col < squares; col++) { //for each column
            if (howMany==1) { //just show the first solution found
                if (positionInRow[row]==col) { //if positioninrow[currentRow] == currentColumn,
                    cout << "Q"; //print Q
                }
                else if ((row+col)%2==0) { //if currentRow + currentColumn is even,
                    cout << "X";  //print X
                }
                else {
                    cout << ".";
                }
            }

        } //end inner for loop
        cout << "\n"; //end of the row
    } //end outer for loop
}
void ChessBoard::putQueen(int row) {
    for (int col = 0; col < squares; col++)
        if (column[col] == available &&
            leftDiagonal [row+col] == available &&
            rightDiagonal[row-col+norm] == available) {
            positionInRow[row] = col;
            column[col] = !available;
            leftDiagonal[row+col] = !available;
            rightDiagonal[row-col+norm] = !available;
            if (row < squares-1)
                putQueen(row+1);
            else printBoard(cout);
            column[col] = available;
            leftDiagonal[row+col] = available;
            rightDiagonal[row-col+norm] = available;
        }
    boardConfigurations++;
}
void ChessBoard::findSolutions() {
    putQueen(0);
    cout << howMany << " solutions found.\n";
    cout << boardConfigurations << " board configurations.\n"; //display number of board configurations
}

int main() {
    int n;
    string option;
    do {
        cout << "Enter a value for n from 4 to 10: " << endl;
        cin >> n;
        ChessBoard board(n);
        board.findSolutions();
        cout << "Would you like to enter another value? If not, enter x to exit" << endl; //asks user if they want to rerun the search
        cin >> option;
    } while(option!="x");
    return 0;
}
