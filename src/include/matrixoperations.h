#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

typedef struct matrix
{
    int rows;
    int columns;
    int** matrix;
}matrix;

matrix* newMatrix(int rows, int columns, char argCount, ...);
matrix* sumMatrix(matrix* m1, matrix* m2);

#endif
