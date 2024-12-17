#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/aocutils.h"

// distance between 2 ints
int dist(int a, int b) {
    if (b - a > 0) 
        return b - a;
    return a - b;
}

// quicksort & helpers

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int lag = low - 1;

    for (int mov = low; mov < high; mov++) {
        if (arr[mov] < pivot) {
            lag++;
            swap(&arr[mov], &arr[lag]);
        }
    }

    lag++;
    swap(&arr[lag], &arr[high]);
    return lag;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int partIdx = partition(arr, low, high);
        quickSort(arr, low, partIdx - 1);
        quickSort(arr, partIdx + 1, high);
    }
}

// print int array contents

void printArr(int *arr, int size) {
    if (size == 0) {
        printf("[]");
        return;
    }

    printf("[");

    for (int i = 0; i < size - 1; i++)
        printf("%d, ", arr[i]);

    printf("%d]\n", arr[size - 1]);
    return;
}

// define a 2-dimensional table of integers & access parameters

typedef struct table {
    int rowCt;
    int colCt;
    int *data;
} Table;

Table *createTable(int rowCt, int colCt) {
    Table *t = (Table *) malloc(sizeof(Table));
    if (t == NULL) {
        fprintf(stderr, "ERROR: memory allocation for table failed\n");
        exit(1);
    }
    t->data = (int *) calloc((size_t) (rowCt * colCt), sizeof(int));
    if (t->data == NULL) {
        fprintf(stderr, "ERROR: memory allocation for table data failed\n");
        exit(1);
    }
    t->rowCt = rowCt;
    t->colCt = colCt;
    
    return t;
}

void destroyTable(Table *t) {
    free(t->data);
    t->data = NULL;
    free(t);
}

int getElem(Table *t, int rowIdx, int colIdx) {
    int pos = rowIdx * t->colCt + colIdx;
    return t->data[pos];
}

void putElem(Table *t, int rowIdx, int colIdx, int elem) {
    int pos = rowIdx * t->colCt + colIdx;
    t->data[pos] = elem;
}

void printTable(Table *t) {
    printf("rows=%d\ncolumns=%d\n[", t->rowCt, t->colCt);
    for (int i = 0; i < t->rowCt; i++) {
        if (i != 0) printf(" ");

        int *arr = t->data + t->colCt * i;
        printf("[");

        for (int j = 0; j < t->colCt - 1; j++)
            printf("%d, ", arr[j]);

        printf("%d]", arr[t->colCt - 1]);
        printf("%s", i != t->rowCt-1 ? "\n" : "]\n");
    }
}

int *getCol(Table *t, int colIdx) {
    if (colIdx >= t->colCt) {
        fprintf(stderr, "Error: no col of index %d in table with %d columns.\n", colIdx, t->colCt);
        exit(1);
    }
    int *col = (int *) calloc((size_t) t->rowCt, sizeof(int));

    for (int i = 0; i < t->rowCt; i++)
        col[i] = getElem(t, i, colIdx);

    return col;
}

void destroyCol(int *col) {
    free(col);
}

// parse tsv file

int readCSV(char *path, char *delim, Table *t) {
    // set up file access
    FILE *fptr = fopen(path, "r");

    if (fptr == NULL) {
        fprintf(stderr, "Error: could not open file '%s'.\n", path);
        return 1;
    }

    // populate table
    char buffer[1000];
    int row = 0;
    while (fgets(buffer, 1000, fptr) != NULL) {
        int col = 0;
        char *numStr = strtok(buffer, delim);

        while (numStr != NULL) {
            putElem(t, row, col, atoi(numStr));
            numStr = strtok(NULL, delim);
            col++;
        }
        row++;
    }
    fclose(fptr);
    return 0;
}

void destroyCSV(Table *t) {
    destroyTable(t);
}
