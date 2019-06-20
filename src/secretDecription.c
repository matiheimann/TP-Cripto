//
// Created by mheimann on 20/06/19.
//

#include "include/secretDecription.h"
#include <stdlib.h>

MatrixStruct recoverMatrixS(MatrixStruct* matrixDoubleS, MatrixStruct matrixR)
{
    return NULL;
}

MatrixStruct recoverMatrixW(MatrixStruct* matrixDoubleS, MatrixStruct matrixRw)
{
    return NULL;
}

MatrixStruct recoverMatirxR(MatrixStruct* matrixG, MatrixStruct matrixSh)
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

MatrixStruct recoverMatrixG(MatrixStruct matrixSh, MatrixStruct matrixV){
    return NULL;
}