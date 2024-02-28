
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


list* init_list(void* val);
pf* init_pf();

void iter_pf(pf* p, void (*fnc)(void*), enum position start);
void iteri_pf(pf* p, void (*fnc)(int, void*), enum position start);
void* map_pf(pf* p, void* (*fnc)(void*), enum position start);
void* mapi_pf(pf* p, void* (*fnc)(int, void*), enum position start);

void add_pf(pf* p, void* val, enum position pos);
void* extract_pf(pf* p, enum position pos);
void free_pf(pf* p, void (*free_data)(void*));
bool pf_vide(pf* p);

file* init_file();
void add_file(file* f, void* val);
void* extract_file(file* f);
void free_file(file* f, void (*free_data)(void*));
bool file_vide(file* f);
void iter_file(file* f, void (*fnc)(void*));
void iteri_file(file* f, void (*fnc)(int, void*));
void* map_file(file* f, void* (*fnc)(void*));
void* mapi_file(file* f, void* (*fnc)(int, void*));

pile* init_pile();
void add_pile(pile* p, void* val);
void* extract_pile(pile* p);
void free_pile(pile* p, void (*free_data)(void*));
bool pile_vide(pile* p);
void iter_pile(pile* p, void (*fnc)(void*));
void iteri_pile(pile* p, void (*fnc)(int, void*));
void* map_pile(pile* p, void* (*fnc)(void*));
void* mapi_pile(pile* p, void* (*fnc)(int, void*));



#endif // PILE_FILE_H