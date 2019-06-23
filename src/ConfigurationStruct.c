//
// Created by mheimann on 23/06/19.
//

#include "include/ConfigurationStruct.h"
#include <stdlib.h>

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
