#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <intrin.h>
#include "matrix.h"
#include "C:\Users\User\CLionProjects\course1\libs\base\base.h"


matrix getMemMatrix(int nRows, int nCols){
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols){
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);

    return ms;
}


void freeMemMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i++)
        free(m->values[i]);
}

void freeMemMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++){
        freeMemMatrix(&ms[i]);
    }
}

void inputMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i++){
        printf("Input %d elements of the %d rows matrix (separated by a space):", m->nCols, i + 1);
        for (int j = 0; j < m->nCols; j++)
            scanf(" %d", &m->values[i][j]);
    }
}

void inputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++){
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m){
    printf("Print matrix:\n");
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++){
        printf("%d)", i + 1);
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix m, int i1, int i2){
    assert(i1 < m.nRows || i2 < m.nRows);

    int *t;
    t = m.values[i2];
    m.values[i2] = m.values[i1];
    m.values[i1] = t;
}

void swapColumns(matrix m, int j1, int j2){
    for (int i = 0; i < m.nRows; i++){
        swap(&m.values[i][j1], &m.values[i][j2]);
    }
}

void insertionSort(int *a, const size_t size){
    for (size_t i = 1; i < size; i++){
        int t = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > t){
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

int getSum(int *a, int n){
    int r = 0;
    for (int i = 0; i < n; i++)
        r += a[i];
    return r;
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)){
    int r[m.nRows] = {};
    for (int i = 0; i < m.nRows; i++){
        r[i] = getSum(m.values[i], m.nCols);
    }

    for (int i = 1; i < m.nRows; i++){
        int t = r[i];
        int *t1 = m.values[i];
        int j = i;
        while (j > 0 && r[j - 1] > t){
            r[j] = r[j - 1];
            m.values[j] = m.values[j - 1];
            j--;
        }
        r[j] = t;
        m.values[j] = t1;
    }
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)){
    int r[m.nCols] = {};
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++)
            r[j] += m.values[i][j];
    }

    for (int i = 0; i < m.nCols - 1; i++){
        int minPos = i;
        for (int j = i + 1; j < m.nCols; j++)
            if (r[j] < r[minPos])
                minPos = j;
        swap(&r[i], &r[minPos]);
        swapColumns(m, i, minPos);
    }

}

bool isSquareMatrix(matrix *m){
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    int r = 0;
    for (int i = 0; i < m1->nRows; i++){
        r += memcmp(m1->values[i], m2->values[i], sizeof(int) * m1->nCols);
    }
    return r == 0;
}

bool isEMatrix(matrix *m){
    if (isSquareMatrix(m)){
        int flag_for_1 = 0;
        int flag_for_0 = 0;
        for (int i = 0; i < m->nRows; i++){
            for (int j = 0; j < m->nRows; j++){
                if (i == j && m->values[i][j] == 1)
                    flag_for_1++;
                if (i != j && m->values[i][j] == 0)
                    flag_for_0++;
            }
        }
        int quantity_diagonal_elements = m->nRows;
        return flag_for_1 == m->nRows && flag_for_0 == m->nRows * m->nCols - quantity_diagonal_elements;
    }
    return 0;
}

bool isSymmetricMatrix(matrix *m){
    if (isSquareMatrix(m)){
        int flag = 0;
        for (int i = 0; i < m->nRows; i++){
            for (int j = 0; j < m->nRows; j++){
                if (i != j && m->values[i][j] == m->values[j][i])
                    flag++;
            }
        }
        int quantity_diagonal_elements = m->nRows;

        return flag == m->nRows * m->nCols - quantity_diagonal_elements;
    }

    return 0;
}

void transposeSquareMatrix(matrix *m){
    if (isSquareMatrix(m)){
        for (int i = 0; i < m->nRows; i++){
            for (int j = i + 1; j < m->nCols; j++){
                swap(&m->values[i][j], &m->values[j][i]);
            }
        }
    }

    else
        fprintf(stderr, "Error: Input matrix is not square.\n");
}

matrix transposeMatrix(matrix *m){
    matrix newMatrix = getMemMatrix(m->nCols, m->nRows);
    for (int i = 0; i < m->nRows; i++)
        for (int j = 0; j < m->nCols; j++)
            newMatrix.values[j][i] = m->values[i][j];
    return newMatrix;
}

position getMinValuePos(matrix m){
    position t = {0, 0};

    for (int i = 0; i < m.nRows; i++){
        if (m.values[i][getMinIndex(m.values[i], m.nCols)] < m.values[t.rowIndex][t.colIndex]){
            t.rowIndex = i;
            t.colIndex = getMinIndex(m.values[i], m.nCols);
        }
    }
    return t;
}

position getMaxValuePos(matrix m){
    position t = {0, 0};

    for (int i = 0; i < m.nRows; i++){
        if (m.values[i][getMaxIndex(m.values[i], m.nCols)] < m.values[t.rowIndex][t.colIndex]){
            t.rowIndex = i;
            t.colIndex = getMaxIndex(m.values[i], m.nCols);
        }
    }
    return t;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols){
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++){
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];
    }
    return m;
}


//тесты
int countZeroRows(matrix m, int nRows, int nCols){
    int counter = 0;
    int zerosInCurrentCols = 0;
    for (int i = 0; i < nRows; i++){
        for (int j = 0; j < nCols; j++){
            if (m.values[i][j] == 0)
                zerosInCurrentCols++;
            if (zerosInCurrentCols == nCols)
                counter++;
        }
    }
    return counter;
}

void test_countZeroRows(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    0, 0, 0,
                    0, 0, 1,
                    0, 0, 0,
                    0, 1, 1,
            },
            5, 3
    );
    assert(countZeroRows(m, 5, 3) == 2);
    freeMemMatrix(&m);
}
