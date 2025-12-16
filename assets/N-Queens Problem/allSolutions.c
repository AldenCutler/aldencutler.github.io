#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/*
Find all solutions to the n-queens problem for a given n.
*/

int solveAll(int n, int board[n][n], int row, int count) {

    // if all queens are places, we're done
    if (row == n) {
        return count + 1;
    }

    // otherwise, try to place a queen in each column in this row from left to right
    for (int i = 0; i < n; i++) {
        if (!isThreatened(n, board, row, i)) {
            // place a queen
            board[row][i] = 1;

            // recursively call solve on the next row
            count = solveAll(n, board, row + 1, count);

            // if placing the queen isn't valid, remove it and try the next column (backtracking)
            board[row][i] = 0;
        }
    }

    // if we get here, then we couldn't place a queen in this row
    return count;
}

int getAllSolutions(int n, int board[n][n]) {
    int count = 0;
    count = solveAll(n, board, 0, count);
    return count;
}
