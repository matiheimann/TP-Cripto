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

unsigned char* loadBitmapFile(char* filename, bitmapInformationHeader* bitmapInfoHeader);

void swapBGRToRGB(unsigned char* imageBitmap, unsigned int imageSize);

char isValidBMPHeader(bitmapFileHeader* bmpHeaderToValidate);

void printBMPFileHeader(bitmapFileHeader* fileHeaderToPrint);

void printBMPInformationHeader(bitmapInformationHeader* informationHeaderToPrint);

#endif