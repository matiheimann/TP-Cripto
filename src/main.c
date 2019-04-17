#include <stdlib.h>
#include "include/BMPLibrary.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		return 0;
	}

	bitmapInformationHeader informationHeader;
	unsigned char** bitmapMatrix;

	bitmapMatrix = getBitmapMatrixFromBMPFile(argv[1], &informationHeader);

	if(bitmapMatrix != NULL)
	{
		printBMPInformationHeader(&informationHeader);
		free(bitmapMatrix);
		return 1;
	}

	return 0;
}
