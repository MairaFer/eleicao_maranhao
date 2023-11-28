#include <stdio.h>
#include <funcao_aux.h>

Dados ler_dados_do_csv(char *linha) {
    Dados dados;
    sscanf(linha, "%d,%d,%d,%d,%d,%d,%49[^,],%d",
           &dados.NR_ZONA, &dados.NR_SECAO, &dados.QT_APTOS, &dados.QT_COMPARECIMENTO,
           &dados.QT_ABSTENCOES, &dados.NR_VOTAVEL, dados.NM_VOTAVEL, &dados.QT_VOTOS);

    return dados;
}

void imprimir_zona_eleitoral(Dados dados) {
    printf("NR_ZONA: %d, NR_SECAO: %d, QT_APTOS: %d, QT_COMPARECIMENTO: %d, "
           "QT_ABSTENCOES: %d, NR_VOTAVEL: %d, NM_VOTAVEL: %s, QT_VOTOS: %d\n",
           dados.NR_ZONA, dados.NR_SECAO, dados.QT_APTOS, dados.QT_COMPARECIMENTO,
           dados.QT_ABSTENCOES, dados.NR_VOTAVEL, dados.NM_VOTAVEL, dados.QT_VOTOS);
}


void listar_por_zona_recursivo(tree t, int zona) {
    if (t != NULL) {
        if (t->info.NR_ZONA == zona) {
            imprimir_zona_eleitoral(t->info);
        }
        listar_por_zona_recursivo(t->esq, zona); // recurssividade
        listar_por_zona_recursivo(t->dir, zona);
    }
}

void somar_votos_candidatos(tree t, int zona, int *votos_candidato1, int *votos_candidato2) {
  if (t != NULL) {
      if (t->info.NR_ZONA == zona) {
          if (t->info.NR_VOTAVEL == 1) {
              *votos_candidato1 += t->info.QT_VOTOS;
          } else if (t->info.NR_VOTAVEL == 2) {
              *votos_candidato2 += t->info.QT_VOTOS;
          }
      }
      somar_votos_candidatos(t->esq, zona, votos_candidato1, votos_candidato2);
      somar_votos_candidatos(t->dir, zona, votos_candidato1, votos_candidato2);
    }
}

void somar_votos_candidatos_secao(tree t, int zona, int secao, int *votos_candidato1, int *votos_candidato2) {
    if (t != NULL) {
        if (t->info.NR_ZONA == zona && t->info.NR_SECAO == secao) {
            if (t->info.NR_VOTAVEL == 1) {
                *votos_candidato1 += t->info.QT_VOTOS;
            } else if (t->info.NR_VOTAVEL == 2) {
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
  
    calcular_total_votos(t);

    return (total_votos > 0) ? ((float)total_votos_candidato / total_votos) * 100 : 0.0;
}
float calcular_porcentagem_votos(tree t, int zona, int candidato) {
    int total_votos_candidato = 0;
    int total_votos = 0;

    calcular_total_votos(t, zona, &total_votos, &total_votos_candidato, candidato);

    return (total_votos > 0) ? ((float)total_votos_candidato / total_votos) * 100 : 0.0;
}

void encontrar_maior_porcentagem_recursivo(tree t, int candidato, int *zona_maior_porcentagem, float *maior_porcentagem) {
    if (t != NULL) {
        float porcentagem = calcular_porcentagem_votos(t, t->info.NR_ZONA, candidato);

        if (porcentagem > *maior_porcentagem) {
            *maior_porcentagem = porcentagem;
            *zona_maior_porcentagem = t->info.NR_ZONA;
        }

      
        encontrar_maior_porcentagem_recursivo(t->esq, candidato, zona_maior_porcentagem, maior_porcentagem);
        encontrar_maior_porcentagem_recursivo(t->dir, candidato, zona_maior_porcentagem, maior_porcentagem);
    }
}

void informar_maior_porcentagem(tree t, int candidato) {
    int zona_maior_porcentagem = -1;
    float maior_porcentagem = 0.0;
  
    encontrar_maior_porcentagem_recursivo(t, candidato, &zona_maior_porcentagem, &maior_porcentagem);

    if (zona_maior_porcentagem != -1) {
        printf("O candidato %d obteve a maior porcentagem de votos na Zona Eleitoral %d: %.2f%%\n",
               candidato, zona_maior_porcentagem, maior_porcentagem);
    } else {
        printf("Nenhuma Zona Eleitoral encontrada para o candidato %d.\n", candidato);
    }
}
