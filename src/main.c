#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>
#include "include/ConfigurationStruct.h"
#include "include/BMPLibrary.h"
#include "matrixStruct.h"
#include "random.h"
#include "include/matrixStruct.h"
#include "include/secretSharing.h"
#include "include/steganography.h"

void distributeSecret(char* imageToHide, char* watermarkImage, int k, int n, char* carrierImagesDirectory);

ImageShares retreiveImageShares(char* imageToHide, MatrixStruct* matricesS, MatrixStruct* matricesW, int n, int k);

void distributeSecret(char* imageToHide, char* watermarkImage, int k, int n, char* carrierImagesDirectory)
{
	if(validateImageToHide(imageToHide, n) == 0)
		return;

	if(validateWatermarkImage(imageToHide, watermarkImage) == 0)
		return;

	bitmapFileHeader BMPFileHeader;
	bitmapInformationHeader BMPInformationHeader;
	readBMPFile(imageToHide, &BMPFileHeader, &BMPInformationHeader);

	if(validateCarrierImages(BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight, n, carrierImagesDirectory) == 0)
		return;

	MatrixStruct* matricesS = retreiveSquaredMatricesFromImage(imageToHide, n);
	MatrixStruct* matricesW = retreiveSquaredMatricesFromImage(watermarkImage, n);

	ImageShares imageShares = retreiveImageShares(imageToHide, matricesS, matricesW, n, k);

	int steganographyModeToUse;

	if(k==4 && n==8)
		steganographyModeToUse = LSB_MODE;

	if(k==2 && n==4)
		steganographyModeToUse = LSB2_MODE;

	hideMatricesInImagesWithLSB(imageShares.ShMatrices, carrierImagesDirectory, steganographyModeToUse, imageShares.ShMatricesAmount);

	unsigned char* extraData = getExtraDataFromImage(imageToHide, &BMPFileHeader, &BMPInformationHeader);

	createImageFromMatrices(imageShares.RwMatrices, n, imageShares.RwMatricesAmount, "RW.bmp", &BMPFileHeader, &BMPInformationHeader, extraData);
	
	//TESTS
	
	/*bitmapFileHeader BMPFileHeader;
	bitmapInformationHeader BMPInformationHeader;
	readBMPFile(imageToHide, &BMPFileHeader, &BMPInformationHeader);

	MatrixStruct* matricesS = retreiveSquaredMatricesFromImage(imageToHide, n);

	unsigned char* extraData = getExtraDataFromImage(imageToHide, &BMPFileHeader, &BMPInformationHeader);

	createImageFromMatrices(matricesS, 8, 1925, "test.bmp", &BMPFileHeader, &BMPInformationHeader, extraData);

	printBMPFileHeader(&BMPFileHeader);

	printBMPInformationHeader(&BMPInformationHeader);

	printf("%lu\n", sizeof(bitmapFileHeader));
	printf("%lu\n", sizeof(bitmapInformationHeader));*/
}

ImageShares retreiveImageShares(char* imageToHide, MatrixStruct* matricesS, MatrixStruct* matricesW, int n, int k)
{
	bitmapFileHeader BMPFileHeader;
	bitmapInformationHeader BMPInformationHeader;
	readBMPFile(imageToHide, &BMPFileHeader, &BMPInformationHeader);
  	
  	int SmatricesAmount = (BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight)/(n*n);

    MatrixStruct* matricesSh = malloc(sizeof(MatrixStruct) * SmatricesAmount * n);
    MatrixStruct* matricesRw = malloc(sizeof(MatrixStruct) * SmatricesAmount);

    int currentMatrixShIndex = 0;
    int currentMatrixRwIndex = 0;

    for(int i=0; i<SmatricesAmount; i++)
    {
    	MatrixStruct* tmp = constructImageShare(matricesS[i], k, matricesW[i]);

    	int j = 0;
    	while(j<n)
    	{
    		matricesSh[currentMatrixShIndex] = tmp[j];
    		currentMatrixShIndex++;
    		j++;
    	}

    	matricesRw[currentMatrixRwIndex] = tmp[j];
    	currentMatrixRwIndex++;
    }

    ImageShares imageShares;

    imageShares.ShMatrices = matricesSh;
    imageShares.ShMatricesAmount = SmatricesAmount * n;

    imageShares.RwMatrices = matricesRw;
	imageShares.RwMatricesAmount = SmatricesAmount;

    return imageShares;
}

