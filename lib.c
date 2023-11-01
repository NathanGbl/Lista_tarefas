#include <stdio.h>
#include <string.h>
#include "lib.h"

void exibe_menu(int *opcao) {

  // função exibe várias opções e pede ao usuário escolher dentre as opções
  printf("Selecione uma das opções abaixo:\n");
  printf("1. Criar tarefa\n");
  printf("2. Deletar tarefa\n");
  printf("3. Listar tarefa\n");
  printf("4. Alterar tarefa\n");
  printf("0. Sair\n");
  printf("Opção: ");
  scanf("%d", opcao);
  
}

// gerencia_tarefa

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
    return;
  }
  else {
    printf("Dados inválidos.\n");
    return;
  }
  
}

void listar_tarefa(lista_tarefa *lt) {
  
  for (int x = 0; x < lt->qtnd; x++) { 
    // loop que itera sobre as tarefas dentro do array de struct tarefa[100] e exibe cada informação até chegar na última tarefa através do lt->qtnd
    printf("\nTarefa %d\n", x);
    printf("\tDescrição: %s\n", lt->tarefa[x].descricao);
    printf("\tCategoria: %s\n", lt->tarefa[x].categoria);
    printf("\tPrioridade: %d\n", lt->tarefa[x].prioridade);
    printf("\tEstado: %s\n\n", lt->tarefa[x].estado);
  }
  
}

void deleta_tarefa(lista_tarefa *lt, int tarefa) {

  printf("Digite o número da tarefa para deletá-la: ");
  scanf("%d", &tarefa);

  for (; tarefa < lt->qtnd; tarefa++) { 
    // loop que itera a partir da posição da tarefa dentro do array tarefa[100] do struct lista_tarefa que o usuário quer deletar.
    // o loop sobrescreve as variáveis dentro do struct tarefa com as variáveis da próxima tarefa a partir da posição que o usuário digitar
    strcpy(lt->tarefa[tarefa].descricao, lt->tarefa[tarefa + 1].descricao);
    strcpy(lt->tarefa[tarefa].categoria, lt->tarefa[tarefa + 1].categoria);
    lt->tarefa[tarefa].prioridade = lt->tarefa[tarefa].prioridade;
    strcpy(lt->tarefa[tarefa].estado, lt->tarefa[tarefa + 1].estado);
  }
  lt->qtnd -= 1; // diminui o lt->qtnd para a variável apontar para a última tarefa
  printf("\tTarefa deletada com sucesso!\n");
  
}

void exibe_menu2(int *tarefa, int *dado_alterado) {
  
  printf("\t Número da tarefa que deseja alterar: ");
  scanf("%d", tarefa);
  printf("\n");

  printf("\tEscolha o dado da tarefa %d que deseja alterar:\n", *tarefa);
  printf("\t1. Descrição\n");
  printf("\t2. Categoria\n");
  printf("\t3. Prioridade\n");
  printf("\t4. Estado\n");
  printf("\tOpção: ");
  scanf("%d", dado_alterado);
  printf("\n");
  
}

void alterar_tarefa(lista_tarefa *lt) {

  int tarefa;
  int dado_alterado;
  int prioridade;
  char estado[20];
  exibe_menu2(&tarefa, &dado_alterado);

  if (dado_alterado == 1) {
    printf("\tDigite a nova descrição: ");
    scanf("%s", lt->tarefa[tarefa].descricao);
    printf("\n\tMudança realizada com sucesso!\n");
  }
  else if (dado_alterado == 2) {
    printf("\tDigite a nova categoria: ");
    scanf("%s", lt->tarefa[tarefa].categoria);
    printf("\n\tMudança realizada com sucesso!\n");
  }
  else if (dado_alterado == 3) {
    printf("\tDigite a nova prioridade: ");
    scanf("%d", &prioridade);
    if (prioridade >= 0 && prioridade <= 10) {
      lt->tarefa[tarefa].prioridade = prioridade;
      printf("\n\tMudança realizada com sucesso!\n");
    }
    else {
      printf("\n\tDados inválidos. Mudança cancelada.\n");
    }
  }
  else if (dado_alterado == 4) {
    printf("\tDigite o novo estado: ");
    scanf("%s", estado);
    if (strcmp(estado, "concluído") == 0 || strcmp(estado, "em andamento") == 0 || strcmp(estado, "incompleto") == 0) {
      strcpy(lt->tarefa[tarefa].estado, estado);
      printf("\n\tMudança realizada com sucesso!\n");
    }
    else {
      printf("\n\tDados inválidos. Mudança cancelada.\n");
    }
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