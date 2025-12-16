#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/helpers.h"
#include "../include/mmu.h"

extern int arg_count;

/**
 * Read and check input from stdin, return 1 if exceeds the max length
 * and return 0 if input is valid.
 * If input is interrupted or EOF, exit the program.
 * @param str the input string
 * @return 1 if input exceeds the max length, 0 if input is valid
 */
int read_input(char* str) {
    int c;

    // if input interrupted or EOF, exit
    if (fgets(str, MAX_INPUT_LENGTH + 3, stdin) == NULL) {
        exit_memsim();
    }

    // if input character > MAX_INPUT_LENGTH, clear the stdin and return 1
    if (strlen(str) > MAX_INPUT_LENGTH + 1) {
        printf("\nERROR: input exceeds the limit (128).\n");
        if (str[MAX_INPUT_LENGTH + 1] != '\n') {
            while ((c = getchar()) != '\n' && c != EOF); // clear the stdin
        }
        return 1;
    }

    // otherwise, input is valid so remove the newline character
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    return 0;
}

/**
 * Read and check input arguments, return 1 if exceeds the max length
 * and return 0 if args are valid.
 * @param pstr the array of strings to store the arguments
 * @param str the input string
 * @return 1 if input exceeds the max length, 0 if args are valid
 */
int read_args(char** pstr, char* str) {
    if (strlen(str) != 0) {
        char* splitter = ",";
        pstr[arg_count++] = strtok(str, splitter);
        while ((pstr[arg_count] = strtok(NULL, splitter))) {
            if (arg_count > MAX_ARGS) {
                printf("ERROR: input arguments exceeds the limit (32).\n");
                return 1;
            }
            arg_count++;
        }
    }
    pstr[arg_count] = NULL;
    return 0;
}