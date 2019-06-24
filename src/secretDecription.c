//
// Created by mheimann on 20/06/19.
//

#include "include/secretDecription.h"
#include <stdlib.h>
#include <stdio.h>

MatrixStruct recoverMatrixS(MatrixStruct matrixDoubleS, MatrixStruct matrixR)
{
    MatrixStruct matrixS = newZeroMatrixStruct(matrixR->rows, matrixR->cols);
    addMatrix(matrixDoubleS, matrixR, matrixS);
    for(int i = 0; i < matrixS->rows; i++)
    {
        for(int j = 0; j < matrixS->cols; j++)
        {
            matrixS->matrix[i][j] = matrixS->matrix[i][j];
        }
    }
    return matrixS;
}

MatrixStruct recoverMatrixW(MatrixStruct matrixDoubleS, MatrixStruct matrixRw)
{
    MatrixStruct matrixW = newZeroMatrixStruct(matrixRw->rows, matrixRw->cols);
    addMatrix(matrixDoubleS, matrixRw, matrixW);
    for(int i = 0; i < matrixW->rows; i++)
    {
        for(int j = 0; j < matrixW->cols; j++)
        {
            matrixW->matrix[i][j] = matrixW->matrix[i][j];
        }
    }
    return matrixW;
}

MatrixStruct recoverMatrixR(MatrixStruct* matrixG, int* shadowNumber, int size)
{
    int val = matrixG[0]->rows/matrixG[0]->cols;
    MatrixStruct matrixAux = newZeroMatrixStruct(val, val + 1);
    MatrixStruct matrixR = newZeroMatrixStruct(matrixG[0]->rows, matrixG[0]->rows);
    for(int i = 0; i < val; i++)
    {
        int pot = 1;
        for(int j = 0; j < val; j++)
        {
            matrixAux->matrix[i][j] = pot;
            pot = pot * shadowNumber[i];
            pot = pot % 251;
        }
    }
    for(int i = 0; i < matrixG[0]->rows; i++)
    {
        for(int j = 0; j < matrixG[0]->cols; j++)
        {
            for(int k = 0; k < size; k++)
            {
                matrixAux->matrix[k][val] = matrixG[k]->matrix[i][j];
            }
            int * ans = malloc(sizeof(int) * val);
            if(solveMatrixStruct(matrixAux, ans))
            {
                for(int k = 0; k < val; k++)
                {
                    matrixR->matrix[i][j * val + k] = ans[k];
                }

            }
            else
            {
                freeMatrixStr(matrixAux);
                freeMatrixStr(matrixR);
                free(ans);
                return NULL;
            }
            free(ans);
        }
    }

    freeMatrixStr(matrixAux);
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
    freeMatrixStr(matrixB);
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