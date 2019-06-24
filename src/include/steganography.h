
#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include "matrixStruct.h"

#define SET_BIT(number, bitPosition, bitValue) (number)  = (((number) & ~(1<<(bitPosition))) | ((bitValue)<<(bitPosition))) 
#define GET_BIT(number, bitPosition) ((number & (1 << ((bitPosition)))) > 0 ? 1 : 0)

#define LSB_MODE 1
#define LSB2_MODE 2

struct shadowedShare {

    MatrixStruct* ShMatrices;

    int* associatedShadows;
};

typedef struct shadowedShare ShadowedShares;

void hideMatricesInImagesWithLSB(MatrixStruct* matricesToHide, char* imagesFolderPath, int steganographyMode, int matricesAmount);

MatrixStruct* selectMatricesToHide(MatrixStruct* matricesToHide, int matricesShareNumber, int n, int ShMatricesPerParticipant);

ShadowedShares retreiveMatricesFromImagesWithLSB(char* imagesFolderPath, int steganographyMode, int n, int k, int ShMatricesPerParticipant, int ShMatricesAmount);

int validateCarrierImages(int secretImageSize, int requiredImages, char* imagesFolderPath);

int validateCarrierImagesForRecovery(int requiredImages, char* imagesFolderPath);

#endif