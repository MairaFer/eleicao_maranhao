#include "arvore_binaria.h"
#include "funcoes_aux.h"
#include <stdio.h>

#define NUM_ZONA 111
#define MAX_LINHA 150
#define MAX 1024
#define RAIZ 0
#define ESQUERDA 1
#define DIREITA 2
#define MAX_BUFFER 100000

const Dados VL_NULO = {0, 0, 0, 0, 0, 0, "", 0};


tree posiciona_arvore_para_carregar(tree t) {
  if (t != NULL) {
    while (t->esq != NULL) {
      t = t->esq;
    }
  }
  return t;
}


int carrega_dados(char *nome_arq1, tree *t) {
  FILE *arquivo;
  Dados dados = VL_NULO;
  char pala[MAX_LINHA], linha[1024];
  ;
  short local_insercao = ESQUERDA; 
  tree aux;

  arquivo = fopen(nome_arq1, "r");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
  }

  if (*t == NULL)
    local_insercao = RAIZ;
  else
    aux = posiciona_arvore_para_carregar(*t);
 
  char cabecalho[MAX];
  if (fgets(cabecalho, MAX, arquivo) == NULL) {
    perror("Erro ao ler o cabeçalho");
    fclose(arquivo);
    return 1;
  }

  while (!feof(arquivo)) {
    for (int i = 1; i <= 13; i++) {
      strcpy(pala, ler_palavra(arquivo));
    }
    
    strcpy(pala, ler_palavra(arquivo)); 
    removeAspas(pala);
    dados.NR_ZONA = atoi(pala);

    strcpy(pala, ler_palavra(arquivo));
    removeAspas(pala);
    dados.NR_SECAO = atoi(pala);

    for (int i = 1; i <= 7; i++) {
      strcpy(pala, ler_palavra(arquivo));
    }

    strcpy(pala, ler_palavra(arquivo)); 
    removeAspas(pala);
    dados.QT_APTOS = atoi(pala);
    strcpy(pala, ler_palavra(arquivo)); 
    removeAspas(pala);
    dados.QT_COMPARECIMENTO = atoi(pala);
    strcpy(pala, ler_palavra(arquivo)); 
    removeAspas(pala);
    dados.QT_ABSTENCOES = atoi(pala);

    strcpy(pala, ler_palavra(arquivo));
    strcpy(pala, ler_palavra(arquivo));
    strcpy(pala, ler_palavra(arquivo));
    strcpy(pala, ler_palavra(arquivo));

    strcpy(pala, ler_palavra(arquivo)); 
    removeAspas(pala);
    dados.NR_VOTAVEL = atoi(pala);

    strcpy(pala, ler_palavra(arquivo)); 
    removeAspas(pala);
    strcpy(dados.NM_VOTAVEL, pala);

    strcpy(pala, ler_palavra(arquivo)); 
    removeAspas(pala);
    dados.QT_VOTOS = atoi(pala);

    for (int i = 1; i <= 13; i++) {
      strcpy(pala, ler_palavra(arquivo));
    }
    aux = incluir_na_arvore(&aux, local_insercao, dados);
    if (local_insercao == RAIZ)
      *t = aux; 
    local_insercao = DIREITA;
  
  }
  fclose(arquivo);
}

void listar_por_zona(tree t, int zona) {
  if (vazia(t)) {
    return;
  }
  listar_por_zona(t->esq, zona);
  if (t->info.NR_ZONA == zona) {
    printf("Seca  o: %d\tCandidato: %s\tVotos: %d\n", t->info.NR_SECAO, t->info.NM_VOTAVEL, t->info.QT_VOTOS);
  }
  listar_por_zona(t->dir, zona);
}

void informar_votos_por_zona(tree t, int zona, int *votos_candidato1, int *votos_candidato2) {
  if(vazia(t)){
    return;
  }
  informar_votos_por_zona(t->esq, zona, votos_candidato1, votos_candidato2);
  if(t->info.NR_ZONA == zona){
    if(t->info.NR_VOTAVEL == 13){
      *votos_candidato1 += t->info.QT_VOTOS;
    } else if (t->info.NR_VOTAVEL == 22){
      *votos_candidato2 += t->info.QT_VOTOS;
    }
  }
  informar_votos_por_zona(t->dir, zona, votos_candidato1, votos_candidato2);
}

void informar_votos_por_secao(tree t, int zona, int secao) {
    int votos_candidato1 = 0, votos_candidato2 = 0;
    somar_votos_candidatos_secao(t, zona, secao, &votos_candidato1, &votos_candidato2);

    printf("Total de votos para o candidato 1 na Zona %d, Seção %d: %d\n", zona, secao, votos_candidato1);
    printf("Total de votos para o candidato 2 na Zona %d, Seção %d: %d\n", zona, secao, votos_candidato2);
}

void informar_qtde_secoes(tree t, int zona) {
    int qtde_secoes = contar_secoes_recursivo(t, zona);
    printf("A Zona Eleitoral %d possui %d seções eleitorais.\n", zona, qtde_secoes);
}


int main() {
  tree arvore;
  define(&arvore);
  
  int opcao, candidato = 0, votos_candidato1 = 0, votos_candidato2 = 0;
  int zona = 0, secao = 0;
  char arquivo[30];

  do {
    printf("\n--------------------------MENU------------------------\n");
    printf("[1] - Carregar dados da árvore\n");
    printf("[2] - Listar por Zona Eleitoral\n");
    printf("[3] - Informar a quantidade de votos por Zona Eleitoral\n");
    printf("[4] - Informar a quantidade de votos por Seção Eleitoral\n");
    printf("[5] - Informar a quantidade de seções eleitorais por Zona Eleitoral\n");
    printf("[6] - Informar em qual Zona Eleitoral um candidato obteve a maior porcentagem de votos\n");
    printf("[0] - Sair\n");
    printf("-------------------------------------------------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      snprintf(arquivo, sizeof(arquivo), "2t_MA.csv");
      printf("\n%s\n", arquivo);
      carrega_dados(arquivo, &arvore);
      printf("Dados carregados.\n");
      getchar();
      break;
      
    case 2:
      printf("Informe o número da Zona Eleitoral: ");
      scanf("%d", &zona);
      listar_por_zona(arvore, zona);
      printf("\nAperte ENTER para continuar\n");
      getchar();
      break;
      
    case 3:
      printf("Informe o número da Zona Eleitoral: ");
      scanf("%d", &zona);
      informar_votos_por_zona(arvore, zona, &votos_candidato1, &votos_candidato2);
      printf("Votos para candidato 1 - Luiz Inacio Lula da Silva \nZona: %d\n %d votos", zona, votos_candidato1);
      getchar();
      printf("\nVotos para candidato 2 - bolsonaro \nZona: %d\n %d", zona, votos_candidato2);
      printf("\nAperte ENTER para continuar\n");
      getchar();
      break;

    case 4:
      printf("Informe o número da Zona Eleitoral: ");
      scanf("%d", &zona);
      printf("Informe o número da Seção Eleitoral: "); 
      scanf("%d", &secao);
      informar_votos_por_secao(arvore, zona, secao); 
     
      getchar();
      break;
      
    case 5:
      printf("Informe o número da Zona Eleitoral: ");
      scanf("%d", &zona);
      informar_qtde_secoes(arvore, zona); 
      break;

      
    case 6:
      informar_maior_porcentagem(arvore, 13);
      informar_maior_porcentagem(arvore, 22);
      break;
      
    case 0:
      printf("Encerrando o programa.\n");
      break;
      default:
      printf("Opção inválida. Tente novamente.\n");
    }
  } while (opcao != 0);
}    