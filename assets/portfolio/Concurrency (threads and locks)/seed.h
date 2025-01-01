#include <stdio.h>
#include <stdlib.h>

int getseed() {
    FILE *fp;
    int seed;
    fp = fopen("seed.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    fscanf(fp, "%d", &seed);
    fclose(fp);
    return seed;
}