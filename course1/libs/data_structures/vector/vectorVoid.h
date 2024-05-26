#ifndef INC_VECTORVOID_H
#define INC_VECTORVOID_H

#include <limits.h>
#include <stdbool.h>

typedef struct vectorVoid {
    void *data;
    size_t size;
    size_t capacity;
    size_t baseTypeSize;

} vectorVoid;

//создает вектор размером n и типом sizeof(type)
vectorVoid createVectorV(size_t n, size_t baseTypeSize);

//изменяет количество памяти, выделенное под хранение элементов вектора
void reserveV(vectorVoid *v, size_t newCapacity);

//освобождает память, выделенную под неиспользуемые элементы
void shrinkToFitV(vectorVoid *v);

//удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vectorVoid *v);

//освобождает память, выделенную вектору
void deleteVectorV(vectorVoid *v);

//является ли вектор пустым
bool isEmptyV(vectorVoid *v);

//является ли вектор полным
bool isFullV(vectorVoid *v);

//записывает по адресу destination index-ый элемент вектора v
void getVectorValueV(vectorVoid *v, size_t index, void *destination);

//записывает на index-ый элемент вектора v значение, расположенное по адресу source
void setVectorValueV(vectorVoid *v, size_t index, void *source);

#endif