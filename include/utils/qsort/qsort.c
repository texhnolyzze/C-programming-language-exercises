#include <string.h>
#include "qsort.h"

static inline size_t select_partition_elem(
        const void *arr,
        const size_t elem_size,
        size_t lo,
        size_t hi,
        const int (*cmp)(const void *, const void *)
) {
    const size_t mid = lo + (hi - lo) / 2;
    const void *lo_elem = arr + lo * elem_size;
    const void *mid_elem = arr + mid * elem_size;
    const void *hi_elem = arr + hi * elem_size;
    if (cmp(lo_elem, mid_elem) < 0) {
        if (cmp(lo_elem, hi_elem) < 0) {
            if (cmp(mid_elem, hi_elem) < 0) {
                return mid;
            } else {
                return hi;
            }
        } else {
            return lo;
        }
    } else {
        if (cmp(mid_elem, hi_elem) < 0) {
            return mid;
        } else {
            if (cmp(lo_elem, hi_elem) < 0) {
                return hi;
            } else {
                return lo;
            }
        }
    }
}

static size_t partition(
        void *arr,
        const size_t left,
        const size_t right,
        const size_t elem_size,
        char partition_elem[],
        const int (*cmp)(const void *, const void *)
) {
    size_t partition_elem_idx = select_partition_elem(arr, elem_size, left, right, cmp);
    memcpy(partition_elem, arr + partition_elem_idx * elem_size, elem_size);
    size_t lo = left;
    size_t hi = right;
    memcpy(arr + partition_elem_idx * elem_size, arr + lo * elem_size, elem_size);
    for (;;) {
        for (;;) {
            const void *hi_elem = arr + hi * elem_size;
            if (cmp(hi_elem, partition_elem) < 0) {
                memcpy(arr + lo * elem_size, arr + hi * elem_size, elem_size);
                break;
            } else {
                hi--;
                if (hi == lo) {
                    goto exit_loop;
                }
            }
        }
        for (;;) {
            const void *lo_elem = arr + lo * elem_size;
            if (cmp(lo_elem, partition_elem) > 0) {
                memcpy(arr + hi * elem_size, arr + lo * elem_size, elem_size);
                break;
            } else {
                lo++;
                if (hi == lo) {
                    goto exit_loop;
                }
            }
        }
    }
    exit_loop:
    memcpy(arr + lo * elem_size, partition_elem, elem_size);
    return lo;
}

static void insertion_sort(
        void *arr,
        const size_t left,
        const size_t right,
        const size_t elem_size,
        char temp_bytes[],
        const int (*cmp)(const void *, const void *)
) {
    for (size_t i = left + 1; i <= right; ++i) {
        memcpy(temp_bytes, arr + i * elem_size, elem_size);
        size_t j = i - 1;
        for (;;) {
            const void *elem = arr + j * elem_size;
            if (cmp(elem, temp_bytes) > 0) {
                memcpy(arr + (j + 1) * elem_size, elem, elem_size);
            } else {
                memcpy(arr + (j + 1) * elem_size, temp_bytes, elem_size);
                break;
            }
            if (j == left) {
                memcpy(arr + j * elem_size, temp_bytes, elem_size);
                break;
            }
            j--;
        }
    }
}

static void qsort(
        void *arr,
        const size_t left,
        const size_t right,
        const size_t elem_size,
        char temp_bytes[],
        const int (*cmp)(const void *, const void *)
) {
    if (left >= right) {
        return;
    }
    if (right - left + 1 <= 25) {
        insertion_sort(arr, left, right, elem_size, temp_bytes, cmp);
        return;
    }
    size_t i = partition(arr, left, right, elem_size, temp_bytes, cmp);
    if (i != 0) {
        qsort(arr, left, i - 1, elem_size, temp_bytes, cmp);
    }
    qsort(arr, i + 1, right, elem_size, temp_bytes, cmp);
}

void myqsort(void *arr, const size_t len, const size_t elem_size, const int (*cmp)(const void *, const void *)) {
    char temp_bytes[elem_size];
    qsort(arr, 0, len - 1, elem_size, temp_bytes, cmp);
}
