#ifndef MATRICES_RESOLVER_SECRETSHARING_H
#define MATRICES_RESOLVER_SECRETSHARING_H

#include "matrixStruct.h"
#include "matrixList.h"

void costructImageShare(MatrixStruct matrixS, int n, int k, MatrixStruct waterMark);

MatrixStruct generateMatrixX(int n, int k);

MatrixStruct generateMatrixA(MatrixStruct matrixS, int n, int k);

int validateMatrixA(MatrixStruct matrixToValidate, MatrixStruct matrixS, int k);

MatrixStruct generateMatrixSdouble(MatrixStruct matrixA);

MatrixStruct generateMatrixR(MatrixStruct matrixS, MatrixStruct matrixSdouble);

MatrixList generateMatrixsXList(int n, int k);

MatrixStruct generateMatrixV(MatrixStruct matrixA, MatrixStruct matrixX);

MatrixStruct* generateMatrixListG(MatrixStruct matrixR, int k);

MatrixStruct generateMatrixListRw(MatrixStruct waterMark, MatrixStruct matrixSdouble);

MatrixStruct* generateMatrixListSh(MatrixStruct matrixV, MatrixStruct* matrixListG);

bool verifyImage(MatrixStruct matrixS, MatrixStruct watermark, MatrixStruct matrixR, MatrixStruct matrixSdouble);


#endif //MATRICES_RESOLVER_SECRETSHARING_H
