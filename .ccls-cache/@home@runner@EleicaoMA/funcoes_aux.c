// funcoes_aux.c
#include <stdio.h>
#include "funcoes_aux.h"
#define MAX_LINHA 150

struct ZonaInfo {
  int NR_ZONA;
  int numSecoes; 
  float votos;
  float votosC;
};
struct ZonaInfo zonaInfo;

Dados ler_dados_do_csv(char *linha) {
    Dados dados;
    sscanf(linha, "%d,%d,%d,%d,%d,%d,%49[^,],%d",
           &dados.NR_ZONA, &dados.NR_SECAO, &dados.QT_APTOS, &dados.QT_COMPARECIMENTO,
           &dados.QT_ABSTENCOES, &dados.NR_VOTAVEL, dados.NM_VOTAVEL, &dados.QT_VOTOS);

    return dados;
}


void imprimir_zona_eleitoral(tree t, Dados dados) {
    printf("NR_ZONA: %d, NR_SECAO: %d, QT_APTOS: %d, QT_COMPARECIMENTO: %d, "
           "QT_ABSTENCOES: %d, NR_VOTAVEL: %d, NM_VOTAVEL: %s, QT_VOTOS: %d\n",
           dados.NR_ZONA, dados.NR_SECAO, dados.QT_APTOS, dados.QT_COMPARECIMENTO,
           dados.QT_ABSTENCOES, dados.NR_VOTAVEL, dados.NM_VOTAVEL, dados.QT_VOTOS);
}


void somar_votos_candidatos_secao(tree t, int zona, int secao, int *votos_candidato1, int *votos_candidato2) {
    if (t != NULL) {
        if (t->info.NR_ZONA == zona && t->info.NR_SECAO == secao) {
            if (t->info.NR_VOTAVEL == 13) {
                *votos_candidato1 += t->info.QT_VOTOS;
            } else if (t->info.NR_VOTAVEL == 22) {
                *votos_candidato2 += t->info.QT_VOTOS;
            }
        }
        somar_votos_candidatos_secao(t->esq, zona, secao, votos_candidato1, votos_candidato2);

        somar_votos_candidatos_secao(t->dir, zona, secao, votos_candidato1, votos_candidato2);
    }
}

int contar_secoes_recursivo(tree t, int zona) {
    if (t == NULL) {
        return 0;
    }

    int qtde_secoes = 0;
    if (t->info.NR_ZONA == zona) {
        qtde_secoes++;
    }

    qtde_secoes += contar_secoes_recursivo(t->esq, zona);
    qtde_secoes += contar_secoes_recursivo(t->dir, zona);

    return qtde_secoes;
}

void calcular_total_votos(tree t, int zona, int *total_votos, int *total_votos_candidato, int candidato) {
    if (t != NULL && t->info.NR_ZONA == zona) {
        *total_votos += t->info.QT_VOTOS;
        if (t->info.NR_VOTAVEL == candidato) {
            *total_votos_candidato += t->info.QT_VOTOS;
        }
    }
}

float calcular_porcentagem_votos(tree t, int zona, int candidato) {
    int total_votos_candidato = 0;
    int total_votos = 0;

    calcular_total_votos(t, zona, &total_votos, &total_votos_candidato, candidato);

    return (total_votos > 0) ? ((float)total_votos_candidato / total_votos) * 100 : 0.0;
}

void porcentagem_zona(tree t, int candidato, int nr_zona) {
  if (t == NULL) {
      return;
  }
  porcentagem_zona(t->esq, candidato, nr_zona);
  if (t->info.NR_ZONA == nr_zona && t->info.NR_VOTAVEL == candidato) {
      zonaInfo.votosC += t->info.QT_VOTOS;
  }
  if (t->info.NR_ZONA == nr_zona) {
      zonaInfo.votos += t->info.QT_VOTOS;
  }
  porcentagem_zona(t->dir, candidato, nr_zona);
}

void informar_maior_porcentagem(tree t, int candidato) {
  double maior_porcentagem = -1,porcentagem = 0.0;
  int zona_maior_porcentagem = 0;

  for(int i=1;i<=111;i++){
    zonaInfo.votos = 0;
    zonaInfo.votosC =0;
    porcentagem_zona(t, candidato, i);
    porcentagem = (zonaInfo.votosC/zonaInfo.votos)*100;
    if(i == 1){
      zona_maior_porcentagem =1;
      maior_porcentagem = porcentagem;
    }else if(maior_porcentagem < porcentagem){
      maior_porcentagem = porcentagem;
      zona_maior_porcentagem = i;
    }
  }
  printf("O Candidato %d teve a maior porcentagem na Zona %d com: %.2f%% de votos\n", candidato,zona_maior_porcentagem ,maior_porcentagem);

}

char* ler_palavra(FILE *arq) {
char c;
char palavra[MAX_LINHA] =""; 
int indice = 0;
c = fgetc(arq);
while (c != EOF) {
       if (c == '\n' || c == ';') {
           palavra[indice] = '\0'; // Adiciona o caractere nulo ao final da palavra
          return palavra;
       } else {
          palavra[indice] = c; // Adiciona o caractere à palavra
          indice++;
      }
      c = fgetc(arq);
  }
// return '\0';
}

void removeAspas(char *str) {
    size_t length = strlen(str);

    // Verifica se a string tem pelo menos duas aspas duplas
    if (length >= 2 && str[0] == '"' && str[length - 1] == '"') {
        // Move o ponteiro para o segundo caractere
        memmove(str, str + 1, length - 2);

        // Adiciona um terminador nulo no final da string
        str[length - 2] = '\0';
    }
}