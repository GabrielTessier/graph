
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

/* Initialise un graphe de taille `size`

   Le graphe est orienté si et seulement si `oriente` = true */
graph* init_graph(int size, bool oriente);

/* Ajoute un arc entre les sommets `s1` et `s2` dans le graphe `g` */
void add_arc(graph* g, int s1, int s2);

/* Retire l'arc entre les sommets `s1` et `s2` dans le graphe `g` */
void delete_arc(graph*g, int s1, int s2);

/* Ajoute un arc entre les sommets `s1` et `s2` avec le poid `w` dans le graphe `g` */
void add_arc_p(graph* g, int s1, int s2, float w);

/* Libère le graphe `g` */
void free_graph(graph* g);

/* Parcour depuis `s1` utilisant la fonction `add` pour ajouter dans le sac et `ext` pour retirer un élément du sac */
file* parcour(graph* g, int s1, void (*add)(pf*, void*), void* (*ext)(pf*));

/* Parcour en largeur depuis `s1` */
file* parcour_largeur(graph* g, int s1);

/* Parcour en profondeur depuis `s1` */
file* parcour_profondeur(graph* g, int s1);

/* Algorithme de Dijkstra depuis `s1` */
int* dijkstra(graph* g, int s1);


#endif // GRAPH_H