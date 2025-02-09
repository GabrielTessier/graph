
#include <stdlib.h>
#include <stdio.h>

#include "tas.h"


heap* init_heap(int val, void* data, bool (*cmp)(int, int)) {
  heap* h = (heap*) malloc(sizeof(heap));
  h->tab = (node**) malloc(sizeof(node*));
  h->capacity = 1;
  h->size = 1;
  h->cmp = cmp;
  h->tab[0] = (node*) malloc(sizeof(node));
  h->tab[0]->val = val;
  h->tab[0]->data = data;
  return h;
}

void free_heap(heap* h, void (*free_data)(void*)) {
  for (int i=0; i<h->size; i++) {
    if (free_data != NULL) (*free_data)(h->tab[i]->data);
    free(h->tab[i]);
  }
  free(h->tab);
  free(h);
}

void add_heap_corection(heap* h, int index)
{
    int parent = (index - 1) / 2;
    if ((*h->cmp)(h->tab[index]->val, h->tab[parent]->val)) {
        node* tmp = h->tab[parent];
        h->tab[parent] = h->tab[index];
        h->tab[index] = tmp;
        add_heap_corection(h, parent);
    }
}

void up_heap_capacity(heap* h) {
    h->capacity = h->capacity * 2;
    node** tmp = h->tab;
    h->tab = (node**) malloc(sizeof(node*)*h->capacity);
    for (int i=0; i<h->size; i++) {
        h->tab[i] = tmp[i];
    }
    free(tmp);
}

void add_heap(heap* h, int val, void* data) {
    if (h->size == h->capacity) {
        up_heap_capacity(h);
    }
    h->tab[h->size] = (node*) malloc(sizeof(node));
    h->tab[h->size]->val = val;
    h->tab[h->size]->data = data;
    add_heap_corection(h, h->size);
    h->size++;
}

void extract_heap_correction(heap* h, int i) {
    int l = i*2+1;
    int r = i*2+2;
    if (l >= h->size || l < 0) l = -1;
    if (r >= h->size || r < 0) r = -1;
    int m = i;
    if (l != -1 && (*h->cmp)(h->tab[l]->val, h->tab[m]->val)) m = l;
    if (r != -1 && (*h->cmp)(h->tab[r]->val, h->tab[m]->val)) m = r;
    if (m != i) {
        node* tmp = h->tab[m];
        h->tab[m] = h->tab[i];
        h->tab[i] = tmp;
        extract_heap_correction(h, m);
    }
}

int extract_heap(heap* h, void** pdata) {
    if (h->size == 0) {
        // vide
        return -1;
    }
    node* res = h->tab[0];
    h->tab[0] = h->tab[h->size - 1];
    h->size--;
    extract_heap_correction(h, 0);
    (*pdata) = res->data;
    int rv = res->val;
    free(res);
    return rv;
}


