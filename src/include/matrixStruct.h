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
MatrixStruct copyMatrixStruct(MatrixStruct toCopy);

// Frees
void freeMatrixStr(MatrixStruct matrix);

// Getter & Setters;
void setMatrix(MatrixStruct matrixStruct, int ** matrix, int rows, int cols);
void setToEmptyMatrix(MatrixStruct matrix);
int getAtPosition(MatrixStruct matrix, int row, int col);
int getMatrixRange(MatrixStruct matrix);
void setAtPosition(MatrixStruct matrix, int row, int col, int value);

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
void proyectionMatrix(MatrixStruct matrix, MatrixStruct answer);

// Binary MatrixxStruct Operations
void multiplyMatrixStructs(MatrixStruct matrix1, MatrixStruct matrix2, MatrixStruct answer);
void addMatrix(MatrixStruct matrix1, MatrixStruct matrix2, MatrixStruct answer);
void substractMatrix(MatrixStruct matrix1, MatrixStruct matrix2, MatrixStruct answer);

// Matrix Solver
int solveMatrixStruct(MatrixStruct matrix, int * answer);

int getDeterminant(MatrixStruct matrix);

MatrixStruct copyColumn(MatrixStruct matrix, int col);
void copyColumnToAnotherMatrix(MatrixStruct matrix1, MatrixStruct matrix2, int col1, int col2);
MatrixStruct subMatrixWithoutModule(MatrixStruct m1, MatrixStruct m2);
MatrixStruct sumMatrixWithoutModule(MatrixStruct m1, MatrixStruct m2);

#endif //MATRICES_RESOLVER_MATRIXSTRC_H
