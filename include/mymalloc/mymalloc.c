#include <stddef.h>
#include <heapapi.h>
#include <stdbool.h>
#include "mymalloc.h"

struct header {
    struct header *next;
    size_t units;
};

typedef struct header Header;

static Header *head;

const size_t MIN_UNITS = 32;

size_t allocated = 0;

void *mymalloc(size_t bytes) {
    size_t units = (bytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    Header *alloc;
    if (head == NULL) {
        alloc = HeapAlloc(GetProcessHeap(), 0, max(MIN_UNITS, units) * sizeof(Header));
        if (alloc == NULL) {
            return NULL;
        }
        allocated += max(MIN_UNITS, units) * sizeof(Header);
        alloc->units = max(MIN_UNITS, units);
        alloc->next = NULL;
        head = alloc;
    }
    Header *curr = head;
    Header *prev = NULL;
    Header *temp;
    for (;;) {
        if (curr->units >= units) {
            if (curr->units == units) {
                if (prev == NULL) {
                    head = curr->next;
                } else {
                    prev->next = curr->next;
                }
            } else {
                temp = curr + units;
                if (prev == NULL) {
                    head = temp;
                } else {
                    prev->next = temp;
                }
                temp->next = curr->next;
                temp->units = curr->units - units;
                curr->units = units;
            }
            return curr + 1;
        }
        if (curr->next == NULL) {
            alloc = HeapAlloc(GetProcessHeap(), 0, max(MIN_UNITS, units) * sizeof(Header));
            if (alloc == NULL) {
                return NULL;
            }
            allocated += max(MIN_UNITS, units) * sizeof(Header);
            alloc->units = max(MIN_UNITS, units);
            if (alloc < head) {
                temp = head;
                head = alloc;
                alloc->next = temp;
                prev = NULL;
                curr = alloc;
            } else {
                curr = head;
                while (true) {
                    if (alloc > curr && (curr->next == NULL || alloc < curr->next)) {
                        temp = curr->next;
                        curr->next = alloc;
                        alloc->next = temp;
                        break;
                    }
                    curr = curr->next;
                }
                prev = curr;
                curr = alloc;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void myfree(void *memory) {
    Header *h = memory;
    h--;
    if (head == NULL) {
        head = h;
        return;
    }
    Header *curr = head;
    Header *prev = NULL;
    do {
        if (h < curr) {
            if (prev == NULL) {
                head = h;
                if (h + h->units == curr) {
                    h->units += curr->units;
                    h->next = curr->next;
                } else {
                    h->next = curr;
                }
                return;
            } else {
                prev->next = h;
                if (h + h->units == curr) {
                    h->units += curr->units;
                    h->next = curr->next;
                } else {
                    h->next = curr;
                }
                return;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
    } while (curr != NULL);
    if (prev + prev->units == h) {
        prev->units += h->units;
    } else {
        prev->next = h;
    }
}

size_t total_free_memory() {
    size_t res = 0;
    const Header *curr = head;
    while (curr != NULL) {
        res += curr->units * sizeof(Header);
        curr = curr->next;
    }
    return res;
}

size_t total_allocated() {
    return allocated;
}
