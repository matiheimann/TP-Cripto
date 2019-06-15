//
// Created by lococo on 14/06/19.
//

#include "include/secretSharing.h"
#include "include/matrixStruct.h"
#include "include/matrixList.h"
#include "include/random.h"
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

void costructImageShare(MatrixStruct matrixS, int n, int k, MatrixStruct waterMark)
{
    /*MatrixStruct matrixA = generateMatrixA(n, k);
    MatrixStruct matrixSdouble = generateMatrixSdouble(matrixA);
    MatrixStruct matrixR = generateMatrixR(matrixS, matrixSdouble);
    MatrixList matrixlistX = generateMatrixXList(n, k);
    MatrixList matrixlistV = generateMatrixVList(matrixA, matrixlistX);
    MatrixList matrixListG = generateMatrixListG(matrixR, matrixlistV);
    MatrixStruct matrixListRw = generateMatrixListRw(waterMark, matrixSdouble);
    MatrixList matrixListSh = generateMatrixListSh(matrixlistV, matrixListG);*/
    return;
}

MatrixList generateMatrixListSh(MatrixList matrixListV, MatrixList matrixListG) {
    return NULL;
}

MatrixStruct generateMatrixListRw(MatrixStruct waterMark, MatrixStruct matrixSdouble) {
    return NULL;
}

MatrixList generateMatrixListG(MatrixStruct matrixR, MatrixList matrixListV) {
    return NULL;
}


MatrixList generateMatrixVList(MatrixStruct matrixA, MatrixList matrixXlist) {
    return NULL;
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
        return -1;
    }

    MatrixStruct transposeMatrix = newEmptyMatrixStruct();
    MatrixStruct multiplicationResultMatrix = newEmptyMatrixStruct();

    transposeMatrixStruct(matrixToValidate, transposeMatrix);
    multiplyMatrixStructs(transposeMatrix, matrixToValidate, multiplicationResultMatrix);

    if(getDeterminant(multiplicationResultMatrix) == 0)
    {
        return -1;
    }

    MatrixStruct proyectionMatrixToValidate = newEmptyMatrixStruct();
    proyectionMatrix(matrixToValidate, proyectionMatrixToValidate);

    MatrixStruct matrixRToValidate = newEmptyMatrixStruct();
    substractMatrix(matrixS, proyectionMatrixToValidate, matrixRToValidate);

    for(int i=0; i<matrixRToValidate->rows; i++)
    {
        for(int j=0; j<matrixRToValidate->cols; j++)
        {
            if(matrixRToValidate->matrix[i][j] > 251)
                return -1;
        }
    }
    
    return 1;
}

void recoveryImageShare(MatrixList shadows, int n, int k, MatrixStruct watermark)
{
    /*MatrixStruct matrixB = recoveryMatrixB(shadows, n, k);
    MatrixStruct matrixSdouble = generateMatrixSdouble(matrixB);
    MatrixList matrixListG = recoveryMatrixG(shadows);
    MatrixStruct matrixR = recoveryMatrixR(matrixListG);
    MatrixStruct matrixS = recoveryMatrixS(matrixSdouble, matrixR);
    bool verify = verifyImage(matrixS, watermark, matrixR, matrixSdouble);*/
    return;

}

bool verifyImage(MatrixStruct matrixS, MatrixStruct watermark, MatrixStruct matrixR, MatrixStruct matrixSdouble) {
    return 0;
}

MatrixStruct recoveryMatrixS(MatrixStruct matrixSdouble, MatrixStruct matrixR) {
    return NULL;
}

MatrixStruct recoveryMatrixR(MatrixList matrixListG) {
    return NULL;
}

MatrixList recoveryMatrixG(MatrixList shadows) {
    return NULL;
}

MatrixStruct recoveryMatrixB(MatrixList shadows, int n, int k) {
    return NULL;
}