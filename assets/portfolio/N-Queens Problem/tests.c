#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

char* arrayRepresentation(int n, int board[n][n]) {
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int col = -1;
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) {
                col = j;
            }
        }
        arr[i] = col + 1;
    }

    char* str = malloc(100 * sizeof(char));
    char* temp = malloc(100 * sizeof(char));
    strcpy(str, "");
    strcpy(temp, "");

    for (int i = 0; i < n; i++) {
        sprintf(temp, "%d", arr[i]);
        strcat(str, temp);
        if (i != n - 1) {
            strcat(str, ", ");
        }
    }

    return str;
}

// isLegalPosition Test Cases
void isLegalPositionTests() {
    
    printf("\n\n\n  isLegalPosition Test Cases:\n-------------------------------------------\n");
    int n = 8;    
    int board[n][n];
    int queenPositions[8] = {1, 6, 8, 3, 7, 0, 0, 0};

    // Test Case 1 (legal position)
    setBoard(n, board, queenPositions);
    // printBoard(n, board);
    printf("  Test Case 1: %s\n", isLegalPosition(n, board) ? " \033[0;32m PASS" : " \033[0;31m FAIL");
    printf("\033[0m");
    printf("  isLegalPosition: %s\n", isLegalPosition(n, board) ? "true" : "false");

    // Test Case 2 (legal position)
    int queenPositions2[8] = {1, 6, 8, 3, 7, 4, 2, 5};
    setBoard(n, board, queenPositions2);
    // printBoard(n, board);
    printf("\n  Test Case 2: %s\n", isLegalPosition(n, board) ? " \033[0;32m PASS" : " \033[0;31m FAIL");
    printf("\033[0m");
    printf("  isLegalPosition: %s\n", isLegalPosition(n, board) ? "true" : "false");

    // Test Case 3 (illegal position)
    int queenPositions3[8] = {1, 6, 8, 3, 5, 0, 0, 0};
    setBoard(n, board, queenPositions3);
    // printBoard(n, board);
    printf("\n  Test Case 3: %s\n", !isLegalPosition(n, board) ? " \033[0;32m PASS" : " \033[0;31m FAIL");
    printf("\033[0m");
    printf("  isLegalPosition: %s\n", isLegalPosition(n, board) ? "true" : "false");

    // Test Case 4 (illegal position)
    int queenPositions4[8] = {1, 6, 8, 3, 7, 2, 0, 0};
    setBoard(n, board, queenPositions4);
    // printBoard(n, board);
    printf("\n  Test Case 4: %s\n", !isLegalPosition(n, board) ? " \033[0;32m PASS" : " \033[0;31m FAIL");
    printf("\033[0m");
    printf("  isLegalPosition: %s\n", isLegalPosition(n, board) ? "true" : "false");
    printf("\n");
    // ---------------------------------------------------------------------------------

}

