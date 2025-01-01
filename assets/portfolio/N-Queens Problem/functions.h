#include <stdbool.h>

// Prints the board to the screen.
// @param n the size of the board
// @param board the board
void printBoard(int n, int board[n][n]);

// Given a board, sets the board with the given queen positions.
// @param n the size of the board
// @param board the board
// @param queens the queen positions: queens[i] = file, i = rank
void setBoard(int n, int board[n][n], int queens[n]);

// Given a square on the board, returns 1 if the square is threatened by a queen, 0 otherwise.
// @param n the size of the board
// @param board the board
// @param row the row of the square
// @param col the column of the square
int isThreatened(int n, int board[n][n], int row, int col);

// Given a board, returns 1 if the board is legal (meaning no queen attacks another queen) and 0 otherwise.
// @param n the size of the board
// @param board the board
int isLegalPosition(int n, int board[n][n]);

// Given a board, returns the row of the last queen in the board.
// @param n the size of the board
// @param board the board
// @param row the row to start searching from
int getNextRow(int n, int board[n][n], int row);

// Returns the column of a queen in a specific row, or -1 if there is no queen in that row.
// @param n the size of the board
// @param board the board
// @param row the row to check
int getCol(int n, int board[n][n], int row);

// Function used to differentiate between a full legal board and a not full legal board
// @param n the size of the board
// @param board the board
// @param row the row to start searching from
int nextLegalPosition(int n, int board[n][n], int row);

// Returns true if a solution exists (and manipulates the board to be a solution), or false if a solution does not exist.
// @param n the size of the board
// @param board the board
// @param row the row to start searching from
int getNextLegalPosition(int n, int board[n][n], int row);

// Recursively finds the first solution to the n-queens problem.
// @param n the size of the board
// @param board the board
// @param row the row to start searching from
int solve(int n, int board[n][n], int row);

// Returns true if a solution exists (and manipulates the board to be a solution), or false if a solution does not exist.
// @param n the size of the board
// @param board the board
int getSolution(int n, int board[n][n]);

// Recursively finds all solutions to the n-queens problem.
// @param n the size of the board
// @param board the board
// @param row the row to start searching from
int solveAll(int n, int board[n][n], int row, int count);

// Returns true if a solution exists (and manipulates the board to be a solution), or false if a solution does not exist.
// @param n the size of the board
// @param board the board
int getAllSolutions(int n, int board[n][n]);

// Tests Question 1 (isLegalPosition)
void isLegalPositionTests();

// Tests Question 2 (nextLegalPosition)
void nextLegalPositionTests();

// Tests Question 3 (findFirstSolution)
void findFirstSolution();

// Tests Question 4 (findAllSolutions)
void findAllSolutions();

// Helper function that takes a solved board and returns a string representation of it where string[i] == column/file and i == row/rank
// @param n the size of the board
// @param board the board
char* arrayRepresentation(int n, int board[n][n]);