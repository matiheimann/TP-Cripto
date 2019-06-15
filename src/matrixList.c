//
// Created by lococo on 14/06/19.
//

#include "include/matrixList.h"
#include <stdlib.h>

MatrixList newMatrixList()
{
    MatrixList list = malloc(sizeof(list));
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}

void AddMatrix(MatrixList list, MatrixStruct matrix)
{
    Node toAdd = newNode(matrix);
    if (list->first == NULL)
    {
        list->first = toAdd;
        list->last = toAdd;
        list->size = 1;
        return;
    }

    list->last->next = toAdd;
    list->last = toAdd;
    list->size += 1;
    return;
}

Node newNode(MatrixStruct matrix)
{
    Node newNode = malloc(sizeof(newNode));
    newNode->next = NULL;
    newNode->matrixStruct = copyMatrixStruct(matrix);
    return newNode;
}

void freeMatrixList(MatrixList list)
{
    freeNodeList(list->first);
    free(list);
    return;
}

void freeNodeList(Node node)
{
    if (node == NULL)
    {
        return;
    }
    freeNodeList(node->next);
    freeMatrixStr(node->matrixStruct);
    free(node);
    return;
}

MatrixStruct getMatrixAtPosition(MatrixList list,  int position)
{
    int count = 0;
    if (position >= list->size)
    {
        return NULL;
    }
    Node aux = list->first;
    while (aux != NULL)
    {
        if (position == count)
        {
            return aux->matrixStruct;
        }
        count++;
        aux = aux->next;
    }
    return NULL;
}
