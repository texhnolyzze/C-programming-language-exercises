#ifndef SANDBOX_QSORT_H
#define SANDBOX_QSORT_H

#include <corecrt.h>

void myqsort(void *arr, size_t len, size_t elem_size, const int (*cmp)(const void *, const void *));

#endif //SANDBOX_QSORT_H
