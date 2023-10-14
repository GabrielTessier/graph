
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/pile_file.h"
#include "include/graph.h"
#include "include/tool.h"
#include "include/tas.h"

int main() {

    // FILE
    printf("FILE :\n");

    file* f = init_file(itv(1));
    add_file(f, itv(2));
    add_file(f, itv(3));
    add_file(f, itv(4));

    print_file(f, print_int);

    for (int i=0; i<5; i++) {
        int* v = (int*) extract_file(f);
        print_int(v);
        printf("\n");
        if (v!=NULL) free(v);
    }

    add_file(f, itv(3));

    free_file(f, free);

    file* f2 = init_file(itv(1));
    add_file(f2, itv(2));
    add_file(f2, itv(3));
    add_file(f2, itv(4));

    free_file(f2, free);


    // PILE
    printf("\nPILE :\n");

    pile* p = init_pile(itv(1));
    add_pile(p, itv(2));
    add_pile(p, itv(3));
    add_pile(p, itv(4));

    for (int i=0; i<5; i++) {
        int* v = (int*) extract_pile(p);
        print_int(v);
        printf("\n");
        if (v!=NULL) free(v);
    }

    free_pile(p, free);

    pile* p2 = init_pile(itv(1));
    add_pile(p2, itv(2));
    add_pile(p2, itv(3));
    add_pile(p2, itv(4));

    free_pile(p2, free);


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

    print_file(pl, print_int);
    print_file(pp, print_int);

    free_file(pl, free);
    free_file(pp, free);
    free_graph(g);


    // TAS
    printf("\nTAS :\n");

    heap* h = init_heap(5, itv(1), inf);
    add_heap(h, 3, itv(2));
    add_heap(h, 7, itv(3));
    add_heap(h, 1, itv(4));

    while (h->size > 0) {
        int** b = (int**) malloc(sizeof(int*));
        int val = extract_heap(h, (void**) b);
        printf("%d, %d\n", val, **b);
        free(*b);
        free(b);
    }
    printf("\n");

    free_heap(h, free);


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
        printf("%d -> %d\n", pred[i], i);
    }

    free(pred);
    free_graph(g2);

    return 0;
}