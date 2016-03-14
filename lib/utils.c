#include "utils.h"

void* checked_malloc(int size) {
    void *p = malloc(size);
    assert(p);
    return p;
}
