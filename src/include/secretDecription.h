//
// Created by mheimann on 20/06/19.
//

#ifndef TP_CRIPTO_SECRETDECRIPTION_H
#define TP_CRIPTO_SECRETDECRIPTION_H

#include "matrixStruct.h"

MatrixStruct recoverMatrixS(MatrixStruct matrixDoubleS, MatrixStruct matrixR);
MatrixStruct recoverMatrixW(MatrixStruct matrixDoubleS, MatrixStruct matrixRw);
MatrixStruct recoverMatrixR(MatrixStruct* matrixG, int* shadowNumber, int size);
MatrixStruct recoverMatrixDoubleS(MatrixStruct* matrixSh, int size);
MatrixStruct recoverMatrixG(MatrixStruct matrixSh);
MatrixStruct* recoveryAlgorithm(MatrixStruct* matrixSh, MatrixStruct matrixRw, int* shadowNumber, int size);


#endif //TP_CRIPTO_SECRETDECRIPTION_H
