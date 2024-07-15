
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

/* Initialise un tas contenant un élément de valeur `val` et de donné `data`

   La fonction `cmp` est la fonction qui sera utilisé pour comparer les éléments du tas */
heap* init_heap(int val, void* data, bool (*cmp)(int, int));

/* Libère le tas `h` et libère chaque éléments du tas

   Pour libérer les données de chaque élément la fonction `free_data` est utilisée */
void free_heap(heap* h, void (*free_data)(void*));

/* Ajoute un élément de valeur `val` et de donnée `data` au tas `h` */
void add_heap(heap* h, int val, void* data);

/* Extrait le plus grand élément, d'après la fonction de comparaison, du tas `h`

   Renvoie la valeur de l'élément et stoke les donnés dans `pdata` */
int extract_heap(heap* h, void** pdata);


#endif // TAS_H