//
// Created by lococo on 09/06/19.
//

#ifndef MATRICES_RESOLVER_MATRIXSTRC_H
#define MATRICES_RESOLVER_MATRIXSTRC_H

#include <stdbool.h>

struct matrixStrc {
    int ** matrix;
    int rows;
    int cols;
};

typedef struct matrixStrc * MatrixStruct;


// Creation of MatrixStruct
MatrixStruct newMatrixStruct(int ** matrix, int rows, int cols);
MatrixStruct newEmptyMatrixStruct();
MatrixStruct newIdentityMatrixStruct(int n);
MatrixStruct newZeroMatrixStruct(int rows, int cols);

// Frees
void freeMatrixStr(MatrixStruct matrix);

// Getter & Setters;
void setMatrix(MatrixStruct matrixStruct, int ** matrix, int rows, int cols);
void setToEmptyMatrix(MatrixStruct matrix);
int getAtPosition(MatrixStruct matrix, int row, int col);

// Equals
bool isEmptyMatrix(MatrixStruct matrix);
bool areEqualsMatrixStruct(MatrixStruct matrix1, MatrixStruct matrix2);

//Print MatrixStruct
void printMatrixStructWithResults(MatrixStruct matrixStruct);
void printMatrixStruct(MatrixStruct matrixStruct);

// Unary MatrixStruct Operations
void transposeMatrixStruct(MatrixStruct matrixStruct, MatrixStruct answer);
void getInvertibleMatrixStruct(MatrixStruct matrix, MatrixStruct answer);
void addResultCol(MatrixStruct matrix, int * col);

// Binary MatrixxStruct Operations
void multiplyMatrixStructs(MatrixStruct matrix1, MatrixStruct matrix2, MatrixStruct answer);
void addMatrix(MatrixStruct matrix1, MatrixStruct matrix2, MatrixStruct answer);


#endif //MATRICES_RESOLVER_MATRIXSTRC_H
