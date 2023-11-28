//funcoes_aux.h
#ifndef FUNCOES_AUX_H
#define FUNCOES_AUX_H

#include "arvore_binaria.h" 
#include <stdio.h> 

#ifndef DADOS_STRUCT
#define DADOS_STRUCT

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


#endif

Dados ler_dados_do_csv(char *linha);
void imprimir_zona_eleitoral(tree t, Dados dados);
void listar_por_zona_recursivo(tree t, int zona);
void somar_votos_candidatos(tree t, int zona, int *votos_candidato1, int *votos_candidato2);
void somar_votos_candidatos_secao(tree t, int zona, int secao, int *votos_candidato1, int *votos_candidato2);
void calcular_total_votos(tree t, int zona, int *total_votos, int *total_votos_candidato, int candidato);
int contar_secoes_recursivo(tree t, int zona);
float calcular_porcentagem_votos(tree t, int zona, int candidato);
void porcentagem_zona(tree t, int candidato, int nr_zona);
void informar_maior_porcentagem(tree t, int candidato);
char* ler_palavra(FILE *arq);
void removeAspas(char *str);

#endif