int main(int argc, char* argv[])
{

	//distributeSecret(char* imageToHide, char* watermarkImage, int k, int n, char* carrierImagesDirectory);
	distributeSecret(argv[1], argv[2], 4, 8, argv[3]);
    Configuration configuration = initializeConfiguration();
    int c;
    while(((c = getopt(argc, argv, "rds:m:k:n:l:"))) != -1)
    {
        switch(c)
        {
            case 'r':
                if(configuration->isRecovery == -1)
                {
                    configuration->isRecovery = 1;
                }
            case 'd':
                if(configuration->isRecovery == -1)
                {
                    configuration->isRecovery = 0;
                }
        }
    }

	/*MatrixStruct* matricesS = retreiveSMatricesFromImage(argv[1], 8);

	bitmapFileHeader BMPFileHeader;
	bitmapInformationHeader BMPInformationHeader;
	readBMPFile(argv[1], &BMPFileHeader, &BMPInformationHeader);
  	
  	int matricesAmount = (BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight)/(8*8);
  	int matricesShAmount = matricesAmount*8;

    MatrixStruct* matricesSh = malloc(sizeof(MatrixStruct) * matricesShAmount);
    int currentMatrixShIndex = 0;
    for(int i=0; i<matricesAmount; i++)
    {
    	MatrixStruct* tmp = constructImageShare(matricesS[i], 4, matricesS[0]);

    	for(int j=0; j<8; j++)
    	{
    		matricesSh[currentMatrixShIndex] = tmp[j];
    		currentMatrixShIndex++;
    	}
    }

    hideMatricesInImagesWithLSB(matricesSh, argv[2], LSB2_MODE, matricesShAmount);

   	printf("Before:\n");
    for(int a=0; a<2; a++)
	{
		for(int i=0; i<8; i++)
		{
			for(int j=0; j<5; j++)
			{
				printf("%u ", matricesSh[a]->matrix[i][j]);
			}

			printf("\n");
		}

		printf("\n");
	}

    MatrixStruct* matrixesShRetreived = retreiveMatricesFromImagesWithLSB(argv[2], LSB2_MODE, 8, 5, matricesShAmount);

	printf("After:\n");
	for(int a=0; a<2; a++)
	{
		for(int i=0; i<8; i++)
		{
			for(int j=0; j<5; j++)
			{
				printf("%u ", matrixesShRetreived[a]->matrix[i][j]);
			}

			printf("\n");
		}

		printf("\n");
	}*/

	//hideMatricesInImagesWithLSB(matricesS, argv[2], LSB_MODE);

	/*MatrixStruct* matricesRetreived = retreiveMatricesFromImagesWithLSB(argv[2], LSB_MODE, 8);*/

	/*for(int a=0; a<8; a++)
	{
		for(int b=0; b<8; b++)
		{
			printf("%d ", matricesRetreived[0]->matrix[a][b]);
		}

		printf("\n");
	}*/
    
	//createImageFromSMatrices(matricesRetreived, 8, matricesAmount, argv[3], &BMPFileHeader, &BMPInformationHeader);

	/*unsigned char* bitmapArray;
	bitmapArray = getBitmapArrayFromBMPFile(argv[1], &BMPFileHeader, &BMPInformationHeader);

	writeBMPFile(argv[2], &BMPFileHeader, &BMPInformationHeader, bitmapArray);

	printBMPFileHeader(&BMPFileHeader);
	printf("\n");
	printBMPInformationHeader(&BMPInformationHeader);*/

	/*for(int num=0; num<1925; num++)
	{
		for(int i=0; i<8; i++)
		{
			for(int j=0; j<8; j++)
			{
				printf("%d ", matricesS[num]->matrix[i][j]);
			}

			printf("\n");
		}

		printf("\n");
	}*/

	//MatrixStruct* matricesToHide = malloc(1);

	//hideMatricesInImagesWithLSB(matricesToHide, argv[1]);
	/*if(argc < 2)
	{
		return 0;
	}

	bitmapArray = getBitmapArrayFromBMPFile(argv[1], &BMPFileHeader, &BMPInformationHeader);

	if(bitmapArray == NULL)
	{
		return 1;
	}

	//Write bmp file test
	writeBMPFile("$HOME/test.bmp", &BMPFileHeader, &BMPInformationHeader, bitmapArray);

	writeBMPFile("$HOME/test.bmp", &BMPFileHeader, &BMPInformationHeader, bitmapArray);*/
	/*MatrixStruct testMatrixS = newZeroMatrixStruct(4,4);

	testMatrixS->matrix[0][0] = 1;
	testMatrixS->matrix[0][1] = 35;
	testMatrixS->matrix[0][2] = 52;
	testMatrixS->matrix[0][3] = 40;
	testMatrixS->matrix[1][0] = 33;
	testMatrixS->matrix[1][1] = 68;
	testMatrixS->matrix[1][2] = 69;
	testMatrixS->matrix[1][3] = 240;
	testMatrixS->matrix[2][0] = 54;
	testMatrixS->matrix[2][1] = 72;
	testMatrixS->matrix[2][2] = 212;
	testMatrixS->matrix[2][3] = 181;
	testMatrixS->matrix[3][0] = 38;
	testMatrixS->matrix[3][1] = 239;
	testMatrixS->matrix[3][2] = 176;
	testMatrixS->matrix[3][3] = 238;

	MatrixStruct* matrixes = generateMatrixListG(testMatrixS, 2);


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

    MatrixStruct* ret = generateMatrixListSh(testMatrixV, matrixes);
	for(int i=0; i<4; i++){
	    for(int j =0 ; j < 4; j++){
	        for(int k = 0; k < 3; k++){
	            printf("%d ", ret[i]->matrix[j][k]);
	        }
	        printf("\n");
	    }
	    printf("\n");
	}



	    }
	    printf("\n");
	}
	printf("%d", ret[0]->matrix[0][0]);*/
}
