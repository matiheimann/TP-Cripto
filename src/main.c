#include <stdlib.h>
#include <stdio.h>
#include "include/BMPLibrary.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		return 0;
	}

	bitmapFileHeader BMPFileHeader;
	bitmapInformationHeader BMPInformationHeader;
	unsigned char* bitmapArray;

	readBMPFile(argv[1], &BMPFileHeader, &BMPInformationHeader);

	bitmapArray = getBitmapArrayFromBMPFile(argv[1], &BMPFileHeader, &BMPInformationHeader);

	if(bitmapArray == NULL)
	{
		return 1;
	}

	//Write bmp file test
	writeBMPFile("$HOME/test.bmp", &BMPFileHeader, &BMPInformationHeader, bitmapArray);
}
