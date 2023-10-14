
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "pile_file.h"

struct graph {
    int size;
    bool oriente;
    float** matris_adj;
};
typedef struct graph graph;


graph* init_graph(int size, bool oriente);
void add_arc(graph* g, int s1, int s2);
void delete_arc(graph*g, int s1, int s2);
void add_arc_p(graph* g, int s1, int s2, float w);
void free_graph(graph* g);
file* parcour(graph* g, int s1, void (*add)(pf*, void*), void* (*ext)(pf*));
file* parcour_largeur(graph* g, int s1);
file* parcour_profondeur(graph* g, int s1);
int* dijkstra(graph* g, int s1);


#endif // GRAPH_H