#include <stdio.h>
#include "functions.h"

int solve(int n, int board[n][n], int row) {
    // if all queens are places, we're done
    if (row == n) return 1;

    // otherwise, try to place a queen in each column in this row from left to right
    for (int i = 0; i < n; i++) {
        if (!isThreatened(n, board, row, i)) {
            // place a queen
            board[row][i] = 1;

            // recursively call solve on the next row
            if (solve(n, board, row + 1)) return 1;

            // if placing the queen isn't valid, remove it and try the next column (backtracking)
            board[row][i] = 0;
        }
    }

    // if we get here, then we couldn't place a queen in this row
    return 0;
}

int getSolution(int n, int board[n][n]) {
    if (solve(n, board, 0) == 0) {
        return 0;
        printf("No solution found.\n");
    }

    return 1;
}