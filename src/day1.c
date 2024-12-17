#include <stdio.h>
#include <stdlib.h>
#include "../headers/aocutils.h"

#define DAY1_SIZE 1000

int main(void) {
    // int test1[] = {3, 4, 2, 1, 3, 3};
    // int test2[] = {4, 3, 5, 3, 9, 3};

    // int size1 = (int) sizeof(test1) / sizeof(int);
    // int size2 = (int) sizeof(test2) / sizeof(int);
    Table *t = createTable(DAY1_SIZE, 2);
    readCSV("/home/aspandit/aoc24/data/day1.tsv", "   ", t);
    int *col1 = getCol(t, 0);
    int *col2 = getCol(t, 1);

    quickSort(col1, 0, DAY1_SIZE - 1);
    quickSort(col2, 0, DAY1_SIZE - 1);

    int totalDist = 0;
    for (int i = 0; i < DAY1_SIZE; i++) {
        int distance = dist(col1[i], col2[i]);
        totalDist += distance;
    }

    printf("total distance: %d\n", totalDist);

    destroyCSV(t);
    destroyCol(col1);
    destroyCol(col2);
    return 0;
}