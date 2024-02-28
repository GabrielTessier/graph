
#include <stdlib.h>
#include <stdbool.h>

#include "../include/pile_file.h"

list* init_list(void* val) {
    list* l = (list*) malloc(sizeof(list));
    l->post = NULL;
    l->pre = NULL;
    l->val = val;
    return l;
}

pf* init_pf() {
    pf* p = (pf*) malloc(sizeof(pf));
    p->d = NULL;
    p->f = NULL;
    return p;
}

void iter_pf(pf* p, void (*fnc)(void*), enum position start) {
    list* il = NULL;
    if (start == DEBUT) il = p->d;
    else if (start == FIN) il = p->f;
    while (il != NULL) {
        fnc(&il->val);
        if (start == DEBUT) il = il->post;
        else if (start == FIN) il = il->pre;
    }
}

void iteri_pf(pf* p, void (*fnc)(int, void*), enum position start) {
    list* il = NULL;
    if (start == DEBUT) il = p->d;
    else if (start == FIN) il = p->f;
    int i = 0;
    while (il != NULL) {
        fnc(i, &il->val);
        i++;
        if (start == DEBUT) il = il->post;
        else if (start == FIN) il = il->pre;
    }
}

void* map_pf(pf* p, void* (*fnc)(void*), enum position start) {
    pf* res = init_pf();
    list* il = NULL;
    enum position nstart;
    if (start == DEBUT) {
        nstart = FIN;
        il = p->d;
    } else if (start == FIN) {
        nstart = DEBUT;
        il = p->f;
    }
    while (il != NULL) {
        add_pf(res, fnc(&il->val), nstart);
        if (start == DEBUT) il = il->post;
        else if (start == FIN) il = il->pre;
    }
    return res;
}

void* mapi_pf(pf* p, void* (*fnc)(int, void*), enum position start) {
    pf* res = init_pf();
    list* il = NULL;
    enum position nstart;
    if (start == DEBUT) {
        nstart = FIN;
        il = p->d;
    } else if (start == FIN) {
        nstart = DEBUT;
        il = p->f;
    }
    int i = 0;
    while (il != NULL) {
        add_pf(res, fnc(i, &il->val), nstart);
        i++;
        if (start == DEBUT) il = il->post;
        else if (start == FIN) il = il->pre;
    }
    return res;
}

void add_pf(pf* p, void* val, enum position pos) {
    if (p->d == NULL) {
        list* il = init_list(val);
        p->d = il;
        p->f = il;
    } else {
        if (pos == DEBUT) {
            list* il = init_list(val);
            il->post = p->d;
            p->d->pre = il;
            p->d = il;
        } else if (pos == FIN) {
            list* il = init_list(val);
            il->pre = p->f;
            p->f->post = il;
            p->f = il;
        }
    }
}

void* extract_pf(pf* p, enum position pos) {
    if (pos == DEBUT && p->d != NULL) {
        void* val = p->d->val;
        list* d = p->d;
        if (p->d->post != NULL) {
            p->d = p->d->post;
            p->d->pre = NULL;
            if (p->d == p->f) p->f->pre = NULL;
        } else {
            p->d = NULL;
            p->f = NULL;
        }
        free(d);
        return val;
    } else if (pos == FIN && p->f != NULL) {
        void* val = p->f->val;
        list* f = p->f;
        if (p->f->pre != NULL) {
            p->f = p->f->pre;
            p->f->post = NULL;
            if (p->d == p->f) p->d->post = NULL;
        } else {
            p->d = NULL;
            p->f = NULL;
        }
        free(f);
        return val;
    }
    return NULL;
}

void free_pf(pf* p, void (*free_data)(void*)) {
    while (p->d != NULL) {
        void* data = extract_pf(p, FIN);
        if (free_data != NULL) free_data(data);
    }
    free(p);
}

bool pf_vide(pf* p) {
    return p->d == NULL;
}


file* init_file() {
    file* f = (file*) malloc(sizeof(file));
    f->d = NULL;
    f->f = NULL;
    return f;
}

void add_file(file* f, void* val) {
    add_pf(f, val, DEBUT);
}

void* extract_file(file* f) {
    return extract_pf(f, FIN);
}

void free_file(file* f, void (*free_data)(void*)) {
    free_pf(f, (*free_data));
}

bool file_vide(file* f) {
    return pf_vide(f);
}

void iter_file(file* f, void (*fnc)(void*)) {
    iter_pf(f, (*fnc), DEBUT);
}
void iteri_file(file* f, void (*fnc)(int, void*)) {
    iteri_pf(f, (*fnc), DEBUT);
}
void* map_file(file* f, void* (*fnc)(void*)) {
    return map_pf(f, (*fnc), DEBUT);
}
void* mapi_file(file* f, void* (*fnc)(int, void*)) {
    return mapi_pf(f, (*fnc), DEBUT);
}

pile* init_pile() {
    pile* p = (pile*) malloc(sizeof(pile));
    p->d = NULL;
    p->f = NULL;
    return p;
}

void add_pile(pile* p, void* val) {
    add_pf(p, val, DEBUT);
}

void* extract_pile(pile* p) {
    return extract_pf(p, DEBUT);
}

void free_pile(pile* p, void (*free_data)(void*)) {
    free_pf(p, (*free_data));
}

bool pile_vide(pile* p) {
    return pf_vide(p);
}

void iter_pile(pile* p, void (*fnc)(void*)) {
    iter_pf(p, (*fnc), FIN);
}
void iteri_pile(pile* p, void (*fnc)(int, void*)) {
    iteri_pf(p, (*fnc), FIN);
}
void* map_pile(pile* p, void* (*fnc)(void*)) {
    return map_pf(p, (*fnc), FIN);
}
void* mapi_pile(pile* p, void* (*fnc)(int, void*)) {
    return mapi_pf(p, (*fnc), FIN);
}