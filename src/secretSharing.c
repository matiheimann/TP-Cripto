#include "include/secretSharing.h"
#include "include/matrixStruct.h"
#include "include/matrixList.h"
#include "include/random.h"
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

MatrixStruct* constructImageShare(MatrixStruct matrixS, int k, MatrixStruct matrixW)
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
        ret[i] = newZeroMatrixStruct(n, matrixListG[0]->cols +1);
        for(int j = 0; j < n; j++){
            ret[i]->matrix[j][0] = matrixV->matrix[j][i];
            for(int w = 0; w < (n/k); w++){
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
        ret[i-1] = newZeroMatrixStruct(n, n/k);
        for(int j = 0; j < n; j++){
            for(int w = 0; w < n/k; w++)
            {
                int pot = 1;
                for(int y = 0; y < k; y++)
                {
                        ret[i - 1]->matrix[j][w] += matrixR->matrix[j][w*k + y] * pot;
                        ret[i - 1]->matrix[j][w] = ret[i - 1]->matrix[j][w] % 251;
                        pot *= i;
                        pot = pot % 251;
                }
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
        freeMatrixStr(aux);
        freeMatrixStr(ans);
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

    MatrixStruct matrixRToValidate = newZeroMatrixStruct(matrixS->rows, matrixS->cols);
    substractMatrix(matrixS, proyectionMatrixToValidate, matrixRToValidate);

    for(int i=0; i<matrixRToValidate->rows; i++)
    {
        for(int j=0; j<matrixRToValidate->cols; j++)
        {
            if(matrixRToValidate->matrix[i][j] % 251 > 250) {
                return 0;
            }
            matrixRToValidate->matrix[i][j] = matrixRToValidate->matrix[i][j] % 256;
        }
    }

    return 1;
}

MatrixStruct* retreiveSquaredMatricesFromImage(char* imageFilePath, int matrixDimension)
{
    bitmapFileHeader BMPFileHeader;
    bitmapInformationHeader BMPInformationHeader;
    unsigned char* bitmapArray;

    readBMPFile(imageFilePath, &BMPFileHeader, &BMPInformationHeader);
    bitmapArray = getBitmapArrayFromBMPFile(imageFilePath, &BMPFileHeader, &BMPInformationHeader);

    int currentPixelIndex = 0;
    int bitmapArrayLength = BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight;

    MatrixStruct* matricesToReturn = malloc(sizeof(MatrixStruct));
    int currentMatrixIndex = 0;

    while(currentPixelIndex < bitmapArrayLength)
    {
        int i,j;
        MatrixStruct currentMatrix = newZeroMatrixStruct(matrixDimension, matrixDimension);

        for(i=0; i<matrixDimension; i++)
        {
            for(j=0; j<matrixDimension; j++)
            {
                currentMatrix->matrix[i][j] = bitmapArray[currentPixelIndex];
                currentPixelIndex++;
            }
        }

        matricesToReturn = realloc(matricesToReturn, sizeof(MatrixStruct)*(currentMatrixIndex + 1));

        matricesToReturn[currentMatrixIndex] = currentMatrix;
        currentMatrixIndex++;
    }

    free(bitmapArray);
    return matricesToReturn;
}

void createImageFromMatrices(MatrixStruct* matrices, int dimension, int matricesAmount, char* filePath, bitmapFileHeader* fileHeader, bitmapInformationHeader* informationHeader, unsigned char* extraData)
{
    unsigned char* bitmapArray = getBitmapArrayFromMatrices(matrices, dimension, matricesAmount);

    writeBMPFile(filePath, fileHeader, informationHeader, bitmapArray, extraData);
    free(bitmapArray);
}

unsigned char* getBitmapArrayFromMatrices(MatrixStruct* matrices, int dimension, int matricesAmount)
{
    int bitmapArrayLength = dimension*dimension*matricesAmount;
    unsigned char* bitmapArray = malloc(bitmapArrayLength);

    int currentMatrix = 0;
    int currentPixel = 0;
    while(currentMatrix < matricesAmount)
    {
        int i,j;
        for(i=0; i<dimension; i++)
        {
            for(j=0; j<dimension; j++)
            {
                bitmapArray[currentPixel] = matrices[currentMatrix]->matrix[i][j];
                currentPixel++;
            }
        }

        currentMatrix++;
    }

    return bitmapArray;
}
