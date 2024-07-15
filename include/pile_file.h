
#ifndef PILE_FILE_H
#define PILE_FILE_H

#include <stdbool.h>

struct list {
    void* val;
    struct list* pre;
    struct list* post;
};
typedef struct list list;

struct pf {
    list* d;
    list* f;
};
typedef struct pf pf;

typedef pf file;
typedef pf pile;

enum position {DEBUT, FIN};

/* Initialise un maillon avec pour valeur `val` */
list* init_list(void* val);

/* Initialise une liste doublement chaînée */
pf* init_pf();

/* Applique la fonction `fnc` à chaque élément de la liste `p` en partant de la position `start` */
void iter_pf(pf* p, void (*fnc)(void*), enum position start);

/* Applique la fonction `fnc` à chaque élément de la liste `p` en partant de la position `start` */
void iteri_pf(pf* p, void (*fnc)(int, void*), enum position start);

/* Créer une nouvelle liste dont chaque élément est le résultat de `fnc` sur un élément de `p` */
void* map_pf(pf* p, void* (*fnc)(void*), enum position start);

/* Créer une nouvelle liste dont chaque élément est le résultat de `fnc` sur un élément de `p` */
void* mapi_pf(pf* p, void* (*fnc)(int, void*), enum position start);

/* Ajoute un maillon de valeur `val` en position `pos` à la liste `p` */
void add_pf(pf* p, void* val, enum position pos);

/* Extrait la valeur du maillon en position `pos` de la liste `p` */
void* extract_pf(pf* p, enum position pos);

/* Libère la liste `p` et libère chaque maillon

   Pour libérer un maillon la fonction `free_data` est utilisée pour libérer la donner du maillon 
   
   Si les données des maillons ne doit pas être libérer alors mettre `NULL` pour `free_data` */
void free_pf(pf* p, void (*free_data)(void*));

/* Renvoie si la liste est vide ou non */
bool pf_vide(pf* p);


/* Initialise une liste */
file* init_file();

/* Ajoute un maillon de valeur `val` à la liste `p` */
void add_file(file* f, void* val);

/* Extrait la valeur du premier maillon de la liste `p` */
void* extract_file(file* f);

/* Libère la liste `p` et libère chaque maillon

   Pour libérer un maillon la fonction `free_data` est utilisée pour libérer la donner du maillon 
   
   Si les données des maillons ne doit pas être libérer alors mettre `NULL` pour `free_data` */
void free_file(file* f, void (*free_data)(void*));

/* Renvoie si la liste est vide ou non */
bool file_vide(file* f);

/* Applique la fonction `fnc` à chaque élément de la liste `p` */
void iter_file(file* f, void (*fnc)(void*));

/* Applique la fonction `fnc` à chaque élément de la liste `p` */
void iteri_file(file* f, void (*fnc)(int, void*));

/* Créer une nouvelle liste dont chaque élément est le résultat de `fnc` sur un élément de `p` */
void* map_file(file* f, void* (*fnc)(void*));

/* Créer une nouvelle liste dont chaque élément est le résultat de `fnc` sur un élément de `p` */
void* mapi_file(file* f, void* (*fnc)(int, void*));


/* Initialise une pile */
pile* init_pile();

/* Ajoute un maillon de valeur `val` à la pile `p` */
void add_pile(pile* p, void* val);

/* Extrait la valeur du premier maillon de la pile `p` */
void* extract_pile(pile* p);

/* Libère la pile `p` et libère chaque maillon

   Pour libérer un maillon la fonction `free_data` est utilisée pour libérer la donner du maillon 
   
   Si les données des maillons ne doit pas être libérer alors mettre `NULL` pour `free_data` */
void free_pile(pile* p, void (*free_data)(void*));

/* Renvoie si la pile est vide ou non */
bool pile_vide(pile* p);

/* Applique la fonction `fnc` à chaque élément de la pile `p` */
void iter_pile(pile* p, void (*fnc)(void*));

/* Applique la fonction `fnc` à chaque élément de la pile `p` */
void iteri_pile(pile* p, void (*fnc)(int, void*));

/* Créer une nouvelle pile dont chaque élément est le résultat de `fnc` sur un élément de `p` */
void* map_pile(pile* p, void* (*fnc)(void*));

/* Créer une nouvelle pile dont chaque élément est le résultat de `fnc` sur un élément de `p` */
void* mapi_pile(pile* p, void* (*fnc)(int, void*));


#endif // PILE_FILE_H