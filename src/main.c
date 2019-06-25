#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <getopt.h>
#include <string.h>
#include "include/ConfigurationStruct.h"
#include "include/BMPLibrary.h"
#include "matrixStruct.h"
#include "random.h"
#include "include/matrixStruct.h"
#include "include/secretSharing.h"
#include "include/steganography.h"
#include "include/utils.h"
#include "include/secretDecription.h"

void printMessage();

bool distributeSecret(char* imageToHide, char* watermarkImage, int k, int n, char* carrierImagesDirectory);

bool recoverSecret(char* newImageFilePath, char* RwImage, int k, int n, char* carrierImagesDirectory);

ImageShares retreiveImageShares(char* imageToHide, MatrixStruct* matricesS, MatrixStruct* matricesW, int n, int k);

bool recoverSecret(char* newImageFilePath, char* RwImage, int k, int n, char* carrierImagesDirectory)
{

	if(validateCarrierImagesForRecovery(k, carrierImagesDirectory) == 0)
		return FALSE;

	bitmapFileHeader BMPFileHeader;
	bitmapInformationHeader BMPInformationHeader;

	if(readBMPFile(RwImage, &BMPFileHeader, &BMPInformationHeader) == 0)
	{
		return FALSE;
	}

	int steganographyModeToUse;

	if(k==4 && n==8)
		steganographyModeToUse = LSB_MODE;

	if(k==2 && n==4)
		steganographyModeToUse = LSB2_MODE;

	int ShMatricesAmount = ((BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight)/(n*n)) * n;
	int ShMatricesPerParticipant = ShMatricesAmount/n;

	MatrixStruct* RwMatrices = retreiveSquaredMatricesFromImage(RwImage, n);

	ShadowedShares shadowedShares = retreiveMatricesFromImagesWithLSB(carrierImagesDirectory, steganographyModeToUse, n, k, ShMatricesPerParticipant, ShMatricesAmount);

	int matricesSAmount = (BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight)/(n*n);

	MatrixStruct* matricesS = malloc(sizeof(MatrixStruct) * matricesSAmount);
	MatrixStruct* matricesW = malloc(sizeof(MatrixStruct) * matricesSAmount);

	int currentMatrixIndex = 0;
	int currentRwMatrixIndex = 0;

	for(int i=0; i<ShMatricesPerParticipant; i++)
	{
		MatrixStruct* tmp = malloc(sizeof(MatrixStruct) * n);

		int* shadows = malloc(sizeof(int) * n);

		for(int j=0; j<n; j++)
		{
			tmp[j] = shadowedShares.ShMatrices[(j*ShMatricesPerParticipant)+i];
			shadows[j] = shadowedShares.associatedShadows[(j*ShMatricesPerParticipant)+i] + 1;
		}

		MatrixStruct* result = recoveryAlgorithm(tmp, RwMatrices[currentRwMatrixIndex], shadows, k);
		matricesS[currentMatrixIndex] = result[0];
		matricesW[currentMatrixIndex] = result[1];
		currentMatrixIndex++;
		currentRwMatrixIndex++;
	}

	unsigned char* extraData = getExtraDataFromImage(RwImage, &BMPFileHeader, &BMPInformationHeader);

	createImageFromMatrices(matricesS, n, matricesSAmount, newImageFilePath, &BMPFileHeader, &BMPInformationHeader, extraData);
	createImageFromMatrices(matricesW, n, matricesSAmount, "Watermark.bmp", &BMPFileHeader, &BMPInformationHeader, extraData);

	return TRUE;
}

bool distributeSecret(char* imageToHide, char* watermarkImage, int k, int n, char* carrierImagesDirectory)
{
	if(validateImageToHide(imageToHide, n) == 0)
		return FALSE;

	if(validateWatermarkImage(imageToHide, watermarkImage) == 0)
		return FALSE;

	bitmapFileHeader BMPFileHeader;
	bitmapInformationHeader BMPInformationHeader;

	if(readBMPFile(imageToHide, &BMPFileHeader, &BMPInformationHeader) == 0)
		return FALSE;

	if(validateCarrierImages(BMPInformationHeader.bitmapWidth*BMPInformationHeader.bitmapHeight, n, carrierImagesDirectory) == 0)
		return FALSE;

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

	return TRUE;
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
    		matricesSh[currentMatrixShIndex + (j*SmatricesAmount)] = tmp[j];
    		j++;
    	}

    	currentMatrixShIndex++;
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
	if (argc < 12)
	{
		printf("Less arguments than required\n");
		printMessage();
		return EXIT_FAILURE;
	}

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
                else
                {
                	printf("Operation type parameter already setted\n");
					printMessage();
					return EXIT_FAILURE;
                }
                break;
            case 'd':
                if(configuration->isRecovery == -1)
                {
                    configuration->isRecovery = 0;
                }
                else
                {
                	printf("Operation type parameter already setted\n");
                    printMessage();
					return EXIT_FAILURE;
                }
                break;
            case 's':
                if(strcmp(configuration->secretImage, "") == 0)
                {
                    configuration->secretImage = optarg;
                }
                else
                {
                	printf("Secret image already setted\n");
          			printMessage();
				    return EXIT_FAILURE;
                }
                break;
            case 'm':
                if(strcmp(configuration->watermark, "") == 0)
                {
                    configuration->watermark = optarg;
                }
                else
                {
                	printf("Watermark image already setted\n");
                    printMessage();
					return EXIT_FAILURE;
                }
                break;
            case 'k':
                if(configuration->k == 0)
                {
                    configuration->k = atoi(optarg);
                }
                else
                {
                	printf("Invalid K parameter\n");
                    printMessage();
					return EXIT_FAILURE;
                }
                break;
            case 'n':
                if(configuration->n == 0)
                {
                    configuration->n = atoi(optarg);
                }
                else
                {
                	printf("Invalid N parameter\n");
                    printMessage();
					return EXIT_FAILURE;
                }
                break;
            case 'l':
                if(strcmp(configuration->directory, "") == 0)
                {
                    configuration->directory = optarg;
                }
                else
                {
                	printf("Invalid directory for image shares\n");
                    printMessage();
					return EXIT_FAILURE;
                }
                break;
            default:
                printMessage();
				return EXIT_FAILURE;
        }
    }

    if(configuration->k == 0 || configuration->n == 0 || strcmp(configuration->directory, "") == 0 ||
    strcmp(configuration->watermark, "") == 0 || strcmp(configuration->secretImage, "") == 0 ||
    configuration->isRecovery == -1)
    {
    	printf("Invalid configuration\n");
    	printConfiguration(configuration);
		printMessage();
		return EXIT_FAILURE;
    }

    bool programSuccess;

    if (configuration->isRecovery == 1)
	{
		programSuccess = recoverSecret(configuration->secretImage, configuration->watermark, configuration->k, configuration->n, configuration->directory);
	}
	else
	{
		programSuccess = distributeSecret(configuration->secretImage, configuration->watermark, configuration->k, configuration->n, configuration->directory);
	}

	return (programSuccess ? EXIT_SUCCESS : EXIT_FAILURE);
}

void printMessage()
{
	printf("In case of recovery: ./ss -r -s [secret image path] -m [watermark image path] -k [k number] -n [n number] -l [directory where images are]\n");
	printf("In case of distribution: ./ss -d -s [secret image path] -m [watermark image path] -k [k number] -n [n number] -l [directory where images are]\n");
}
