#include <stdio.h>
#include <string.h>
#include "lib.h"

void exibe_menu(int *opcao) {

  // função exibe várias opções e pede ao usuário escolher dentre as opções
  printf("Selecione uma das opções abaixo:\n");
  printf("1. Criar tarefa\n");
  printf("2. Deletar tarefa\n");
  printf("3. Listar tarefa\n");
  printf("0. Sair\n");
  printf("Opção: ");
  scanf("%d", opcao);
  
}

void cadastra_tarefa(lista_tarefa  *lt) {
  
  char descricao[300];
  char categoria[100];
  char estado[20];
  int prioridade;
  tarefa tarefa;
  
  printf("Digite a descricao da tarefa %d: ", lt->qtnd);
  scanf("%s", descricao);
  printf("\n");
  strcpy(tarefa.descricao, descricao); // copia a string descrição para a variável descricao dentro do struct tarefa
  
  printf("Digite a categoria da tarefa: ");
  scanf("%s", categoria);
  printf("\n");
  strcpy(tarefa.categoria, categoria); // copia a string categoria para a variável categoria do struct tarefa
  
  printf("Digite a priorirade da tarefa: ");
  scanf("%d", &prioridade);
  printf("\n");
  tarefa.prioridade = prioridade; // atribui à variável prioridade dentro do struct tarefa o inteiro digitado pelo usuário

  printf("Digite o estado da tarefa: ");
  scanf("%s", estado);
  strcpy(tarefa.estado, estado); // copia a string estado para a variável estado dentro do struct tarefa

  if (tarefa.prioridade >= 0 && tarefa.prioridade <= 10 && strcmp(tarefa.estado, "completo") == 0 || strcmp(tarefa.estado, "incompleto") == 0 || strcmp(tarefa.estado, "em andamento") == 0) { // valida a variável prioridade
    lt->tarefa[lt->qtnd] = tarefa; // adiciona o struct tarefa preenchido com os dados na variável tarefa[100] do struct lista_tarefa
    lt->qtnd += 1; // faz a variável apontar para a próxima posição do array de tarefas
    printf("Dados cadastrados com sucesso!\n");
  }
  else {
    printf("Dados inválidos.\n");
  }
  
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