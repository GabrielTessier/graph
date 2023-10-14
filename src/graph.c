
#include <stdbool.h>
#include <stdlib.h>

#include "../include/pile_file.h"
#include "../include/tool.h"
#include "../include/tas.h"
#include "../include/graph.h"

graph* init_graph(int size, bool oriente) {
    graph* g = (graph*) malloc(sizeof(graph));
    g->size = size;
    g->oriente = oriente;
    g->matris_adj = (float**) malloc(sizeof(float*)*size);
    for (int i=0; i<size; i++) {
        g->matris_adj[i] = (float*) malloc(sizeof(float)*size);
        for (int j=0; j<size; j++) {
            g->matris_adj[i][j] = false;
        }
    }
    return g;
}

void add_arc(graph* g, int s1, int s2) {
    if (s1<g->size && s2<g->size) {
        g->matris_adj[s1][s2] = 1;
        if (g->oriente == false) g->matris_adj[s2][s1] = 1;
    }
}
void add_arc_p(graph* g, int s1, int s2, float w) {
    if (s1<g->size && s2<g->size) {
        g->matris_adj[s1][s2] = w;
        if (g->oriente == false) g->matris_adj[s2][s1] = w;
    }
}
void delete_arc(graph*g, int s1, int s2) {
    if (s1<g->size && s2<g->size) {
        g->matris_adj[s1][s2] = 0;
        if (g->oriente == false) g->matris_adj[s2][s1] = 0;
    }
}

void free_graph(graph* g) {
    for (int i=0; i<g->size; i++) {
        free(g->matris_adj[i]);
    }
    free(g->matris_adj);
    free(g);
}

file* parcour(graph* g, int s1, void (*add)(pf*, void*), void* (*ext)(pf*)) {
    bool* vue = (bool*) malloc(sizeof(bool)*g->size);
    for (int i=0; i<g->size; i++) {
        vue[i] = false;
    }
    pf* sac = (pf*) malloc(sizeof(pf));
    list* il = init_list(itv(s1));
    sac->d = il;
    sac->f = il;

    file* par = init_file(NULL);
    while (sac->d != NULL) {
        int* ps = (int*) (*ext)(sac);  // ps != NULL car sac non vide
        int s = *ps;
        if (vue[s] == false) {
            vue[s] = true;
            add_file(par, itv(s));
            for (int i=0; i<g->size; i++) {
                if (g->matris_adj[s][i] != 0) (*add)(sac, itv(i));
            }
        }
        free(ps);
    }
    free_pf(sac, free);
    free(vue);
    extract_file(par);
    return par;
}

file* parcour_largeur(graph* g, int s1) {
    return parcour(g, s1, add_file, extract_file);
}
file* parcour_profondeur(graph* g, int s1) {
    return parcour(g, s1, add_pile, extract_pile);
}

int* dijkstra(graph* g, int s1) {
    int* predecesseur = (int*) malloc(sizeof(int)*g->size);
    for (int i=0; i<g->size; i++) {
        predecesseur[i] = -2;
    }
    int* init = (int*) malloc(sizeof(int)*2);
    init[0] = -1;
    init[1] = s1;
    heap* tas = init_heap(0, init, inf);

    while (tas->size != 0) {
        int* arc;
        int prio = extract_heap(tas, (void**)&arc);
        if (predecesseur[arc[1]] == -2) {
            predecesseur[arc[1]] = arc[0];
            for (int i=0; i<g->size; i++) {
                int w = g->matris_adj[arc[1]][i];
                if (w != 0) {
                    int* n_arc = (int*) malloc(sizeof(int)*2);
                    n_arc[0] = arc[1];
                    n_arc[1] = i;
                    add_heap(tas, prio+w, n_arc);
                }
            }
        }
        free(arc);
    }
    free_heap(tas, free);
    return predecesseur;
}