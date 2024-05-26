
#include "base.h"

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int getMinIndex(const int *arr, size_t n) {
    if (n == 0) {
        return -1;
    }

    int minElement = arr[0];
    int minIndex = 0;

    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < minElement) {
            minElement = arr[i];
            minIndex = i;
        }
    }

    return minIndex;
}

int getMaxIndex(const int *arr, size_t n) {
    if (n == 0) {
        return -1;
    }

    int maxElement = arr[0];
    int maxIndex = 0;

    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}