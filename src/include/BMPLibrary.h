#ifndef BMP_LIBRARY_H
#define BMP_LIBRARY_H

#define VALID_BMP_FILE_ID 0x4D42

#define TRUE 1
#define FALSE 0

#pragma pack(push, 1)

typedef struct bitmapFileHeaderStruct
{
    unsigned short fileType;  
    unsigned int fileSize;
    unsigned short reservedField_1;
    unsigned short reservedField_2;
    unsigned int offsetBitsFromHeaderToBitmap;
} bitmapFileHeader;

typedef struct bitmapInformationHeaderStruct
{
    unsigned int headerSize;
    int bitmapWidth;
    int bitmapHeight;
    unsigned short colorPlanes;
    unsigned short bitsPerPixel;
    unsigned int compressionType;
    unsigned int imageSize;
    int pixelsPerMeterOnXAxis;
    int pixelsPerMeterOnYAxis;
    unsigned int numberOfColorsUsed;
    unsigned int numberOfImportantColors;
} bitmapInformationHeader;

#pragma pack(pop)

char isValidBMPHeader(bitmapFileHeader* bmpHeaderToValidate);

int readBMPFile(char* filename, bitmapFileHeader* outFileHeader, bitmapInformationHeader* outInformationHeader);

int writeBMPFile(char* filePath, bitmapFileHeader* fileHeader, bitmapInformationHeader* informationHeader, unsigned char* pixelArray);

void printBMPFileHeader(bitmapFileHeader* fileHeaderToPrint);

void printBMPInformationHeader(bitmapInformationHeader* informationHeaderToPrint);

unsigned char* getBitmapArrayFromBMPFile(char* BMPFile, bitmapFileHeader* fileHeader, bitmapInformationHeader* BMPInfoHeader);

#endif