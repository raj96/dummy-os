#ifndef __KMEM_H
#define __KMEM_H

#include "nostd/stdint.h"

typedef struct __freekmem_list {
    struct __freekmem_list *next;
} __attribute__((packed)) freekmem_list_t;

extern freekmem_list_t *freekmem_list;

void kmem_init(uint64_t start_address, uint64_t length);
void* kmalloc(uint64_t size);
void kfree(void *amem);

#endif