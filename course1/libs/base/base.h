#ifndef INC_BASE_H
#define INC_BASE_H

#include <stddef.h>

//обменивает значения по адресу а и b
void swap(int *a, int *b);

//возвращает индекс первого вхождения элемента с минимальным значением
int getMinIndex(const int *arr, size_t n);

//возвращает индекс первого вхождения элемента с максимальным значением
int getMaxIndex(const int *arr, size_t n);

#endif
