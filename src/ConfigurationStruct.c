//
// Created by mheimann on 23/06/19.
//

#include "include/ConfigurationStruct.h"
#include <stdlib.h>
#include <stdio.h>

Configuration initializeConfiguration()
{
    Configuration conf = malloc(sizeof(ConfigurationStruct));
    conf->isRecovery = -1;
    conf->directory = "";
    conf->k = 0;
    conf->n = 0;
    conf->secretImage = "";
    conf->watermark = "";
    return conf;
}

void printConfiguration(Configuration configuration)
{
	printf("Is recovery: %d\n", configuration->isRecovery);
	printf("Directory: %s\n", configuration->directory);
	printf("K: %d\n", configuration->k);
	printf("N: %d\n", configuration->n);
	printf("Secret image: %s\n", configuration->secretImage);
	printf("Watermark: %s\n", configuration->watermark);
}