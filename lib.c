#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"

void exibe_menu(int *opcao) {

  // função exibe várias opções e pede ao usuário escolher dentre as opções
  printf("Selecione uma das opções abaixo:\n");
  printf("1. Criar tarefa\n");
  printf("2. Deletar tarefa\n");
  printf("3. Listar tarefas\n");
  printf("4. Alterar tarefa\n");
  printf("5. Filtrar tarefas\n");
  printf("6. Exportar tarefas\n");
  printf("0. Sair\n");
  printf("Opção: ");
  scanf("%d", opcao);
  
}

void menu_estado(int *opcao, int modo) {

  if (modo == 1) {
    printf("\t\tSelecione o estado da tarefa:\n");
    printf("\t\t\t1. Completo\n");
    printf("\t\t\t2. Em andamento\n");
    printf("\t\t\t3. Não iniciado\n");
    printf("\t\t\tOpção: ");
    scanf("%d", opcao);
  }
  else if (modo == 2) {
    printf("\t\tSelecione o novo estado da tarefa:\n");
    printf("\t\t\t1. Completo\n");
    printf("\t\t\t2. Em andamento\n");
    printf("\t\t\t3. Não iniciado\n");
    printf("\t\t\tOpção: ");
    scanf("%d", opcao);
  }
  
}

// gerencia_tarefa

void cadastra_tarefa(lista_tarefa  *lt, int *opcao) {
  
  char descricao[300];
  char categoria[100];
  char estado[20];
  int prioridade;
  tarefa tarefa;
  printf("\tDigite a descricao da tarefa %d: ", lt->qtnd);
  getchar();
  scanf("%[^\n]", descricao);
  printf("\n");
  strcpy(tarefa.descricao, descricao); // copia a string descrição para a variável descricao dentro do struct tarefa
  
  printf("\tDigite a categoria da tarefa: ");
  getchar();
  scanf("%[^\n]", categoria);
  printf("\n");
  strcpy(tarefa.categoria, categoria); // copia a string categoria para a variável categoria do struct tarefa
  
  printf("\tDigite a priorirade da tarefa: ");
  scanf("%d", &prioridade);
  printf("\n");
  tarefa.prioridade = prioridade; // atribui à variável prioridade dentro do struct tarefa o inteiro digitado pelo usuário

  menu_estado(opcao, 1);
  switch(*opcao) {
    case 1:
      strcpy(tarefa.estado, "Completo");
      break;
    case 2:
      strcpy(tarefa.estado, "Em andamento");
      break;
    case 3:
      strcpy(tarefa.estado, "Não iniciado");
      break;
    default:
      printf("Opção inválida");
  }

  if (tarefa.prioridade >= 0 && tarefa.prioridade <= 10 && strcmp(tarefa.estado, "Completo") == 0 || strcmp(tarefa.estado, "Em andamento") == 0 || strcmp(tarefa.estado, "Não iniciado") == 0) { // valida a variável prioridade
    lt->tarefa[lt->qtnd] = tarefa; // adiciona o struct tarefa preenchido com os dados na variável tarefa[100] do struct lista_tarefa
    lt->qtnd += 1; // faz a variável apontar para a próxima posição do array de tarefas
    printf("Dados cadastrados com sucesso!\n");
  }
  else {
    printf("Dados inválidos.\n");
  }
  
}

void filtro_prioridade(lista_tarefa *lt) {

  int prioridade;
  int cont = 0;
  printf("\t\tDigite a prioridade desejada: ");
  scanf("%d", &prioridade);
  
  for (int i = 0; i < lt->qtnd; i++) {
    if (lt->tarefa[i].prioridade == prioridade) {
      printf("\t\tTarefa %d\n", i);
      printf("\t\t\tDescrição: %s\n", lt->tarefa[i].descricao);
      printf("\t\t\tCategoria: %s\n", lt->tarefa[i].categoria);
      printf("\t\t\tPrioridade: %d\n", lt->tarefa[i].prioridade);
      printf("\t\t\tEstado: %s\n", lt->tarefa[i].estado);
      cont += 1;
    }
  }
  if (cont == 0) {
    printf("\t\tNão há tarefas com a prioridade %d.\n", prioridade);
  }
  
}

void filtro_estado(lista_tarefa *lt, int *opcao) {
  
  menu_estado(opcao, 1);
  if (*opcao == 1) {
    for (int i = 0; i < lt->qtnd; i++) {
      if (strcmp(lt->tarefa[i].estado, "Completo") == 0) {
        printf("\t\tTarefa %d\n", i);
        printf("\t\t\tDescrição: %s\n", lt->tarefa[i].descricao);
        printf("\t\t\tCategoria: %s\n", lt->tarefa[i].categoria);
        printf("\t\t\tPrioridade: %d\n", lt->tarefa[i].prioridade);
        printf("\t\t\tEstado: %s\n", lt->tarefa[i].estado);
      }
    }
  }
  else if (*opcao == 2) {
    for (int i = 0; i < lt->qtnd; i++) {
      if (strcmp(lt->tarefa[i].estado, "Em andamento") == 0) {
        printf("\t\tTarefa %d\n", i);
        printf("\t\t\tDescrição: %s\n", lt->tarefa[i].descricao);
        printf("\t\t\tCategoria: %s\n", lt->tarefa[i].categoria);
        printf("\t\t\tPrioridade: %d\n", lt->tarefa[i].prioridade);
        printf("\t\t\tEstado: %s\n", lt->tarefa[i].estado);
      }
    }
  }
  else if (*opcao == 3) {
    for (int i = 0; i < lt->qtnd; i++) {
      if (strcmp(lt->tarefa[i].estado, "Não iniciado") == 0) {
        printf("\t\tTarefa %d\n", i);
        printf("\t\t\tDescrição: %s\n", lt->tarefa[i].descricao);
        printf("\t\t\tCategoria: %s\n", lt->tarefa[i].categoria);
        printf("\t\t\tPrioridade: %d\n", lt->tarefa[i].prioridade);
        printf("\t\t\tEstado: %s\n", lt->tarefa[i].estado);
      }
    }
  }
  
}

