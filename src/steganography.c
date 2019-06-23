#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include "steganography.h"
#include "BMPLibrary.h"

void hideMatricesInImagesWithLSB(MatrixStruct* matricesToHide, char* imagesFolderPath, int steganographyMode, int matricesAmount)
{
	DIR* directory;
    struct dirent* directoryFile;
    int imageFilePathLength;

    int currentMatrixToHideIndex = 0;

    if ((directory = opendir (imagesFolderPath)) == NULL) 
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        return;
    }

    int currentShadowImage = 1;
    while ((directoryFile = readdir(directory))) 
    {
        if (!strcmp (directoryFile->d_name, "."))
        	continue;

        if(!strcmp (directoryFile->d_name, ".."))
        	continue;

        imageFilePathLength = strlen(imagesFolderPath) + strlen(directoryFile->d_name) + 1;
        char imageFilePath[imageFilePathLength];

        memset(imageFilePath, 0, imageFilePathLength);

        strncpy(imageFilePath, imagesFolderPath, strlen(imagesFolderPath));
        strcat(imageFilePath, directoryFile->d_name);

        bitmapFileHeader BMPFileHeader;
		bitmapInformationHeader BMPInformationHeader;
		readBMPFile(imageFilePath, &BMPFileHeader, &BMPInformationHeader);

		unsigned char* pixelArray;
		pixelArray = getBitmapArrayFromBMPFile(imageFilePath, &BMPFileHeader, &BMPInformationHeader);

		int pixelArrayLength = BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight*3;

		int currentPixelIndex = 0;

		while(currentPixelIndex<pixelArrayLength && currentMatrixToHideIndex<matricesAmount)
		{
			MatrixStruct currentMatrixToHide = matricesToHide[currentMatrixToHideIndex];

			for(int i=0; i<currentMatrixToHide->rows; i++)
			{
				for(int j=0; j<currentMatrixToHide->cols; j++)
				{
					int currentBit;
					int valueToHide = currentMatrixToHide->matrix[i][j];

					for(currentBit = 0; currentBit < 8; currentBit++)
					{
						if(steganographyMode == LSB_MODE)
						{
							SET_BIT(pixelArray[currentPixelIndex], 0, GET_BIT(valueToHide, 7-currentBit));
						}

						if(steganographyMode == LSB2_MODE)
						{
							SET_BIT(pixelArray[currentPixelIndex], 0, GET_BIT(valueToHide, 7-currentBit));
							currentBit++;
							SET_BIT(pixelArray[currentPixelIndex], 1, GET_BIT(valueToHide, 7-currentBit));
						}

						currentPixelIndex++;
					}
				}
			}
			currentMatrixToHideIndex++;
		}

		BMPFileHeader.reservedField_1 = currentShadowImage;
		writeBMPFile(imageFilePath, &BMPFileHeader, &BMPInformationHeader, pixelArray, NULL);
	    free(pixelArray);
		currentShadowImage++;
    }
}

MatrixStruct* retreiveMatricesFromImagesWithLSB(char* imagesFolderPath, int steganographyMode, int rows, int cols, int matricesToRetreiveAmount)
{
	DIR* directory;

    if ((directory = opendir (imagesFolderPath)) == NULL) 
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        return NULL;
    }

   	struct dirent* directoryFile;

    int imageFilePathLength;

    int currentMatrixToRetreiveIndex = 0;
    MatrixStruct* matricesRetreived = malloc(sizeof(MatrixStruct) * matricesToRetreiveAmount);

    while ((directoryFile = readdir(directory))) 
    {
        if (!strcmp (directoryFile->d_name, "."))
        	continue;

        if(!strcmp (directoryFile->d_name, ".."))
        	continue;

        imageFilePathLength = strlen(imagesFolderPath) + strlen(directoryFile->d_name) + 1;
        char imageFilePath[imageFilePathLength];

        memset(imageFilePath, 0, imageFilePathLength);

        strncpy(imageFilePath, imagesFolderPath, strlen(imagesFolderPath));
        strcat(imageFilePath, directoryFile->d_name);

        bitmapFileHeader BMPFileHeader;
		bitmapInformationHeader BMPInformationHeader;
		unsigned char* pixelArray;

		readBMPFile(imageFilePath, &BMPFileHeader, &BMPInformationHeader);

		pixelArray = getBitmapArrayFromBMPFile(imageFilePath, &BMPFileHeader, &BMPInformationHeader);
		int pixelArrayLength = BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight*3;

		int currentPixelIndex = 0;

		while(currentPixelIndex<pixelArrayLength)
		{
			MatrixStruct currentMatrixToRetreive = newZeroMatrixStruct(rows, cols);

			for(int i=0; i<currentMatrixToRetreive->rows; i++)
			{
				for(int j=0; j<currentMatrixToRetreive->cols; j++)
				{
					int currentBit;
					int valueToRetreive = 0;
					for(currentBit = 0; currentBit < 8; currentBit++)
					{

						if(steganographyMode == LSB_MODE)
						{
							SET_BIT(valueToRetreive, 7-currentBit, GET_BIT(pixelArray[currentPixelIndex], 0));
						}

						if(steganographyMode == LSB2_MODE)
						{
							SET_BIT(valueToRetreive, 7-currentBit, GET_BIT(pixelArray[currentPixelIndex], 0));
							currentBit++;
							SET_BIT(valueToRetreive, 7-currentBit, GET_BIT(pixelArray[currentPixelIndex], 1));
						}

						currentPixelIndex++;
					}
					currentMatrixToRetreive->matrix[i][j] = valueToRetreive;
				}

			}

			matricesRetreived[currentMatrixToRetreiveIndex] = currentMatrixToRetreive;
			currentMatrixToRetreiveIndex++;
		}
    }
    return matricesRetreived;
}

int validateCarrierImages(int secretImageSize, int n, char* imagesFolderPath)
{
	DIR* directory;
    struct dirent* directoryFile;
    int imageFilePathLength;
    int validImages = 0;

    if ((directory = opendir (imagesFolderPath)) == NULL) 
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        return 0;
    }

    while ((directoryFile = readdir(directory))) 
    {
        if (!strcmp (directoryFile->d_name, "."))
        	continue;

        if(!strcmp (directoryFile->d_name, ".."))
        	continue;

        imageFilePathLength = strlen(imagesFolderPath) + strlen(directoryFile->d_name) + 1;
        char imageFilePath[imageFilePathLength];

        memset(imageFilePath, 0, imageFilePathLength);

        strncpy(imageFilePath, imagesFolderPath, strlen(imagesFolderPath));
        strcat(imageFilePath, directoryFile->d_name);

        bitmapFileHeader BMPFileHeader;
		bitmapInformationHeader BMPInformationHeader;
		
		if(readBMPFile(imageFilePath, &BMPFileHeader, &BMPInformationHeader) == 1)
		{
			if((BMPInformationHeader.bitmapHeight*BMPInformationHeader.bitmapWidth == secretImageSize)
				&& BMPInformationHeader.bitsPerPixel == 24)
				validImages++;
		}
    }

    if(validImages != n)
    {
    	printf("Invalid carrier images folder, make sure images have same width and height than the secret image, and that they are 24 bits per pixel\n");
    	return 0;
    }

    return 1;
}