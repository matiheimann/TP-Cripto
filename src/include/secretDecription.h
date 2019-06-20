//
// Created by mheimann on 20/06/19.
//

#ifndef TP_CRIPTO_SECRETDECRIPTION_H
#define TP_CRIPTO_SECRETDECRIPTION_H

#include "matrixStruct.h"

MatrixStruct recoverMatrixS(MatrixStruct matrixDoubleS, MatrixStruct matrixR);
MatrixStruct recoverMatrixW(MatrixStruct matrixDoubleS, MatrixStruct matrixRw);
MatrixStruct recoverMatrixR(MatrixStruct* matrixG);
MatrixStruct recoverMatrixDoubleS(MatrixStruct* matrixSh, int size);
MatrixStruct recoverMatrixG(MatrixStruct matrixSh);


#endif //TP_CRIPTO_SECRETDECRIPTION_H
