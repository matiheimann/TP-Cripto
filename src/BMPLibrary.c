#include <stdio.h>
#include <stdlib.h>
#include "BMPLibrary.h"

unsigned char* loadBitmapFile(char* filenameToLoad, bitmapInformationHeader* outInformationHeader)
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
    bitmapImageData = (unsigned char*) malloc(outInformationHeader->imageSize);

    if (!bitmapImageData)
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
    return bitmapImageData;
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

char isValidBMPHeader(bitmapFileHeader* bmpHeaderToValidate)
{
	if (bmpHeaderToValidate->fileType != VALID_BMP_FILE_ID)
	{
		return FALSE;
	}

	return TRUE;
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