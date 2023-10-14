
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/tool.h"

void print_int(void* a) {
    if (a != NULL) printf("%d", *((int*) a));
    else printf("NULL");
}

void* itv(int i) { // int to void*
    int* a = malloc(sizeof(int));
    *a = i;
    return (void*) a;
}

bool inf(int a, int b) {
    return a<b;
}