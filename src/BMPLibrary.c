#include <stdio.h>
#include <stdlib.h>
#include "BMPLibrary.h"

char isValidBMPHeader(bitmapFileHeader* bmpHeaderToValidate)
{
	if (bmpHeaderToValidate->fileType != VALID_BMP_FILE_ID)
	{
		return FALSE;
	}

	return TRUE;
}

int readBMPFile(char* filename, bitmapFileHeader* outFileHeader, bitmapInformationHeader* outInformationHeader)
{
    FILE* filePointer; 
    filePointer = fopen(filename,"rb");

    if (filePointer == NULL)
    {
        printf("Error opening file, invalid path\n");
        return -1;
    }

    fread(outFileHeader, sizeof(bitmapFileHeader), 1, filePointer);

    if(!isValidBMPHeader(outFileHeader))
    {
        fclose(filePointer);
        printf("Error opening file, invalid bmp image\n");
        return -1;
    }

    fread(outInformationHeader, sizeof(bitmapInformationHeader), 1, filePointer); 

    fclose(filePointer);
    return 1;
}

int writeBMPFile(char* filePath, bitmapFileHeader* fileHeader, bitmapInformationHeader* informationHeader, unsigned char* pixelArray)
{
    FILE* filePointer; 
    filePointer = fopen(filePath,"wb");

    if(filePointer == NULL)
    {
        printf("Error creating file\n");
        return -1;
    }

    if(fwrite(fileHeader, sizeof(bitmapFileHeader), 1, filePointer) != 1)
    {
        printf("Error writing file header\n");
        fclose(filePointer);
        return -1;
    }

    if(fwrite(informationHeader, sizeof(bitmapInformationHeader), 1, filePointer) != 1)
    {
        printf("Error writing information header\n");
        fclose(filePointer);
        return -1;
    }

    fseek(filePointer, fileHeader->offsetBitsFromHeaderToBitmap, SEEK_SET);

    if(fwrite(pixelArray, 1, informationHeader->imageSize, filePointer) != informationHeader->imageSize)
    {
        printf("Error writing bitmap array\n");
        fclose(filePointer);
        return -1;
    }

    fclose(filePointer);
    return 1;
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

unsigned char* getBitmapArrayFromBMPFile(char* BMPFile, bitmapFileHeader* fileHeader, bitmapInformationHeader* BMPInfoHeader)
{
    FILE* filePointer; 
    unsigned char* bitmapImageData;

    filePointer = fopen(BMPFile,"rb");

    if (filePointer == NULL)
    {
        printf("error\n");
        return NULL;
    }

    bitmapImageData = (unsigned char*) malloc(BMPInfoHeader->imageSize);

    if (bitmapImageData == NULL)
    {
        free(bitmapImageData);
        fclose(filePointer);
        printf("error\n");
        return NULL;
    }

    fseek(filePointer, fileHeader->offsetBitsFromHeaderToBitmap, SEEK_SET);
    fread(bitmapImageData, BMPInfoHeader->imageSize, 1, filePointer);

    if (bitmapImageData == NULL)
    {
        fclose(filePointer);
        printf("error\n");
        return NULL;
    }

    fclose(filePointer); 
    return bitmapImageData;
}