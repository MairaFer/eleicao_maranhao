// arvore_binaria.c
#include "arvore_binaria.h"
#include <stdlib.h>
#include <stdio.h>

void define(tree *t) {
    *t = NULL;
}

void criaRaiz(tree *t, Dados item) {
    tree no = (ptrNodo)malloc(sizeof(struct nodo));
    no->esq = NULL;
    no->dir = NULL;
    no->info = item;
    *t = no;
}

int vazia(tree t) {
    return (t == NULL);
}

tree criarNodoDir(tree t, Dados item) {
    tree no;
    no = (ptrNodo)malloc(sizeof(struct nodo));
    no->esq = NULL;
    no->dir = NULL;
    no->info = item;
    t->dir = no;
    return t->dir;
}

tree criarNodoEsq(tree t, Dados item) {
    tree no;
    no = (ptrNodo)malloc(sizeof(struct nodo));
    no->esq = NULL;
    no->dir = NULL;
    no->info = item;
    t->esq = no;
    return t->esq;
}

ptrNodo busca(tree t, Dados item) {
    if (t == NULL || t->info.NR_ZONA == item.NR_ZONA) {
        return t;
    } else if (t->info.NR_ZONA > item.NR_ZONA) {
        return busca(t->esq, item);
    } else {
        return busca(t->dir, item);
    }
}

tree incluir_na_arvore(tree *t, int local, Dados dados) {
    if (local == RAIZ) {
        criaRaiz(t, dados);
        return *t;
    } else if (local == ESQUERDA) {
        return criarNodoEsq(*t, dados);
    } else {
        return criarNodoDir(*t, dados);
    }
}


