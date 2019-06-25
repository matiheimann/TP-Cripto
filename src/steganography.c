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

    int currentShadowImage = 0;
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

MatrixStruct* selectMatricesToHide(MatrixStruct* matricesToHide, int matricesShareNumber, int n, int ShMatricesPerParticipant)
{
	MatrixStruct* matrixShares = malloc(sizeof(MatrixStruct) * ShMatricesPerParticipant);

	for(int i=0; i<ShMatricesPerParticipant; i++)
	{
		matrixShares[i] = matricesToHide[((matricesShareNumber-1)*n)+i];
	}

	return matrixShares;
}

ShadowedShares retreiveMatricesFromImagesWithLSB(char* imagesFolderPath, int steganographyMode, int n, int k, int ShMatricesPerParticipant, int ShMatricesAmount)
{
	DIR* directory;

    if ((directory = opendir (imagesFolderPath)) == NULL)
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        ShadowedShares shadowedImageShares;
  	    shadowedImageShares.ShMatrices = NULL;
    	  shadowedImageShares.associatedShadows = NULL;
        return shadowedImageShares;
    }

   	struct dirent* directoryFile;

    int imageFilePathLength;

	  int* associatedShadowNumbers = malloc(sizeof(int) * ShMatricesAmount);

    MatrixStruct* matricesRetreived = malloc(sizeof(MatrixStruct) * ShMatricesAmount);
    int matricesRetreivedIndex = 0;
    int imagesRead = 0;
    while ((directoryFile = readdir(directory)) && imagesRead < k)
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

    		MatrixStruct* currentMatricesRetreived = malloc(sizeof(MatrixStruct) * ShMatricesPerParticipant);

       		int currentMatrixToRetreiveIndex = 0;

    		while(currentPixelIndex<pixelArrayLength)
    		{
    			MatrixStruct currentMatrixToRetreive = newZeroMatrixStruct(n, (n/k)+1);

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
    							SET_BIT(valueToRetreive, 7-currentBit, GET_BIT(pixelArray[currentPixelIndex], 1));
    							currentBit++;
    							SET_BIT(valueToRetreive, 7-currentBit, GET_BIT(pixelArray[currentPixelIndex], 0));
    						}

    						currentPixelIndex++;
    					}
    					currentMatrixToRetreive->matrix[i][j] = valueToRetreive;
    				}
    			}

    			currentMatricesRetreived[currentMatrixToRetreiveIndex] = currentMatrixToRetreive;
    			currentMatrixToRetreiveIndex++;
    		}

    		for(int w=0; w<ShMatricesPerParticipant; w++)
    		{
    			matricesRetreived[matricesRetreivedIndex] = currentMatricesRetreived[w];
    			associatedShadowNumbers[matricesRetreivedIndex] = BMPFileHeader.reservedField_1;
    			matricesRetreivedIndex++;
    		}
		    imagesRead++;
    }
    ShadowedShares shadowedImageShares;
    shadowedImageShares.ShMatrices = matricesRetreived;

    shadowedImageShares.associatedShadows = associatedShadowNumbers;

    return shadowedImageShares;
}

int validateCarrierImages(int secretImageSize, int requiredImages, char* imagesFolderPath)
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
    if(validImages < requiredImages)
    {
    	printf("Invalid carrier images folder, make sure images have same width and height than the secret image, and that they are 24 bits per pixel\n");
    	return 0;
    }

    return 1;
}

int validateCarrierImagesForRecovery(int requiredImages, char* imagesFolderPath)
{
	  DIR* directory;
    struct dirent* directoryFile;
    int imageFilePathLength;
    int validImages = 0;

    int firstImageWidth;
    int firstImageHeight;

    int firstImageChecked = 0;

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
    			if(firstImageChecked == 0)
    			{
    				firstImageHeight = BMPInformationHeader.bitmapHeight;
    				firstImageWidth = BMPInformationHeader.bitmapWidth;
    				firstImageChecked = 1;
    			}

    			if(BMPInformationHeader.bitmapHeight == firstImageHeight && BMPInformationHeader.bitmapWidth == firstImageWidth
    				&& BMPInformationHeader.bitsPerPixel == 24)
    				validImages++;
    		}
    }

    if(validImages < requiredImages)
    {
    	printf("Invalid carrier images folder, make sure images have same width and height than the secret image, and that they are 24 bits per pixel\n");
    	return 0;
    }

    return 1;
}
