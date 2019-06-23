#ifndef MATRICES_RESOLVER_SECRETSHARING_H
#define MATRICES_RESOLVER_SECRETSHARING_H

#include "matrixStruct.h"
#include "matrixList.h"
#include "BMPLibrary.h"

struct imageShare {

    MatrixStruct* ShMatrices;
    int ShMatricesAmount;

    MatrixStruct* RwMatrices;
    int RwMatricesAmount;
};

typedef struct imageShare ImageShares;

MatrixStruct* constructImageShare(MatrixStruct matrixS, int k, MatrixStruct matrixW);

MatrixStruct generateMatrixX(int n, int k);

MatrixStruct generateMatrixA(MatrixStruct matrixS, int n, int k);

int validateMatrixA(MatrixStruct matrixToValidate, MatrixStruct matrixS, int k);

MatrixStruct generateMatrixSdouble(MatrixStruct matrixA);

MatrixStruct generateMatrixR(MatrixStruct matrixS, MatrixStruct matrixSdouble);

MatrixStruct generateMatrixV(MatrixStruct matrixA, MatrixStruct matrixX);

MatrixStruct* generateMatrixListG(MatrixStruct matrixR, int k);

MatrixStruct generateMatrixListRw(MatrixStruct matrixW, MatrixStruct matrixSdouble);

MatrixStruct* generateMatrixListSh(MatrixStruct matrixV, MatrixStruct* matrixListG);

bool verifyImage(MatrixStruct matrixS, MatrixStruct watermark, MatrixStruct matrixR, MatrixStruct matrixSdouble);

MatrixStruct* retreiveSquaredMatricesFromImage(char* imageFilePath, int matrixDimension);

void createImageFromMatrices(MatrixStruct* matrices, int dimension, int matricesAmount, char* filePath, bitmapFileHeader* fileHeader, bitmapInformationHeader* informationHeader, unsigned char* extraData);

unsigned char* getBitmapArrayFromMatrices(MatrixStruct* matrices, int dimension, int matricesAmount);

#endif //MATRICES_RESOLVER_SECRETSHARING_H
