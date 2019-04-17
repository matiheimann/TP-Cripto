#include <stdio.h>
#include <stdlib.h>
#include "BMPLibrary.h"

unsigned char** getBitmapMatrixFromBMPFile(char* filenameToLoad, bitmapInformationHeader* outInformationHeader)
{
	FILE* filePointer; 
    bitmapFileHeader fileHeader; 
    unsigned char *bitmapImageData;

    filePointer = fopen(filenameToLoad,"rb");

    if (filePointer == NULL)
    {
        return NULL;
    }

    fread(&fileHeader, sizeof(bitmapFileHeader), 1, filePointer);

    if(!isValidBMPHeader(&fileHeader))
    {
	   	fclose(filePointer);
        return NULL;
    }

    fread(outInformationHeader, sizeof(bitmapInformationHeader), 1, filePointer);

    if(outInformationHeader->bitmapHeight != outInformationHeader->bitmapWidth)
    {
        printf("Invalid image, it must be of equal height and width\n");
        fclose(filePointer);
        return NULL;
    }

    bitmapImageData = (unsigned char*) malloc(outInformationHeader->imageSize);

    if (bitmapImageData == NULL)
    {
        free(bitmapImageData);
        fclose(filePointer);
        return NULL;
    }

    fseek(filePointer, fileHeader.offsetBitsFromHeaderToBitmap, SEEK_SET);
    fread(bitmapImageData, outInformationHeader->imageSize, 1, filePointer);

    if (bitmapImageData == NULL)
    {
        fclose(filePointer);
        return NULL;
    }

    swapBGRToRGB(bitmapImageData, outInformationHeader->imageSize);

    fclose(filePointer);

    unsigned char** bitmapMatrixToReturn = getMatrixFromBitmapArray(bitmapImageData, outInformationHeader->bitmapHeight);
 
    free(bitmapImageData);

    return bitmapMatrixToReturn;
}

char isValidBMPHeader(bitmapFileHeader* bmpHeaderToValidate)
{
	if (bmpHeaderToValidate->fileType != VALID_BMP_FILE_ID)
	{
		return FALSE;
	}

	return TRUE;
}

unsigned char** getMatrixFromBitmapArray(unsigned char* bitmapArray, int numberOfRows)
{
    unsigned char** bitmapMatrix = reserveSpaceForMatrix(numberOfRows);
    int currentRow = 0;

    int i;
    for(i=0; i<numberOfRows*numberOfRows; i++)
    {
        if(i%numberOfRows == 0)
        {
            currentRow++;
        }

        bitmapMatrix[currentRow][i%numberOfRows] = bitmapArray[i];
    }

    return bitmapMatrix;
}

unsigned char** reserveSpaceForMatrix(int numberOfRows)
{
    if(numberOfRows < 0)
    {
        printf("Invalid number of rows\n");
        return NULL;
    }

    unsigned char** bitmapMatrix = (unsigned char**) malloc(numberOfRows);

    if(bitmapMatrix == NULL)
    {
        printf("Malloc failed\n");
        return NULL;
    }

    int i;
    for(i=0; i<numberOfRows; i++)
    {
        bitmapMatrix[i] = (unsigned char*) malloc(numberOfRows);

        if(bitmapMatrix[i] == NULL)
        {
            printf("Malloc failed\n");
            free(bitmapMatrix[i]);
            return NULL;
        }
    }

    return bitmapMatrix;
}

void swapBGRToRGB(unsigned char* imageBitmap, unsigned int imageSize)
{
    unsigned char temporaryRGB;
    unsigned int i;

    for (i = 0; i < imageSize; i += 3)
    {
        temporaryRGB = imageBitmap[i];
        imageBitmap[i] = imageBitmap[i + 2];
        imageBitmap[i + 2] = temporaryRGB;
    }
}

void printBMPFileHeader(bitmapFileHeader* fileHeaderToPrint)
{
    printf("BMP file header \n");
    printf("File type -> %hi \n", fileHeaderToPrint->fileType);
    printf("File size -> %u \n", fileHeaderToPrint->fileSize);
    printf("Reserved field 1 -> %hi \n", fileHeaderToPrint->reservedField_1);
    printf("Reserved field 2 -> %hi \n", fileHeaderToPrint->reservedField_2);
    printf("Offset bits -> %u \n", fileHeaderToPrint->offsetBitsFromHeaderToBitmap);
}

void printBMPInformationHeader(bitmapInformationHeader* informationHeaderToPrint)
{
    printf("BMP information header \n");
    printf("Header size -> %u \n", informationHeaderToPrint->headerSize);
    printf("Bitmap width -> %d pixels \n", informationHeaderToPrint->bitmapWidth);
    printf("Bitmap height -> %d pixels \n", informationHeaderToPrint->bitmapHeight);
    printf("Color planes -> %hi \n", informationHeaderToPrint->colorPlanes);
    printf("Bits per pixel -> %hi \n", informationHeaderToPrint->bitsPerPixel);
    printf("Compression type -> %u \n", informationHeaderToPrint->compressionType); 
    printf("Image size -> %u \n", informationHeaderToPrint->imageSize);
    printf("Pixels per meter on X axis -> %d \n", informationHeaderToPrint->pixelsPerMeterOnXAxis);
    printf("Pixels per meter on Y axis -> %d \n", informationHeaderToPrint->pixelsPerMeterOnYAxis);
    printf("Number of color used -> %u \n", informationHeaderToPrint->numberOfColorsUsed);
    printf("Number of important colors -> %u \n", informationHeaderToPrint->numberOfImportantColors);
}