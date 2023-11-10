#include <stdio.h>

typedef struct {
  char descricao[301];

  char categoria[101];

  int prioridade;

  char estado[20];
} tarefa; // criação do struct tarefa com a descricao, categoria e prioridade

typedef struct {
  tarefa tarefa[100];
  int qtnd;
} lista_tarefa; // criação do struct lista_tarefa com o tarefa[100], um array de struct, e o inteiro que indica a quantidade de tarefas dentro do tarefa[100]

void exibe_menu(int *opcao);

void menu_estado(int *opcao, int modo);

void cadastra_tarefa(lista_tarefa *lt, int *opcao);

void exportar_prioridade(lista_tarefa *lt);

void exportar_categoria(lista_tarefa *lt);

void exportar_prioridade_categoria(lista_tarefa *lt);

void le_arquivo(lista_tarefa  *lt);

void escreve_arquivo(lista_tarefa *lt);