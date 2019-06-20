//
// Created by lococo on 14/06/19.
//

#ifndef MATRICES_RESOLVER_MATRIXLIST_H
#define MATRICES_RESOLVER_MATRIXLIST_H


#include "matrixStruct.h"

struct matrixNode {
    MatrixStruct matrixStruct;
    struct matrixNode * next;
};

typedef struct matrixNode * Node;

struct list{
    Node first;
    int size;
    Node last;
};

typedef struct list * MatrixList;

MatrixList newMatrixList();
Node newNode(MatrixStruct matrix);

void AddMatrix(MatrixList list, MatrixStruct node);

void freeNodeList(Node node);
void freeMatrixList(MatrixList list);

MatrixStruct getMatrixAtPosition(MatrixList list, int position);


#endif //MATRICES_RESOLVER_MATRIXLIST_H
