//
// Created by mheimann on 20/06/19.
//

#include "include/secretDecription.h"
#include <stdlib.h>

MatrixStruct recoverMatrixS(MatrixStruct matrixDoubleS, MatrixStruct matrixR)
{
    MatrixStruct matrixS = sumMatrixWithoutModule(matrixDoubleS, matrixR);
    for(int i = 0; i < matrixS->rows; i++)
    {
        for(int j = 0; j < matrixS->cols; j++)
        {
            matrixS->matrix[i][j] = matrixS->matrix[i][j] % 256;
        }
    }
    return matrixS;
}

MatrixStruct recoverMatrixW(MatrixStruct matrixDoubleS, MatrixStruct matrixRw)
{
    MatrixStruct matrixW = sumMatrixWithoutModule(matrixDoubleS, matrixRw);
    for(int i = 0; i < matrixW->rows; i++)
    {
        for(int j = 0; j < matrixW->cols; j++)
        {
            matrixW->matrix[i][j] = matrixW->matrix[i][j] % 256;
        }
    }
    return matrixW;
}

MatrixStruct recoverMatrixR(MatrixStruct* matrixG, int* shadowNumber, int size)
{
    MatrixStruct matrixAux = newZeroMatrixStruct(size, matrixG[0]->rows + 1);
    MatrixStruct matrixR = newZeroMatrixStruct(matrixG[0]->rows, matrixG[0]->rows);
    for(int i = 0; i < matrixG[0]->rows; i++)
    {
        for(int j = 0; j < size; j++)
        {
            matrixAux->matrix[i][j] = (j == size - 1) ? shadowNumber[i] : 1;
        }
    }
    for(int i = 0; i < matrixG[0]->rows; i++)
    {
        for(int j = 0; j < matrixG[0]->cols; j++)
        {
            for(int k = 0; k < size; k++)
            {
                matrixAux->matrix[k][matrixG[0]->rows] = matrixG[k]->matrix[i][j];
            }
            int val = matrixG[0]->rows/matrixG[0]->cols;
            int* ans = malloc(sizeof(int) * val);
            if(solveMatrixStruct(matrixAux, ans))
            {
                for(int k = 0; k < val; k++)
                {
                    matrixR->matrix[i][j * val + k] = ans[k];
                }
            }
            else
            {
                return NULL;
            }
        }
    }
    return matrixR;
}

MatrixStruct recoverMatrixDoubleS(MatrixStruct* matrixSh, int size)
{
    MatrixStruct matrixDoubleS = newEmptyMatrixStruct();
    MatrixStruct matrixB = newZeroMatrixStruct(matrixSh[0]->rows, size);
    for(int i = 0; i < size; i++)
    {
        copyColumnToAnotherMatrix(matrixB, matrixSh[i], i, 0);
    }
    proyectionMatrix(matrixB, matrixDoubleS);

    return matrixDoubleS;
}

MatrixStruct recoverMatrixG(MatrixStruct matrixSh)
{

    MatrixStruct matrixG = newZeroMatrixStruct(matrixSh->rows, matrixSh->cols - 1);
    for(int i = 0; i < matrixG->cols; i++)
    {
        copyColumnToAnotherMatrix(matrixG, matrixSh, i, i+1);
    }
    return matrixG;
}

MatrixStruct* recoveryAlgorithm(MatrixStruct* matrixSh, MatrixStruct matrixRw, int* shadowNumber, int size)
{
    MatrixStruct* result = malloc(sizeof(MatrixStruct) * 2);
    MatrixStruct matrixDoubleS = recoverMatrixDoubleS(matrixSh, size);
    MatrixStruct* matrixG = malloc(sizeof(MatrixStruct) * size);
    for(int i = 0; i < size; i++)
    {
        matrixG[i] = recoverMatrixG(matrixSh[i]);
    }
    MatrixStruct matrixR = recoverMatrixR(matrixG, shadowNumber, size);
    result[0] = recoverMatrixS(matrixDoubleS, matrixR);
    result[1] = recoverMatrixW(matrixDoubleS, matrixRw);
    return result;
}