void filtro_categoria(lista_tarefa *lt) {
  
  char categoria[101];
  int cont = 0;
  printf("\t\tDigite a categoria desejada: ");
  scanf("%s", categoria);

  for (int i = 0; i < lt->qtnd; i++) {
    if (strcmp(lt->tarefa[i].categoria, categoria) == 0) {
      cont += 1;
      printf("\t\tTarefa %d\n", i);
      printf("\t\t\tDescrição: %s\n", lt->tarefa[i].descricao);
      printf("\t\t\tCategoria: %s\n", lt->tarefa[i].categoria);
      printf("\t\t\tPrioridade: %d\n", lt->tarefa[i].prioridade);
      printf("\t\t\tEstado: %s\n", lt->tarefa[i].estado);
    }
  }
  if (cont == 0) {
    printf("\t\tCategoria não existe\n");
  }
  
}

int compara_prioridade(const void *valor1, const void *valor2) {

  int prioridade1 = (*(tarefa *)valor1).prioridade;
  int prioridade2 = (*(tarefa *)valor2).prioridade;

  if (prioridade1 > prioridade2) {
    return -1;
  }
  else if (prioridade1 < prioridade2) {
    return 1;
  }
  else {
    return 0;
  }
  
}

void filtro_categoria_prioridade(lista_tarefa *lt) {

  tarefa lt_categoria[100];  
  int lt_categoria_qtnd = 0;  
  char categoria[101];
  
  printf("\t\tCategoria desejada: ");
  scanf("%s", categoria);
  
  for (int i = 0; i < lt->qtnd; i++) {
    if (strcmp(lt->tarefa[i].categoria, categoria) == 0) {
    strcpy(lt_categoria[lt_categoria_qtnd].descricao, lt->tarefa[i].descricao);
    strcpy(lt_categoria[lt_categoria_qtnd].categoria, lt->tarefa[i].categoria);
    lt_categoria[lt_categoria_qtnd].prioridade = lt->tarefa[i].prioridade;
    strcpy(lt_categoria[lt_categoria_qtnd].estado, lt->tarefa[i].estado);
    lt_categoria_qtnd += 1;
    }
  }
  
  qsort(lt_categoria, lt_categoria_qtnd, sizeof(tarefa), compara_prioridade);
  
  for (int i = 0; i < lt_categoria_qtnd; i++) {
    printf("\t\tTarefa %d\n", i);
    printf("\t\t\tDescrição: %s\n", lt_categoria[i].descricao);
    printf("\t\t\tCategoria: %s\n", lt_categoria[i].categoria);
    printf("\t\t\tPrioridade: %d\n", lt_categoria[i].prioridade);
    printf("\t\t\tEstado: %s\n", lt_categoria[i].estado);
  }
  
  if (lt_categoria_qtnd == 0) {
    printf("\t\tCategoria não existe");
  }

}

void menu_filtros(int *opcao) {

  printf("\tEscolha um dos filtros abaixo:\n");
  printf("\t1. Filtrar por prioridade\n");
  printf("\t2. Filtrar por estado\n");
  printf("\t3. Filtrar por categoria\n");
  printf("\t4. Filtrar por categoria e prioridade\n");
  printf("\tOpção: ");
  scanf("%d", opcao);

}

void le_arquivo(lista_tarefa *lt) {

  FILE *f = fopen("tarefas", "rb");
  
  if (f == NULL) {
    return; // verifica se existe o arquivo "tarefas". Se não existir, o arquivo será criado ao finalizar o programa.
  }
  else {
    fread(lt, sizeof(lista_tarefa), 1, f); // Caso exista, atualiza as informações presentes no código. Por exemplo o lt->qtnd que sempre se inicia com 0, mas ao abrir o arquivo, o valor pode mudar.
    fclose(f);
  }
  return;
  
}

void escreve_arquivo(lista_tarefa *lt) {

  FILE *f = fopen("tarefas", "wb");

  if (f == NULL) {
    return; // verifica se existe o arquivo "tarefas". Se não existir, o arquivo será criado pela função escreve_arquivo.
  }
  else {
    fwrite(lt, sizeof(lista_tarefa), 1, f); // Coloca os dados do struct lista_tarefa no arquivo. Caso o arquivo não existam, essa linha cria o arquivo.
    fclose(f);
  }
  
}