//
// Created by lococo on 09/06/19.
//

#include <stdio.h>
#include <stdlib.h>
#include "include/matrixStruct.h"
#include "include/matrixLibrary.h"
#include "include/libraryMod251.h"


/*
 *      Creation of Matrix Struct
 */

MatrixStruct newMatrixStruct(int ** matrix, int rows, int cols)
{
    MatrixStruct ans = malloc(sizeof(ans));
    setMatrix(ans, matrix, rows, cols);
    return ans;
}

MatrixStruct newEmptyMatrixStruct()
{
    MatrixStruct ans = malloc(sizeof(ans));
    ans->matrix = NULL;
    ans->cols = 0;
    ans->rows = 0;
    return ans;
}

MatrixStruct newIdentityMatrixStruct(int n)
{
    if (n <= 0)
    {
        return newEmptyMatrixStruct();
    }
    MatrixStruct ans = newEmptyMatrixStruct();
    ans->rows = n;
    ans->cols = n;
    ans->matrix = newMatrix(n, n);
    setIdentityMatrix(ans->matrix, ans->rows);

    return ans;
}

MatrixStruct newZeroMatrixStruct(int rows, int cols)
{
    MatrixStruct ans = newEmptyMatrixStruct();
    ans->rows = rows;
    ans->cols = cols;
    ans->matrix = newMatrix(rows, cols);
    return ans;
}

MatrixStruct copyMatrixStruct(MatrixStruct toCopy)
{
    MatrixStruct copy = newMatrixStruct(toCopy->matrix, toCopy->rows, toCopy->cols);
    return copy;
}

/*
 *      Frees
 */

void freeMatrixStr(MatrixStruct matrix)
{
    if (matrix->matrix != NULL)
    {
        freeMatrix(matrix->matrix, matrix->rows, matrix->cols);
    }
    free(matrix);
}

/*
 *      Setters && Getters
 */

void setMatrix(MatrixStruct matrixStruct, int ** matrix, int rows, int cols)
{
    int ** auxMatrix = newMatrix(rows, cols);
    if (auxMatrix == NULL)
    {
        perror("No se pudo crear la estructura");
        return;
    }

    copyMatrix(matrix, rows, cols, auxMatrix);
    matrixStruct->matrix = auxMatrix;
    matrixStruct->rows = rows;
    matrixStruct->cols = cols;
    return;
}

void setToEmptyMatrix(MatrixStruct matrix)
{
    if (matrix->matrix != NULL)
    {
        freeMatrix(matrix->matrix, matrix->rows, matrix->cols);
    }
    matrix->rows = 0;
    matrix->cols = 0;
}

int getAtPosition(MatrixStruct matrix, int row, int col)
{
    if (matrix->rows < row || row < 0)
    {
        perror("Acceso a fila no permitida");
        return -1;
    }
    if (matrix->cols < col || col < 0)
    {
        perror("Acceso a columna no permitida");
        return -1;
    }
    if (matrix->matrix == NULL)
    {
        perror("Matriz no inicializada");
        return -2;
    }
    return matrix->matrix[row][col];
}

void setAtPosition(MatrixStruct matrix, int row, int col, int value)
{
    if (row >= matrix->rows ||  row < 0)
    {
        perror("Ingreso a una fila invalida");
        return;
    }
    if (col >= matrix->cols || col < 0)
    {
        perror("Ingreso a una columna invalida");
        return;
    }
    matrix->matrix[row][col] = mod251(value);
    return;
}

int getMatrixRange(MatrixStruct matrix)
{
    if (matrix == NULL || isEmptyMatrix(matrix))
    {
        return 0;
    }
    return getRangeOfMatrix(matrix->matrix, matrix->rows, matrix->cols);
}
/*
 *      Equals
 */

bool isEmptyMatrix(MatrixStruct matrix)
{
    if (matrix->cols != 0)
    {
        return false;
    }

    if (matrix->rows != 0)
    {
        return false;
    }

    if (matrix->matrix != NULL)
    {
        return false;
    }
    return true;
}

