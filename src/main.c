#include <stdlib.h>
#include <stdio.h>
#include "include/BMPLibrary.h"
#include "matrixStruct.h"
#include "random.h"
#include <time.h>
#include "include/matrixStruct.h"
#include "include/secretSharing.h"

int main(int argc, char* argv[])
{
	/*if(argc < 2)
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

	writeBMPFile("$HOME/test.bmp", &BMPFileHeader, &BMPInformationHeader, bitmapArray);*/

	MatrixStruct testMatrixS = newZeroMatrixStruct(4,2);
	testMatrixS->matrix[0][1] = 62;
	testMatrixS->matrix[1][1] = 59;
	testMatrixS->matrix[2][1] = 43;
	testMatrixS->matrix[3][1] = 84;
	testMatrixS->matrix[0][0] = 83;
	testMatrixS->matrix[1][0] = 62;
	testMatrixS->matrix[2][0] = 58;
	testMatrixS->matrix[3][0] = 102;

	MatrixStruct proy = newEmptyMatrixStruct();
	proyectionMatrix(testMatrixS, proy);

	for(int i = 0; i < 4; i++){
	    for(int j = 0; j < 4; j++){
	        printf("%d ", proy->matrix[i][j]);
	    }
	    printf("\n");
	}

}
