//
// Created by mheimann on 22/06/19.
//

#ifndef TP_CRIPTO_CONFIGURATIONSTRUCT_H
#define TP_CRIPTO_CONFIGURATIONSTRUCT_H

typedef struct ConfigurationStruct
{
    char isRecovery;
    int n;
    int k;
    char* directory;
    char* watermark;
    char* secretImage;

}ConfigurationStruct;

typedef struct ConfigurationStruct* Configuration;

Configuration initializeConfiguration();

void printConfiguration(Configuration configuration);

#endif //TP_CRIPTO_CONFIGURATIONSTRUCT_H
