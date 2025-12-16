#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

/*
From any (possibly partial) position, we need to be able to find the next legal
position. There are, perhaps, three cases here. First, the next legal position
from an illegal partial position; second, the next legal position from a legal
partial position, and third, the next legal position after a full-fledged solution.
*/

int getNextRow(int n, int board[n][n], int row) {
    int answer = row;
    int col = -1;

    // check current row
    for (int i = 0; i < n; i++) {
        if (board[row][i] == 1) {
            col = i;
        }
    }

    // if not found, move up a row and check again
    if (col == -1) {
        answer = getNextRow(n, board, row - 1);
    }

    // if we get here, we found the last queen
    return answer;
}

int getCol(int n, int board[n][n], int row) {
    for (int i = 0; i < n; i++) {
        if (board[row][i] == 1) {
            return i;
        }
    }
    return -1;
}

int nextLegalPosition(int n, int board[n][n], int row) {
    int nextRow = getNextRow(n, board, n - 1);

    // if the board is legal and not full:
    if (nextRow < (n - 1) && isLegalPosition(n, board)) {
        // call the function on a new row
        return getNextLegalPosition(n, board, nextRow + 1);
    }

    // otherwise, call the function on the given row (this means that the board is either illegal or legal and full)
    return getNextLegalPosition(n, board, nextRow);
}

int getNextLegalPosition(int n, int board[n][n], int row) {
    // gets the first row with a queen in it from bottom to top
    // check if row is empty
    int col = -1;
    for (int i = 0; i < n; i++) {
        if (board[row][i] == 1) col = i;
    }

    // if row is empty:
    if (col == -1) {
        // place a queen in the first column that is not threatened by any other queen
        for (int i = 0; i < n; i++) {
            if (!isThreatened(n, board, row, i)) {
                board[row][i] = 1;
                return 1;   // return 1 to indicate that the position is legal
            }
        }

        // if the queen could not be placed, then we remove the previous queen and try again in the previous row
        int previousRow = getNextRow(n, board, row - 1);
        int previousCol = getCol(n, board, previousRow);
        board[previousRow][previousCol] = 0;    // remove the previous queen
        return getNextLegalPosition(n, board, row - 1);   // call the function on the previous row
    }

    // otherwise, if the row is not empty:
    int queenRow = row;
    int queenCol = getCol(n, board, row);

    // remove the queen
    board[queenRow][queenCol] = 0;

    // try placing a queen in each col in the current row
    for (int i = col; i < n; i++) {   
        // check if queen can be placed on square
        if (!isThreatened(n, board, row, i)) {
            // don't place queen in same column that it was in before
            if (i != queenCol) {
                // place queen
                board[row][i] = 1;
                return 1;   // return 1 to indicate that the position is legal
            }
        }
    }

    // if we get here, then we could not place a queen in the current row so we try the row above it
    return getNextLegalPosition(n, board, row - 1);
}