//
// Created by mheimann on 20/06/19.
//

#include "include/secretDecription.h"
#include <stdlib.h>

MatrixStruct recoverMatrixS(MatrixStruct matrixDoubleS, MatrixStruct matrixR)
{
    MatrixStruct matrixS = newEmptyMatrixStruct();
    addMatrix(matrixDoubleS, matrixR, matrixS);
    return matrixS;
}

MatrixStruct recoverMatrixW(MatrixStruct matrixDoubleS, MatrixStruct matrixRw)
{
    MatrixStruct matrixW = newEmptyMatrixStruct();
    addMatrix(matrixDoubleS, matrixRw, matrixW);
    return matrixW;
}

MatrixStruct recoverMatrixR(MatrixStruct* matrixG)
{
    return NULL;
}

MatrixStruct recoverMatrixDoubleS(MatrixStruct* matrixSh, int size)
{
    MatrixStruct matrixDoubleS = newEmptyMatrixStruct();
    MatrixStruct matrixB = newZeroMatrixStruct(matrixSh[0]->rows, size);
    for(int i = 0; i < size; i++){
        copyColumnToAnotherMatrix(matrixB, matrixSh[i], i, 1);
    }

    proyectionMatrix(matrixB, matrixDoubleS);

    return matrixDoubleS;
}

MatrixStruct recoverMatrixG(MatrixStruct matrixSh){

    MatrixStruct matrixG = newZeroMatrixStruct(matrixSh->rows, matrixSh->cols - 1);
    for(int i = 0; i < matrixG->cols; i++)
    {
        copyColumnToAnotherMatrix(matrixG, matrixSh, i, i+1);
    }
    return matrixG;
}