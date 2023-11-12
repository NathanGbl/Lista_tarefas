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

  // menu para escolher o estado da tarefa
  if (modo == 1) {
    // versão do menu para qualquer outra função
    printf("\t\tSelecione o estado da tarefa:\n");
    printf("\t\t\t1. Completo\n");
    printf("\t\t\t2. Em andamento\n");
    printf("\t\t\t3. Não iniciado\n");
    printf("\t\t\tOpção: ");
    scanf("%d", opcao);
  }
  else if (modo == 2) {
    // versão do menu para a função de alterar o estado da tarefa
    printf("\t\tSelecione o novo estado da tarefa:\n");
    printf("\t\t\t1. Completo\n");
    printf("\t\t\t2. Em andamento\n");
    printf("\t\t\t3. Não iniciado\n");
    printf("\t\t\tOpção: ");
    scanf("%d", opcao);
  }
  
}

void cadastra_tarefa(lista_tarefa  *lt, int *opcao) {
  
  char descricao[300];
  char categoria[100];
  int prioridade;
  tarefa tarefa;
  printf("\tDigite a descricao da tarefa %d: ", lt->qtnd);
  clean_buffer();
  scanf("%[^\n]", descricao);
  printf("\n");
  strcpy(tarefa.descricao, descricao); // copia a string descrição para a variável descricao dentro do struct tarefa
  
  printf("\tDigite a categoria da tarefa: ");
  clean_buffer();
  scanf("%[^\n]", categoria);
  printf("\n");
  strcpy(tarefa.categoria, categoria); // copia a string categoria para a variável categoria do struct tarefa
  
  printf("\tDigite a priorirade da tarefa: ");
  scanf("%d", &prioridade);
  printf("\n");
  tarefa.prioridade = prioridade; // atribui à variável prioridade dentro do struct tarefa o inteiro digitado pelo usuário

  menu_estado(opcao, 1); // Chama a função para colocar o estado da tarefa
  switch(*opcao) {
    case 1:
      strcpy(tarefa.estado, "Completo"); // Atribui a variável estado dentro do struct tarefa a string correspondente a opção digitada pelo usuário.
      break;
    case 2:
      strcpy(tarefa.estado, "Em andamento");
      break;
    case 3:
      strcpy(tarefa.estado, "Não iniciado");
      break;
    default:
      printf("Opção inválida"); // Caso o usuário digite uma opção fora das disponíveis.
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

int compara_prioridade(const void *valor1, const void *valor2) {

  // função usava para o qsort da função filtro_categoria_prioridade
  // Essa função reorganiza de forma decrescente as prioridades de cada tarefa
  int prioridade1 = (*(tarefa *)valor1).prioridade; // Acessa a variável prioridade do struct tarefa na posição do *valor1
  int prioridade2 = (*(tarefa *)valor2).prioridade; // Acessa a variável prioridade do struct tarefa na posição do *valor2

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

void filtro_categoria_prioridade(lista_tarefa *lt, int modo) {

  tarefa lt_categoria[100];  
  int lt_categoria_qtnd = 0;  
  char categoria[101];

  printf("\t\tCategoria desejada: ");
  clean_buffer(); // Para que o scanf não registre o \n como input
  scanf("%[^\n]", categoria);

  for (int i = 0; i < lt->qtnd; i++) {
    // Loop que itera sobre todas as tarefas do struct lista_tarefa
    // Caso a categoria for igual a digitada pelo usuário, adiciona-a na lista lt_categoria
    if (strcmp(lt->tarefa[i].categoria, categoria) == 0) {
    strcpy(lt_categoria[lt_categoria_qtnd].descricao, lt->tarefa[i].descricao);
    strcpy(lt_categoria[lt_categoria_qtnd].categoria, lt->tarefa[i].categoria);
    lt_categoria[lt_categoria_qtnd].prioridade = lt->tarefa[i].prioridade;
    strcpy(lt_categoria[lt_categoria_qtnd].estado, lt->tarefa[i].estado);
    lt_categoria_qtnd += 1; // Aumenta a quantidade para apontar para a última tarefa
    }
  }

  qsort(lt_categoria, lt_categoria_qtnd, sizeof(tarefa), compara_prioridade); // Ordena de forma decrescente o array lt_categoria com base na prioridade

  if (modo == 0) {
    // Se for apenas para imprimir, o loop itera sobre a lista lt_categoria e imprime as tarefas dentro dela
    for (int i = 0; i < lt_categoria_qtnd; i++) {
      printf("\t\tTarefa %d\n", i);
      printf("\t\t\tDescrição: %s\n", lt_categoria[i].descricao);
      printf("\t\t\tCategoria: %s\n", lt_categoria[i].categoria);
      printf("\t\t\tPrioridade: %d\n", lt_categoria[i].prioridade);
      printf("\t\t\tEstado: %s\n", lt_categoria[i].estado);
    }
    
    if (lt_categoria_qtnd == 0) {
      printf("\t\tCategoria não existe\n");
    }
  }
  else if (modo == 1) {
    // Se for para escrever no arquivo, abrirá o arquivo Lista_tarefa.txt para escrever
    // O loop itera sobre a lista lt_categoria e escreve as tarefas dentro dela no arquivo
    FILE *f = fopen("Lista_tarefas.txt", "w");
    fprintf(f, "Tarefa           Prioridade               Categoria               estado         descricao\n"); // Digita a primeira linha do arquivo

    for (int i = 0; i < lt_categoria_qtnd; i++) {
      fprintf(f, "Tarefa %d:            %d                    %s                 %s           %s\n", i, lt_categoria[i].prioridade, lt_categoria[i].categoria, lt_categoria[i].estado, lt_categoria[i].descricao);
    }
    fclose(f); // Fecha o arquivo

    if (lt_categoria_qtnd == 0) {
      printf("\t\tCategoria não existe\n");
    }
  }

}

void exportar_prioridade(lista_tarefa *lt) {

  int prioridade;
  int cont = 0;
  printf("\t\tPrioridade desejada: ");
  scanf("%d", &prioridade);
  
  if (prioridade < 0 || prioridade > 10) {
    // Valida a prioridade digitada pelo usuário
    printf("\tPrioridade inválida\n");
  }
  else {
    FILE *f = fopen("Lista_tarefas.txt", "w"); // Abre o arquivo para escrever
    fprintf(f, "Tarefa          Prioridade          Categoria          estado          descricao\n"); // Digita a primeira linha do arquivo
    for (int i = 0; i < lt->qtnd; i++) {
      // Loop itera sobre todas as tarefas do struct lista_tarefa e coloca no arquivo as tarefas com prioridade digitada pelo usuário
      if (lt->tarefa[i].prioridade == prioridade) {
        fprintf(f, "Tarefa %d:            %d                    %s                 %s           %s\n", i, lt->tarefa[i].prioridade, lt->tarefa[i].categoria, lt->tarefa[i].estado, lt->tarefa[i].descricao);
        cont += 1;
      }
    }
    fclose(f); // Fecha o arquivo
    if (cont == 0) {
      printf("\t\tPrioridade não registrada ainda.\n");
    }
  }
  
}

void exportar_categoria(lista_tarefa *lt) {

  char categoria[101];
  int cont = 0;
  printf("\t\tCategoria desejada: ");
  clean_buffer(); // Para que o scanf não registre o \n como input
  scanf("%[^\n]", categoria);
  
  FILE *f = fopen("Lista_tarefas.txt", "w");
  fprintf(f, "Tarefa          Prioridade          Categoria          estado          descricao\n"); // Digita a primeira linha do arquivo
  for (int i = 0; i < lt->qtnd; i++) {
    if (strcmp(lt->tarefa[i].categoria, categoria) == 0) {
      // Loop itera sobre todas as tarefas do struct lista_tarefa e coloca no arquivo as tarefas com categoria digitada pelo usuário
      fprintf(f, "Tarefa %d:            %d                    %s                 %s           %s\n", i, lt->tarefa[i].prioridade, lt->tarefa[i].categoria, lt->tarefa[i].estado, lt->tarefa[i].descricao);
      cont += 1;
    }
  }
  fclose(f); // Fecha o arquivo
  if (cont == 0) {
    printf("\t\tCategoria não registrada ainda.\n");
  }
  
}

void exportar_categoria_prioridade(lista_tarefa *lt) {

  filtro_categoria_prioridade(lt, 1); // Chama a função no modo de escrever txt
  
}

void menu_filtros(int *opcao) {

  // Exibe um menu de opções que o usuário pode filtrar as tarefas
  printf("\tEscolha um dos filtros abaixo:\n");
  printf("\t1. Filtrar por prioridade\n");
  printf("\t2. Filtrar por estado\n");
  printf("\t3. Filtrar por categoria\n");
  printf("\t4. Filtrar por categoria e prioridade\n");
  printf("\tOpção: ");
  scanf("%d", opcao);

}

void menu_exportar(int *opcao) {

  // Exibe um menu de opções que o usuário pode exportar as tarefas
  printf("\tEscolha a forma de exportar as tarefas:\n");
  printf("\t1. Exportar por prioridade\n");
  printf("\t2. Exportar por categoria\n");
  printf("\t3. Exportar por categoria e prioridade\n");
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

void clean_buffer() {

  int i;
  while ((i = getchar() != '\n' && i != EOF)); // Recebe o \n do ENTER de cada scanf para que o próximo scanf não recebe isso como input
  
}