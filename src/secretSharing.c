//
// Created by lococo on 14/06/19.
//

#include "include/secretSharing.h"
#include "include/matrixStruct.h"
#include "include/matrixList.h"
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

MatrixList generateMatrixXList(int n, int k) {
    return NULL;
}

MatrixStruct generateMatrixR(MatrixStruct matrixS, MatrixStruct matrixSdouble) {
    return NULL;
}

MatrixStruct generateMatrixSdouble(MatrixStruct matrixA) {
    return NULL;
}

MatrixStruct generateMatrixA(int n, int k) {
    return NULL;
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