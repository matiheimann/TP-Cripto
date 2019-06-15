//
// Created by lococo on 14/06/19.
//

#ifndef MATRICES_RESOLVER_SECRETSHARING_H
#define MATRICES_RESOLVER_SECRETSHARING_H

#include "matrixStruct.h"
#include "matrixList.h"

void costructImageShare(MatrixStruct matrixS, int n, int k, MatrixStruct waterMark);

MatrixList generateMatrixXList(int n, int k);

MatrixStruct generateMatrixA(int n, int k);

MatrixStruct generateMatrixSdouble(MatrixStruct matrixA);

MatrixStruct generateMatrixR(MatrixStruct matrixS, MatrixStruct matrixSdouble);

MatrixList generateMatrixsXList(int n, int k);

MatrixList generateMatrixVList(MatrixStruct matrixA, MatrixList matrixXlist);

MatrixList generateMatrixListG(MatrixStruct matrixR, MatrixList matrixListV);

MatrixStruct generateMatrixListRw(MatrixStruct waterMark, MatrixStruct matrixSdouble);

MatrixList generateMatrixListSh(MatrixList matrixListV, MatrixList matrixListG);

#endif //MATRICES_RESOLVER_SECRETSHARING_H
