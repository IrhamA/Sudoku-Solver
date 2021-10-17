#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>

using namespace std; 

// print_board(sudoku board) 
//
// prints the board out for your viewing pleasure
void print_board(int b[9][9]) {    

    int row_len = 9;
    int col_len = 9;
    for (int i = 0; i < row_len; i++) {
        //  loop through columns and separate with --- line every 3 entries
        if ((i % 3 == 0) && (i != 0)) {
            printf("--------------------- \n");
        }

        for (int j = 0; j < col_len; j++) {

            if ((j % 3 == 0) && (j != 0)) {
                printf("| ");
            }
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
}

// valid(sudoku board, candidate number, entry on board)
//
// checks if the candidate number is valid based on the box,
// the row, and the column it is a part of returns true if so
bool valid(int b[9][9], int num, pair<int,int> pair) {

    int row = pair.first;
    int col = pair.second;

    // checks the row
    for (int i = 0; i < 9; i++) {
        if (b[row][i] == num && i != col) {
            return false;
        }
    }

    // checks the column
    for (int i = 0; i < 9; i++) {
        if (b[i][col] == num && i != row) {
            return false;
        }
    }

    // checks the box
    int x = row/3; // = 2
    int y = col/3; // = 3

    for (int i = 3*x; i < 3*x+3; i++ ) {
        for (int j = 3*y; j < 3*y+3; j++) {
            if (b[i][j] == num && (i != row) && (j != col)) {
                return false;
            }
        }
    }

    return true;
}

// find_empty(sudoku board)
//
// finds the first empty entry on the board (row, col)
bool find_empty(int b[9][9], pair<int,int> * p) {
    
    int row_len = 9;
    int col_len = 9;

    for (int i = 0; i < row_len; i++) {
        for (int j = 0; j < col_len; j++) {
            if (b[i][j] == 0) {
                *p = make_pair(i,j);
                return true;                
            }
        }
    }

    return false;
}

// solve(sudoku board)
//
// solves the valid sudoku with backtracing algorithm
bool solve(int b[9][9]) {

    // recurse with a new "board" each time
    
    pair<int,int> p;
    bool find = find_empty(b, &p);

    // base case
    // this will happen when there are no 0 entries on the board
    if (!find) {
        return true;
    }

    // entries of p
    int row = p.first;
    int col = p.second;

    // check all candidate entries 1-9 inclusive
    for (int i = 1; i < 10; i++) {
        if (valid(b, i, p)) {
            b[row][col] = i;
            if (solve(b)) {
                return true;
            }
            b[row][col] = 0;
        }
    }
    return false;    
}

/*int main() {

    int board[9][9] = {
    {0,0,5,3,0,0,0,0,0},
    {8,0,0,0,0,0,0,2,0},
    {0,7,0,0,1,0,5,0,0},
    {4,0,0,0,0,5,3,0,0},
    {0,1,0,0,7,0,0,0,6},
    {0,0,3,2,0,0,0,8,0},
    {0,6,0,5,0,0,0,0,9},
    {0,0,4,0,0,0,0,3,0},
    {0,0,0,0,0,9,7,0,0}
    };
    
    print_board(board);
    printf("\n--------------------- \n \n");
    solve(board);
    print_board(board);

    
    pair<int,int> p;
    find_empty(board, &p);
    printf("first: %d \n", p.first);
    printf("second: %d \n", p.second);
    

    return 0;
}*/

