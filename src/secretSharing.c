#include "include/secretSharing.h"
#include "include/matrixStruct.h"
#include "include/matrixList.h"
#include "include/random.h"
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

MatrixStruct* costructImageShare(MatrixStruct matrixS, int k, MatrixStruct matrixW)
{
    MatrixStruct* result = malloc(sizeof(MatrixStruct*) * (matrixS->rows + 1));
    MatrixStruct matrixA = generateMatrixA(matrixS, matrixS->rows, k);
    MatrixStruct matrixSdouble = generateMatrixSdouble(matrixA);
    MatrixStruct matrixR = generateMatrixR(matrixS, matrixSdouble);
    MatrixStruct matrixlistX = generateMatrixX(matrixS->rows, k);
    MatrixStruct matrixlistV = generateMatrixV(matrixA, matrixlistX);
    MatrixStruct* matrixListG = generateMatrixListG(matrixR, k);
    MatrixStruct matrixRw = generateMatrixListRw(matrixW, matrixSdouble);
    MatrixStruct* matrixListSh = generateMatrixListSh(matrixlistV, matrixListG);
    for(int i = 0; i < matrixS->rows; i++)
    {
        result[i] = matrixListSh[i];
    }
    result[matrixS->rows] = matrixRw;
    return result;
}

MatrixStruct* generateMatrixListSh(MatrixStruct matrixV, MatrixStruct* matrixListG) {

    int n = matrixListG[0]->rows;
    int k = matrixListG[0]->cols;

    MatrixStruct* ret = malloc(sizeof(MatrixStruct) * n);

    for(int i = 0; i < n; i++){
        ret[i] = newZeroMatrixStruct(n, k+1);
        for(int j = 0; j < n; j++){
            ret[i]->matrix[j][0] = matrixV->matrix[j][i];
            for(int w = 0; w < k; w++){
                ret[i]->matrix[j][w+1] = matrixListG[i]->matrix[j][w];
            }
        }
    }

    return ret;

}

MatrixStruct generateMatrixListRw(MatrixStruct matrixW, MatrixStruct matrixSdouble) {
    MatrixStruct matrixRw = newEmptyMatrixStruct();
    substractMatrix(matrixW, matrixSdouble, matrixRw);
    return matrixRw;
}

MatrixStruct* generateMatrixListG(MatrixStruct matrixR, int k) {
    int n = matrixR->rows;
    MatrixStruct* ret = malloc(sizeof(MatrixStruct) * n);
    for(int i = 1; i <= n; i++){
        ret[i-1] = newZeroMatrixStruct(n, k);
        for(int j = 0; j < n; j++){
            for(int w = 0; w < k; w++){
                int g = 0;
                for(int y = 0; y < n/k - 1; y++){
                    g += matrixR->matrix[j][w * n/k + y];
                    g = g%251;
                }
                g += matrixR->matrix[j][(w+1) * n/k - 1] * i;
                g = g%251;
                ret[i-1]->matrix[j][w] = g;
            }
        }
    }
    return ret;
}


MatrixStruct generateMatrixV(MatrixStruct matrixA, MatrixStruct matrixX) {
    MatrixStruct matrixV = newZeroMatrixStruct(matrixA->rows,matrixA->rows);
    for(int i = 0; i < matrixX->cols; i++){
        MatrixStruct aux = copyColumn(matrixX, i);
        MatrixStruct ans = newZeroMatrixStruct(matrixA->rows,1);
        multiplyMatrixStructs(matrixA, aux, ans);

        for(int j = 0; j<ans->rows; j++){
            matrixV->matrix[j][i] = ans->matrix[j][0];
        }
    }
    return matrixV;
}

MatrixStruct generateMatrixX(int n, int k) {
    MatrixStruct matrixX = newZeroMatrixStruct(k, n);
    setSeed(clock());
    char* selected = calloc(1, sizeof(bool) * 251);
    for(int i = 0; i < n; i++){
        int a = nextChar();
        while(a > 251 || a == 0 || selected[a])
        {
            a = nextChar();
        }

        selected[a] = 1;
        int lastValue = 1;
        matrixX->matrix[0][i] = lastValue;
        for(int j = 1; j < k; j++){
            lastValue = ((lastValue % 251) * (a % 251)) % 251;
            matrixX->matrix[j][i] = lastValue;
        }
    }
    return matrixX;
}

MatrixStruct generateMatrixR(MatrixStruct matrixS, MatrixStruct matrixSdouble) {
    
    MatrixStruct matrixR = newEmptyMatrixStruct();
    substractMatrix(matrixS, matrixSdouble, matrixR);

    return matrixR;
}

MatrixStruct generateMatrixSdouble(MatrixStruct matrixA) {

    MatrixStruct matrixSdouble = newEmptyMatrixStruct();
    proyectionMatrix(matrixA, matrixSdouble);

    return matrixSdouble;
}

MatrixStruct generateMatrixA(MatrixStruct matrixS, int n, int k) {

    MatrixStruct matrixA = newZeroMatrixStruct(n, k);
    setSeed(clock());
    do
    {
        for(int i=0; i<matrixA->rows; i++)
        {
            for(int j=0; j<matrixA->cols; j++)
            {
                int randRumber = nextChar();
                while(randRumber > 251)
                {
                    randRumber = nextChar();
                }

                matrixA->matrix[i][j] = randRumber;
            }
        }
    } while(!validateMatrixA(matrixA, matrixS, k));

    return matrixA;
}

int validateMatrixA(MatrixStruct matrixToValidate, MatrixStruct matrixS, int k) {

    if(getMatrixRange(matrixToValidate) != k)
    {
        return 0;
    }

    MatrixStruct transposeMatrix = newEmptyMatrixStruct();
    MatrixStruct multiplicationResultMatrix = newEmptyMatrixStruct();

    transposeMatrixStruct(matrixToValidate, transposeMatrix);
    multiplyMatrixStructs(transposeMatrix, matrixToValidate, multiplicationResultMatrix);

    if(getDeterminant(multiplicationResultMatrix) == 0)
    {
        return 0;
    }

    MatrixStruct proyectionMatrixToValidate = newEmptyMatrixStruct();
    proyectionMatrix(matrixToValidate, proyectionMatrixToValidate);

    MatrixStruct matrixRToValidate = newEmptyMatrixStruct();
    matrixRToValidate = subMatrixWithoutModule(matrixS, proyectionMatrixToValidate);

    for(int i=0; i<matrixRToValidate->rows; i++)
    {
        for(int j=0; j<matrixRToValidate->cols; j++)
        {
            if(matrixRToValidate->matrix[i][j] > 250 || matrixRToValidate->matrix[i][j] < 0)
                return 0;
        }
    }
    
    return 1;
}

