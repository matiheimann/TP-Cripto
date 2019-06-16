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

	MatrixStruct testMatrixS = newZeroMatrixStruct(4,4);

	testMatrixS->matrix[0][0] = 2;
	testMatrixS->matrix[0][1] = 5;
	testMatrixS->matrix[0][2] = 2;
	testMatrixS->matrix[0][3] = 3;
	testMatrixS->matrix[1][0] = 3;
	testMatrixS->matrix[1][1] = 6;
	testMatrixS->matrix[1][2] = 4;
	testMatrixS->matrix[1][3] = 5;
	testMatrixS->matrix[2][0] = 4;
	testMatrixS->matrix[2][1] = 7;
	testMatrixS->matrix[2][2] = 4;
	testMatrixS->matrix[2][3] = 6;
	testMatrixS->matrix[3][0] = 1;
	testMatrixS->matrix[3][1] = 4;
	testMatrixS->matrix[3][2] = 1;
	testMatrixS->matrix[3][3] = 7;

	MatrixStruct testMatrixA = newZeroMatrixStruct(4, 2);

	testMatrixA->matrix[0][0] = 3;
	testMatrixA->matrix[0][1] = 7;
	testMatrixA->matrix[1][0] = 6;
	testMatrixA->matrix[1][1] = 1;
	testMatrixA->matrix[2][0] = 2;
	testMatrixA->matrix[2][1] = 5;
	testMatrixA->matrix[3][0] = 6;
	testMatrixA->matrix[3][1] = 6;

	MatrixStruct testMatrixX = newZeroMatrixStruct(2, 4);

	testMatrixX->matrix[0][0] = 9;
	testMatrixX->matrix[1][0] = 5;

	testMatrixX->matrix[0][1] = 4;
	testMatrixX->matrix[1][1] = 4;

	testMatrixX->matrix[0][2] = 9;
	testMatrixX->matrix[1][2] = 8;

	testMatrixX->matrix[0][3] = 3;
	testMatrixX->matrix[1][3] = 2;

	MatrixStruct testMatrixV = newZeroMatrixStruct(4,4);

	testMatrixV = generateMatrixV(testMatrixA, testMatrixX);

	for(int i=0; i<testMatrixV->rows; i++)
	{
		for(int j=0; j<testMatrixV->cols; j++)
		{
			printf("%d ", testMatrixV->matrix[i][j]);
		}

		printf("\n");
	}
}
