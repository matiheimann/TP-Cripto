//
// Created by lococo on 07/06/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "matrixLibrary.h"
#include "libraryMod251.h"


/*          Creation of Matrix          */
int ** newMatrix(int rows, int cols)
{
    int ** matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL)
    {
        printf("No se pudo inicializar la matriz \n");
        exit(0);
    }
    for (int i = 0; i  < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("No se pudo inicializar la fila %d \n", i);
            exit(0);
        }
    }
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

int * newVector (int n)
{
    return malloc(n * sizeof(int));
}

/*          Free Matriz                 */

void freeMatrix(int ** matrix, int rows, int cols)
{
    if (matrix == NULL)
    {
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

/*          Getters, Setters && Copy    */

void copyMatrix (int ** matrixToCopy, int rows, int cols, int ** dest)
{
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            dest[i][j] = matrixToCopy[i][j];
        }
    }
}

void transpose_matrix ( int ** matrix, int rows, int cols, int ** answer)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j ++) {
            answer[j][i] = matrix[i][j];
        }
    }
}

void setIdentityMatrix(int ** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        matrix[i][i] = 1;
    }
}

/*            Equals                    */

bool areEqualMatrix(int ** matrix1, int n, int m, int ** matrix2)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix1[i][j] != matrix2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool areResultOfMatrix(int ** matrix, int n, int m, int * answer)
{
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < m - 1; j++)
        {
            sum =  suma_mod251(sum, producto_mod251(matrix[i][j], answer[j]));
        }
        sum = mod251(sum);
        int verify = mod251(matrix[i][m - 1]);
        if (sum != verify)
        {
            return false;
        }
    }
    return true;
}

/*              Prints                  */

void printMatrixWithResults(int ** matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("= %d \n", matrix[i][m - 1]);
    }
    printf("\n");
}

void printMatrix(int ** matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m ; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printVector(int * vector, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" X%d = %d ", i, vector[i]);
    }
    printf("\n");
}

/*          Operaciones Unarias         */

void productoEscalar(int ** matrix, int n, int m, int num, int ** answer)
{
    for (int i = 0; i < n ; i++)
    {
        for (int j = 0; j < m; j++)
        {
            answer[i][j] = producto_mod251(matrix[i][j], num);
        }
    }
}

void getInvertibleMatrix (int ** matrix, int n, int m, int ** answer)
{
    int ** auxMatrix = newMatrix(n, n * 2);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n*2; j++)
        {
            if (j < n)
            {
                auxMatrix[i][j] = matrix[i][j];
            }
            else if (j - n == i)
            {
                auxMatrix[i][j] = 1;
            } else {
                auxMatrix[i][j] = 0;
            }
        }
    }
    solve_matrix(auxMatrix, n, n*2);
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j < n * 2 ;j++)
        {
            answer[i][j - n] = auxMatrix[i][j];
        }
    }
    freeMatrix(auxMatrix, n, n*2);
}

/*          Operacione Binarias         */
void substract_matrix (int ** matrix1, int n1, int m1, int ** matrix2, int ** answer)
{
    for (int i=0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            answer[i][j] = resta_mod251(matrix1[i][j], matrix2[i][j]);
        }
    }
}

void add_matrix (int ** matrix1, int n1, int m1, int ** matrix2, int ** answer)
{
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            answer[i][j] = suma_mod251(matrix1[i][j],matrix2[i][j]);
        }
    }
}

void multiply_matrix(int ** matrix1, int rows1, int cols1, int ** matrix2, int rows2, int cols2, int** answer)
{
    for (int l = 0; l < rows1; l++)
    {
        for (int p = 0; p < cols2; p++ )
        {
            answer[l][p] = 0;
        }
    }

    for (int i = 0; i < rows1; i ++)
    {
        for (int j = 0; j < cols2; j++)
        {
            for (int k = 0; k < rows2; k++)
            {
                answer[i][j] = suma_mod251(answer[i][j], producto_mod251(matrix1[i][k], matrix2[k][j]));
            }
        }
    }
}


/*          Operaciones de Filas        */

void multiplyRow(int ** matrix, int n1, int m1, int rowIndex, int num)
{
    for (int j = 0; j < m1; j++)
    {
        matrix[rowIndex][j] = producto_mod251(matrix[rowIndex][j], num);
    }
}

void divideRow(int ** matrix, int n, int m,int rowIndex, int num)
{
    for (int j = 0; j < m; j++)
    {
        matrix[rowIndex][j] = dividir_mod251(matrix[rowIndex][j], num);
    }
}

void subtractRow(int ** matrix, int n1, int m1, int rowIndexChanged, int rowIndex)
{
    for (int j = 0; j < m1; j++)
    {
        matrix[rowIndexChanged][j] = mod251(resta_mod251(matrix[rowIndexChanged][j], matrix[rowIndex][j]));
    }

}

void swapInNonZeroRow(int ** matrix, int n1,int m1, int rowIndex)
{
    if (matrix[rowIndex][rowIndex] != 0)
    {
        return;
    }
    else
    {
        for (int i = rowIndex; i < n1; i++)
        {
            if (matrix[i][rowIndex] != 0)
            {
                swapRows(matrix, n1, m1, i, rowIndex);
                return;
            }
        }
    }
}

void swapRows(int ** matrix, int n1, int m1, int rowIndex1, int rowIndex2)
{
    for (int j = 0; j < m1; j++)
    {
        int aux = matrix[rowIndex1][j];
        matrix[rowIndex1][j] = matrix[rowIndex2][j];
        matrix[rowIndex2][j] = aux;
    }
}
/*          Operaciones de Columnas     */

int ** addColToMatrix(int ** matrix, int row, int col, int * newCol)
{
    if (newCol == NULL)
    {
        return NULL;
    }
    if (matrix == NULL)
    {
        return NULL;
    }
    int ** auxMatrix = newMatrix(row, col + 1);
    copyMatrix(matrix, row, col, auxMatrix);
    for (int j = 0; j < row; j++)
    {
        auxMatrix[j][col] = newCol[j];
    }
    return auxMatrix;
}

/*          Matrix Solver               */

void matrixSolver (int ** matrix, int n, int m, int * answer)
{
    int ** auxMatrix = newMatrix(n, m);
    copyMatrix(matrix, n, m, auxMatrix);
    solve_matrix(matrix, n, m);
    getResult(matrix, n, m, answer);
    freeMatrix(auxMatrix, n, m);
    return;
}

void solve_matrix (int ** matrix, int n, int m)
{
    int j;
    for (int i = 0; i < n; i++)
    {
        if (i >= m)
        {
            break;
        }

        swapInNonZeroRow(matrix, n, m, i);

        if (matrix[i][i] == 0)
        {
            return;
        }

        if (matrix[i][i] != 1)
        {
            int factor=matrix[i][i];
            divideRow(matrix, n, m, i, factor);
        }

        for (int j = 0; j < n ; j++)
        {
            if (matrix[j][i] != 0 && j != i)
            {
                int factor = matrix[j][i];
                divideRow(matrix, n, m, j, factor);
                subtractRow(matrix, n, m, j, i);
            }
        }
    }
    for (int x = 0; x < n; x++)
    {
        if (matrix[x][x] != 1)
        {
            int factor = matrix[x][x];
            divideRow(matrix, n, m, x, matrix[x][x]);
        }
    }
}

void getResult(int ** matrix, int n1, int m1, int *answer)
{
    for (int i = 0; i < n1; i++)
    {
        answer[i] = matrix[i][m1 - 1];
    }
    return;
}






