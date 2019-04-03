#include "matrixoperations.h"
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

matrix* newMatrix(int rows, int columns, char argCount, ...)
{

    matrix* m = calloc(1, sizeof(matrix));
    m->matrix = calloc(rows, sizeof(int*));
    m->rows = rows;
    m->columns = columns;
    for(int i = 0; i < rows; i++)
    {
        m->matrix[i] = calloc(columns, sizeof(int));
    }
    if(argCount == 1)
    {
        va_list args;
        int** values = va_arg(args, int**);
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                m->matrix[i][j] = values[i][j];
            }
        }
    }
    return m;
}

matrix* sumMatrix(matrix* m1, matrix* m2)
{
    matrix* m3 = calloc(1, sizeof(matrix));
    m3->rows = (m1->rows > m2->rows) ? m1->rows : m2->rows;
    m3->columns = (m1->columns > m2->columns) ? m1->columns : m2->columns;
    m3->matrix = calloc(m3->rows, sizeof(int*));
    for(int i = 0; i < m3->rows; i++)
    {
        m3->matrix[i] = calloc(m3->columns, sizeof(int));
    }

    int i = 0;
    for(; i < fmin(m1->rows, m2->rows); i++)
    {
        int j = 0;
        for(; j < fmin(m1->columns, m2->columns); j++)
        {
            m3->matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
        }
        for(; j < fmax(m1->columns, m2->columns); j++)
        {
            m3->matrix[i][j] = (m1->columns > m2->columns) ? m1->matrix[i][j] : m2->matrix[i][j];
        }
    }

    for(; i < fmax(m1->rows, m2->rows); i++)
    {
        int j = 0;
        for(; j < fmin(m1->columns, m2->columns); j++)
        {
            m3->matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
        }
        for(; j < fmax(m1->columns, m2->columns); j++)
        {
            m3->matrix[i][j] = (m1->columns > m2->columns) ? m1->matrix[i][j] : m2->matrix[i][j];
        }
    }

    return m3;
}