#include <stdio.h>

#ifndef AOCUTILS_H
#define AOCUTILS_H

// distance between 2 ints
int dist(int a, int b);

// quicksort
void swap(int *a, int *b);
void quickSort(int arr[], int low, int high);

// print int array contents
void printArr(int *arr, int size);

// 2-dimensional table of integers
typedef struct table Table;
Table *createTable(int rowCt, int colCt);
void destroyTable(Table *t);
int getElem(Table *t, int rowIdx, int colIdx);
void putElem(Table *t, int rowIdx, int colIdx, int elem);
void printTable(Table *t);
int *getCol(Table *t, int col);
void destroyCol(int *col);

// reading from CSV files
int readCSV(char *path, char *delim, Table *t);
void destroyCSV(Table *t);

#endif // AOCUTILS_H;