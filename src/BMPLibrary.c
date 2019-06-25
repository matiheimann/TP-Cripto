#include <stdio.h>
#include <stdlib.h>
#include "BMPLibrary.h"

int validateImageToHide(char* imageToValidate, int n)
{
    bitmapFileHeader BMPFileHeader;
    bitmapInformationHeader BMPInformationHeader;

    int readSuccess = readBMPFile(imageToValidate, &BMPFileHeader, &BMPInformationHeader);

    if(readSuccess == 0)
        return readSuccess;

    if(BMPInformationHeader.bitsPerPixel != 8)
    {
        printf("Invalid secret image, it must be 8 bits per pixel\n");
        return 0;
    }

    if((BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight % (n*n)) != 0)
    {
        printf("Invalid secret image, it must be divisible by n*n\n");
        return 0;
    }


    return 1;
}

int validateWatermarkImage(char* imageToHide, char* watermarkImage)
{
    bitmapFileHeader watermarkFileHeader;
    bitmapInformationHeader watermarkInformationHeader;

    int readSuccess = readBMPFile(watermarkImage, &watermarkFileHeader, &watermarkInformationHeader);

    if(readSuccess == 1)
    {
        if(watermarkInformationHeader.bitsPerPixel != 8)
        {
            printf("Invalid watermark image, it must be 8 bits per pixel\n");
        }
        
        bitmapFileHeader imageToHideFileHeader;
        bitmapInformationHeader imageToHideInformationHeader;

        int secretImageRead = readBMPFile(imageToHide, &imageToHideFileHeader, &imageToHideInformationHeader);
    
        if(secretImageRead == 1)
        {
            if((watermarkInformationHeader.bitmapWidth == imageToHideInformationHeader.bitmapWidth)
                && (watermarkInformationHeader.bitmapHeight == imageToHideInformationHeader.bitmapHeight))
                return 1;
            else
            {
                printf("Invalid watermark image, it must be of same width and height than the secret image\n");
            }
        }
    }

    return 0;
}

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
        printf("Error opening bmp file, invalid path\n");
        return 0;
    }

    fread(outFileHeader, sizeof(bitmapFileHeader), 1, filePointer);

    if(!isValidBMPHeader(outFileHeader))
    {
        fclose(filePointer);
        printf("Error opening bmp file, invalid bmp format\n");
        return 0;
    }

    fread(outInformationHeader, sizeof(bitmapInformationHeader), 1, filePointer); 

    fclose(filePointer);
    return 1;
}

int writeBMPFile(char* filePath, bitmapFileHeader* fileHeader, bitmapInformationHeader* informationHeader, unsigned char* pixelArray, unsigned char* extraData)
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

    if(extraData != NULL)
    {
        if(fwrite(extraData, fileHeader->fileOffset - sizeof(bitmapInformationHeader) - sizeof(bitmapFileHeader), 1, filePointer) != 1)
        {
            printf("Error writing information header\n");
            fclose(filePointer);
            return -1;
        }
    }

    if(fwrite(pixelArray, 1, (informationHeader->bitsPerPixel/8) * informationHeader->bitmapWidth * informationHeader->bitmapHeight, filePointer) != informationHeader->imageSize)
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
    printf("Offset bits -> %u \n", fileHeaderToPrint->fileOffset);
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

    bitmapImageData = (unsigned char*) malloc((BMPInfoHeader->bitsPerPixel/8) * BMPInfoHeader->bitmapWidth * BMPInfoHeader->bitmapHeight);

    if (bitmapImageData == NULL)
    {
        free(bitmapImageData);
        fclose(filePointer);
        printf("error\n");
        return NULL;
    }

    fseek(filePointer, fileHeader->fileOffset, SEEK_SET);
    fread(bitmapImageData, (BMPInfoHeader->bitsPerPixel/8) * BMPInfoHeader->bitmapWidth * BMPInfoHeader->bitmapHeight, 1, filePointer);

    if (bitmapImageData == NULL)
    {
        fclose(filePointer);
        printf("error\n");
        return NULL;
    }

    fclose(filePointer); 
    return bitmapImageData;
}

unsigned char* getExtraDataFromImage(char* BMPFile, bitmapFileHeader* fileHeader, bitmapInformationHeader* BMPInfoHeader)
{
    int extraDataLength = fileHeader->fileOffset - sizeof(bitmapFileHeader) - sizeof(bitmapInformationHeader);

    if(extraDataLength <= 0)
        return NULL;

    FILE* filePointer; 
    filePointer = fopen(BMPFile,"rb");

    if (filePointer == NULL)
    {
        printf("error opening bmp file\n");
        return NULL;
    }

    unsigned char* extraData = malloc(extraDataLength);

    fseek(filePointer, sizeof(bitmapFileHeader) + sizeof(bitmapInformationHeader), SEEK_SET);
    fread(extraData, extraDataLength, 1, filePointer);
    
    return extraData;
}