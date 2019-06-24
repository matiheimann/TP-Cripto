//
// Created by mheimann on 23/06/19.
//

#include "include/utils.h"
#include <string.h>
#include <stdio.h>
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