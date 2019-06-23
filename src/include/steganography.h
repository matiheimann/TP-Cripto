
#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include "matrixStruct.h"

#define SET_BIT(number, bitPosition, bitValue) (number)  = (((number) & ~(1<<(bitPosition))) | ((bitValue)<<(bitPosition))) 
#define GET_BIT(number, bitPosition) ((number & (1 << ((bitPosition)))) > 0 ? 1 : 0)

#define LSB_MODE 1
#define LSB2_MODE 2

void hideMatricesInImagesWithLSB(MatrixStruct* matricesToHide, char* imagesFolderPath, int steganographyMode, int matricesAmount);

MatrixStruct* retreiveMatricesFromImagesWithLSB(char* imagesFolderPath, int steganographyMode, int rows, int cols, int matricesToRetreiveAmount);

int validateCarrierImages(int secretImageSize, int n, char* imagesFolderPath);
#endif