bool areEqualsMatrixStruct(MatrixStruct matrix1, MatrixStruct matrix2)
{
    if (matrix1->rows != matrix2->rows)
    {
        return false;
    }
    if (matrix1->cols != matrix2->cols)
    {
        return false;
    }
    if (matrix1->matrix == NULL && matrix2->matrix == NULL)
    {
        return true;
    }
    else if(matrix1->matrix == NULL || matrix2->matrix == NULL)
    {
        return false;
    }
    return areEqualMatrix(matrix1->matrix, matrix1->rows, matrix1->cols, matrix2->matrix);
}

/*
 *      Prints Of Matrix Struct
 */

void printMatrixStructWithResults(MatrixStruct matrixStruct)
{
    if (matrixStruct == NULL)
    {
        return;
    }
    printf("Matrix size : %d x %d \n", matrixStruct->rows, matrixStruct->cols);
    printMatrixWithResults(matrixStruct->matrix, matrixStruct->rows, matrixStruct->cols);
    return;
}

void printMatrixStruct(MatrixStruct matrixStruct)
{
    if (matrixStruct == NULL)
    {
        return;
    }
    printf("Matrix size : %d x %d \n", matrixStruct->rows, matrixStruct->cols);
    printMatrix(matrixStruct->matrix, matrixStruct->rows, matrixStruct->cols);
    return;
}

/*
 *      Unary Matrix Struct Operations
 */

void transposeMatrixStruct(MatrixStruct matrixStruct, MatrixStruct answer)
{
    answer->cols = matrixStruct->rows;
    answer->rows = matrixStruct->cols;
    answer->matrix = newMatrix(answer->rows, answer->cols);
    transpose_matrix(matrixStruct->matrix, matrixStruct->rows, matrixStruct->cols, answer->matrix);

    return;
}

void getInvertibleMatrixStruct(MatrixStruct matrix, MatrixStruct answer)
{
    setToEmptyMatrix(answer);
    answer->cols = matrix->cols;
    answer->rows = matrix->rows;
    answer->matrix = newMatrix(answer->rows, answer->cols);
    getInvertibleMatrix(matrix->matrix, matrix->rows, matrix->cols, answer->matrix);
    return;
}

void multiplyMatrixStruct(MatrixStruct matrix, int num, MatrixStruct answer)
{
    setToEmptyMatrix(answer);
    if (matrix->matrix == NULL)
    {
        return;
    }
    productoEscalar(matrix->matrix, matrix->rows, matrix->cols, num, answer->matrix);
    return;
}

void addResultCol(MatrixStruct matrix, int * col)
{
    if (matrix == NULL || isEmptyMatrix(matrix))
    {
        return;
    }
    int ** newMatrix = addColToMatrix(matrix->matrix, matrix->rows, matrix->cols, col);
    freeMatrix(matrix->matrix, matrix->rows, matrix->cols);
    matrix->matrix = newMatrix;
    matrix->cols = matrix->cols + 1;
}

void proyectionMatrix(MatrixStruct matrix, MatrixStruct answer)
{
    MatrixStruct matrixT    = newEmptyMatrixStruct();
    MatrixStruct aux1       = newEmptyMatrixStruct();
    MatrixStruct aux2       = newEmptyMatrixStruct();
    MatrixStruct aux3       = newEmptyMatrixStruct();

    transposeMatrixStruct(matrix, matrixT);
    multiplyMatrixStructs(matrixT, matrix, aux1);
    getInvertibleMatrixStruct(aux1, aux2);
    multiplyMatrixStructs(matrix, aux2, aux3);
    multiplyMatrixStructs(aux3, matrixT, answer);
    freeMatrixStr(aux1);
    freeMatrixStr(aux2);
    freeMatrixStr(aux3);
    freeMatrixStr(matrixT);
}


/*
 *      Binary Matrix Struct Operation
 */

