//
// Created by mheimann on 20/06/19.
//

#ifndef TP_CRIPTO_SECRETDECRIPTION_H
#define TP_CRIPTO_SECRETDECRIPTION_H

#include "matrixStruct.h"

MatrixStruct recoverMatrixS(MatrixStruct* matrixDoubleS, MatrixStruct matrixR);
MatrixStruct recoverMatrixW(MatrixStruct* matrixDoubleS, MatrixStruct matrixRw);
MatrixStruct recoverMatirxR(MatrixStruct* matrixG, MatrixStruct matrixSh);
MatrixStruct recoverMatrixDoubleS(MatrixStruct* matrixSh, int size);
MatrixStruct recoverMatrixG(MatrixStruct matrixSh, MatrixStruct matrixV);


#endif //TP_CRIPTO_SECRETDECRIPTION_H
