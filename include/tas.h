
#ifndef TAS_H
#define TAS_H

#include <stdbool.h>

struct node {
    int val;
    void* data;
};
typedef struct node node;

struct heap {
    node** tab;
    int size;
    int capacity;
    bool (*cmp)(int, int);
};
typedef struct heap heap;


heap* init_heap(int val, void* data, bool (*cmp)(int, int));
void free_heap(heap* h, void (*free_data)(void*));
void add_heap(heap* h, int val, void* data);
int extract_heap(heap* h, void** pdata);


#endif // TAS_H