void multiplyMatrixStructs(MatrixStruct matrix1, MatrixStruct matrix2, MatrixStruct answer)
{
    if (matrix1->cols != matrix2->rows)
    {
        perror("Error al multiplicar Matrices, el numero de columnas de la matrix1 es diferente que el numero de filas de matrix2");
        return;
    }
    if (answer->matrix != NULL && !isEmptyMatrix(answer))
    {
        freeMatrix(answer->matrix, answer->rows, answer->cols);
    }

    answer->rows = matrix1->rows;
    answer->cols = matrix2->cols;
    answer->matrix = newMatrix(answer->rows, answer->cols);

    if (answer->matrix == NULL)
    {
        perror("No se pudo ejecutar la multiplicacion de matrices");
        return;
    }
    multiply_matrix(matrix1->matrix, matrix1->rows, matrix1->cols, matrix2->matrix, matrix2->rows, matrix2->cols, answer->matrix);
    return;

}

void addMatrix(MatrixStruct matrix1, MatrixStruct matrix2, MatrixStruct answer)
{
    if (matrix1->rows != matrix2->rows)
    {
        perror("No se puede realizar la suma de matrices, tamaños de filas distintas");
        return;
    }
    if (matrix1->cols != matrix2->cols)
    {
        perror("No se puede realizar la suma de matrices, tamaños de columnas distintos");
        return;
    }
    setToEmptyMatrix(answer);
    answer->cols = matrix1->cols;
    answer->rows = matrix1->rows;
    answer->matrix = newMatrix(answer->rows, answer->cols);
    add_matrix(matrix1->matrix, matrix1->rows, matrix1->cols, matrix2->matrix, answer->matrix);
    return;
}

void substractMatrix(MatrixStruct matrix1, MatrixStruct matrix2, MatrixStruct answer)
{
    if (matrix1->rows != matrix2->rows)
    {
        perror("No se puede realizar la suma de matrices, tamaños de filas distintas");
        return;
    }
    if (matrix1->cols != matrix2->cols)
    {
        perror("No se puede realizar la suma de matrices, tamaños de columnas distintos");
        return;
    }
    setToEmptyMatrix(answer);
    answer->cols = matrix1->cols;
    answer->rows = matrix1->rows;
    answer->matrix = newMatrix(answer->rows, answer->cols);
    substract_matrix(matrix1->matrix, matrix1->rows, matrix1->cols, matrix2->matrix, answer->matrix);
    return;
}

/*
 *      Matrix Solver
 */

int solveMatrixStruct(MatrixStruct matrix, int * answer)
{
    if (matrix->matrix == NULL || matrix->rows + 1 < matrix->cols)
    {
        return 0;
    }

    matrixSolver(matrix->matrix, matrix->rows, matrix->cols, answer);

    return 1;
}

int getDeterminant(MatrixStruct matrix)
{
    return determinantOfMatrix(matrix->matrix, matrix->rows);
}

MatrixStruct copyColumn(MatrixStruct matrix, int col){
    MatrixStruct ret = newZeroMatrixStruct(matrix->rows, 1);
    for(int i = 0; i < matrix->rows; i++)
    {
        ret->matrix[i][0] = matrix->matrix[i][col];
    }
    return ret;
}

void copyColumnToAnotherMatrix(MatrixStruct matrix1, MatrixStruct matrix2, int col1, int col2)
{
    for(int i = 0; i < matrix2->rows; i++)
    {
        matrix1->matrix[i][col1] = matrix2->matrix[i][col2];
    }
}

MatrixStruct subMatrixWithoutModule(MatrixStruct m1, MatrixStruct m2)
{
    MatrixStruct result = newZeroMatrixStruct(m1->rows, m1->cols);
    result->matrix = substractWithoutModule(m1->matrix, m2->matrix, m1->rows, m1->cols);
    return result;
}

MatrixStruct sumMatrixWithoutModule(MatrixStruct m1, MatrixStruct m2)
{
    MatrixStruct result = newZeroMatrixStruct(m1->rows, m1->cols);
    result->matrix = addMatrixWithoutModule(m1->matrix, m2->matrix, m1->rows, m1->cols);
    return result;
}