// nextLegalPosition Test Cases
void nextLegalPositionTests() {  

    printf("\n\n\n  nextLegalPosition Test Cases:\n-------------------------------------------\n");
    
    int n = 8;
    int board[n][n];
    int queenPositions[8] = {1, 6, 8, 3, 7, 0, 0, 0};


    // Test Case 1 (illegal initial position)
    int queenPositions2[8] = {1, 6, 8, 3, 5, 0, 0, 0};
    setBoard(n, board, queenPositions2);
    nextLegalPosition(n, board, getNextRow(n, board, n - 1));
    printf("\n  Test Case 1: %s\n", strcmp(arrayRepresentation(n, board), "1, 6, 8, 3, 7, 0, 0, 0") == 0 ? " \033[0;32m PASS" : " \033[0;31m FAIL");
    printf("\033[0m");
    printf("  Initial board: \t{1, 6, 8, 3, 5, 0, 0, 0}\n");
    // printBoard(n, board);
    printf("  Next legal position: \t{%s}\n", arrayRepresentation(n, board));
    printBoard(n, board);
    printf("\n");

    // Test Case 2 (legal initial position)
    setBoard(n, board, queenPositions);
    nextLegalPosition(n, board, getNextRow(n, board, n - 1));
    printf("  Test Case 2: %s\n", strcmp(arrayRepresentation(n, board), "1, 6, 8, 3, 7, 4, 0, 0") == 0 ? " \033[0;32m PASS" : " \033[0;31m FAIL");
    printf("\033[0m");
    printf("  Initial board: \t{1, 6, 8, 3, 7, 0, 0, 0}\n");
    // printBoard(n, board);
    printf("  Next legal position: \t{%s}\n", arrayRepresentation(n, board));
    printBoard(n, board);
    printf("\n");

    // Test Case 3 (legal initial position is full)
    int queenPositions3[8] = {1, 6, 8, 3, 7, 4, 2, 5};
    setBoard(n, board, queenPositions3);
    nextLegalPosition(n, board, getNextRow(n, board, n - 1));
    printf("  Test Case 3: %s\n", strcmp(arrayRepresentation(n, board), "1, 6, 8, 5, 0, 0, 0, 0") == 0 ? " \033[0;32m PASS" : " \033[0;31m FAIL");
    printf("\033[0m");
    printf("  Initial board: \t{1, 6, 8, 3, 7, 4, 2, 5}\n");
    // printBoard(n, board);
    printf("  Next legal position: \t{%s}\n", arrayRepresentation(n, board));
    printBoard(n, board);
    printf("\n");

}

// findFirstSolution Test Cases
void findFirstSolution() {
    // finds the first legal position for n = 4...100
    printf("\n\n  Finding the first legal position for n = 4...100:\n---------------------------------------------\n");
    printf("  Going all the way to 100 is out of the scope of my computer's abilities, so this will be limited to 25 iterations (which is what my desktop can do in a couple seconds).\n");
    printf("  If you would like to run more iterations, change the 25 to whatever number you want in the findFirstSolution function in the tests.c file.\n---------------------------------------------\n");
    for (int n = 4; n <= 25; n++) {
        int board[n][n];
        int queenPositions[n];
        for (int i = 0; i < n; i++) {
            queenPositions[i] = 0;
        }
        setBoard(n, board, queenPositions);
        getSolution(n, board);
        printf("  First legal position for n = %d: {%s}\n", n, arrayRepresentation(n, board));

        // uncomment the line below to see a visual representation of the solution
        // printBoard(n, board);
    }
}

// findAllSolutions Test Cases
void findAllSolutions() {
    
    // numSolutions contains the known number of solutions for n = 4...20
    // source: https://en.wikipedia.org/wiki/Eight_queens_puzzle#Counting_solutions_for_other_sizes_n 
    long long numSolutions[17] = {2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 2279184, 14772512, 95815104, 666090624, 4968057848, 39029188884};
    
    // Counts the number of solutions for n = 4...20
    printf("\n\n  Counting the number of solutions for n = 4...20:\n");
    printf("---------------------------------------------\n");
    printf("  Going all the way to n = 20 is not going to be possible on virtually any hardware, as even at n = 15, there are over 2 million possible solutions. \n");
    printf("  If you would like to run more iterations, change the 14 to whatever number you want in the findAllSolutions function in the tests.c file.\n");
    printf("---------------------------------------------\n");
    for (int n = 4; n <= 14; n++) {         // change 14 to 20 to test for n = 4...20, 14 is what my computer can handle in a reasonable amount of time (about 10 seconds)
        int board[n][n];
        int queenPositions[n];
        for (int i = 0; i < n; i++) {
            queenPositions[i] = 0;
        }
        setBoard(n, board, queenPositions);
        int solutions = getAllSolutions(n, board);
        printf("  Number of solutions for n = %d: %-11d\t%s\n", n, solutions, solutions == numSolutions[n - 4] ? " \033[0;32m PASS" : " \033[0;31m FAIL");
        printf("\033[0m");
    }
}

