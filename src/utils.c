//
// Created by mheimann on 23/06/19.
//

#include "include/utils.h"
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
int isNaturalNumber(char* num)
{
    int i = 0;
    while(num[i] != 0)
    {
        if(num[i] < '0' || num[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
