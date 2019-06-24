#ifndef MATRICES_RESOLVER_MATRIXLIBRARY_H
#define MATRICES_RESOLVER_MATRIXLIBRARY_H

#include <stdbool.h>

// Creation Of Matrix & Vectors
int ** newMatrix(int n, int m);
int * newVector (int n);

//  Frees
void freeMatrix(int ** matrix, int n, int m);

// Getters , Setters && Copys
void copyMatrix (int ** matrixToCopy, int n, int m, int ** dest);
void setIdentityMatrix(int ** matrix, int n);
int getRangeOfMatrix(int ** matrix, int rows, int cols);

// Equals
bool areEqualMatrix(int ** matrix1, int n, int m, int ** matrix2);
bool areResultOfMatrix(int ** matrix, int n, int m, int * answer);

// Prints
void printMatrixWithResults(int ** matrix, int n, int m);
void printMatrix (int ** matrix, int n, int m);
void printVector(int * vector, int n);

// Unary Operations
void productoEscalar(int ** matrix, int n, int m, int num, int ** answer);
void transpose_matrix ( int ** matrix, int n, int m, int ** answer);
void getInvertibleMatrix (int ** matrix, int n, int m, int ** answer);

// Binary Operations
void add_matrix (int ** matrix1, int n1, int m1, int ** matrix2, int ** answer);
void substract_matrix (int ** matrix1, int n1, int m1, int ** matrix2, int ** answer);
void multiply_matrix(int ** matrix1, int n1, int m1, int ** matrix2, int n2, int m2, int** answer);

// RowOperatios
void multiplyRow(int ** matrix, int n1, int m1, int rowIndex, int num);
void divideRow(int ** matrix, int n, int m, int rowIndex, int num);
void swapRows(int ** matrix, int n1, int m1, int rowIndex1, int rowIndex2);
void swapInNonZeroRow(int ** matrix, int n1,int m1, int rowIndex);
void subtractRow(int ** matrix, int n1, int m1, int rowIndexChanged, int rowIndex);

// Col Operations
int ** addColToMatrix(int ** matrix, int row, int col, int * newCol);

// MatrixSolver
void matrixSolver (int ** matrix1, int n1, int m1, int * answer);
void solve_matrix (int ** matrix, int n, int m);
void getResult(int ** matrix, int n1, int m1, int * answer);

int determinantOfMatrix(int** mat, int n);
void getCofactor(int** mat, int** temp, int q, int n);
int** substractWithoutModule(int** m1, int** m2, int rows, int cols);
int** addMatrixWithoutModule(int** m1, int** m2, int rows, int cols);



#endif //MATRICES_RESOLVER_MATRIXLIBRARY_H
