typedef struct {
    int NR_ZONA;
    int NR_SECAO;
    int QT_APTOS;
    int QT_COMPARECIMENTO;
    int QT_ABSTENCOES;
    int NR_VOTAVEL;
    char NM_VOTAVEL[50];
    int QT_VOTOS;
} Dados;

typedef struct nodo *ptrNodo;

struct nodo {
    Dados info;
    ptrNodo esq;
    ptrNodo dir;
};

typedef ptrNodo tree;

#define RAIZ 0
#define ESQUERDA 1
#define DIREITA 2


void define(tree *t);
void criaRaiz(tree *t, Dados item);
int vazia(tree t);
tree criarNodoDir(tree t, Dados item);
tree criarNodoEsq(tree t, Dados item);
ptrNodo busca(tree t, Dados item);
tree incluir_na_arvore(tree *t, int local, Dados dados);

// add mais