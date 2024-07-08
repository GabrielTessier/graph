
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/pile_file.h"
#include "include/graph.h"
#include "include/tool.h"
#include "include/tas.h"

void print_int(void* i) {
    int a = (int) (long) (*((int**)i));
    printf("%d, ", a);
}

int main() {

    // FILE
    printf("FILE :\n");

    file* f = init_file();
    add_file(f, (int*) 1);
    add_file(f, (int*) 2);
    add_file(f, (int*) 3);
    add_file(f, (int*) 4);

    iter_file(f, print_int);
    printf("\n");

    while (file_vide(f) == false) {
        int* v = (int*) extract_file(f);
        print_int(&v);
        printf("\n");
    }

    add_file(f, (int*) 3);

    free_file(f, NULL);

    file* f2 = init_file();
    add_file(f2, (int*) 1);
    add_file(f2, (int*) 2);
    add_file(f2, (int*) 3);
    add_file(f2, (int*) 4);

    free_file(f2, NULL);


    // PILE
    printf("\nPILE :\n");

    pile* p = init_pile();
    add_pile(p, (int*) 1);
    add_pile(p, (int*) 2);
    add_pile(p, (int*) 3);
    add_pile(p, (int*) 4);

    while (pile_vide(p) == false) {
        int* v = (int*) extract_pile(p);
        print_int(&v);
        printf("\n");
    }

    free_pile(p, NULL);

    pile* p2 = init_pile();
    add_pile(p2, (int*) 1);
    add_pile(p2, (int*) 2);
    add_pile(p2, (int*) 3);
    add_pile(p2, (int*) 4);

    free_pile(p2, NULL);


    // GRAPH
    printf("\nGRAPH :\n");

    graph* g = init_graph(6, true);
    add_arc(g, 0, 1);
    add_arc(g, 0, 2);
    add_arc(g, 1, 3);
    add_arc(g, 1, 4);
    add_arc(g, 3, 5);

    file* pl = parcour_largeur(g, 0);
    file* pp = parcour_profondeur(g, 0);

    iter_file(pl, print_int);
    printf("\n");
    iter_file(pp, print_int);
    printf("\n");

    free_file(pl, NULL);
    free_file(pp, NULL);
    free_graph(g);


    // TAS
    printf("\nTAS :\n");

    heap* h = init_heap(5, (int*) 1, inf);
    add_heap(h, 3, (int*) 2);
    add_heap(h, 7, (int*) 3);
    add_heap(h, 1, (int*) 4);

    while (h->size > 0) {
        int* b;
        int val = extract_heap(h, (void**) &b);
        printf("%d, %d\n", val, (int)(long)b);
    }
    printf("\n");

    free_heap(h, NULL);


    // DIJKSTRA
    printf("\nDIJKSTRA :\n");

    graph* g2 = init_graph(6, false);
    add_arc_p(g2, 0, 1, 7);
    add_arc_p(g2, 0, 2, 9);
    add_arc_p(g2, 0, 5, 14);
    add_arc_p(g2, 1, 2, 10);
    add_arc_p(g2, 1, 3, 15);
    add_arc_p(g2, 2, 3, 11);
    add_arc_p(g2, 2, 5, 2);
    add_arc_p(g2, 3, 4, 6);
    add_arc_p(g2, 4, 5, 9);

    int* pred = dijkstra(g2, 0);
    for (int i=0; i<g2->size; i++) {
        //printf("i : %d\n", i);
        printf("%d -> %d\n", pred[i], i);
    }

    free(pred);
    free_graph(g2);

    return 0;
}