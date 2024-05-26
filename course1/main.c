#include <stdio.h>
#include "C:\Users\User\CLionProjects\course1\libs\data_structures\matrix\matrix.h"

int getMin(const int *a, int n){
    int minElement = a[0];
    for (int i = 0; i < n; i++)
        if (a[i] < minElement)
            minElement = a[i];

    return minElement;
}

void sortColsByMinElement(matrix *m){
    *m = transposeMatrix(m);
    for (int k = 0; k < m->nRows; k++){
        int iMin = k;
        int currentMin = getMin(m->values[iMin], m->nCols);
        for (int i = k + 1; i < m->nRows; i++){
            if (getMin(m->values[i], m->nCols) < currentMin){
                currentMin = getMin(m->values[i], m->nCols);
                iMin = i;
            }
        }

        if (iMin != k)
            swapRows(*m, iMin, k);
    }

    *m = transposeMatrix(m);
}

int main(){

    matrix t = getMemMatrix(3, 6);
    inputMatrix(&t);
    outputMatrix(t);

    puts("\n");
    sortColsByMinElement(&t);
    outputMatrix(t);

    return 0;
}
