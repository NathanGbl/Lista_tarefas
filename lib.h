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

// gerencia_tarefa

void exibe_menu(int *opcao);

void menu_estado(int *opcao, int modo);

void cadastra_tarefa(lista_tarefa *lt, int *opcao);

void deleta_tarefa(lista_tarefa *lt, int tarefa);

void listar_tarefa(lista_tarefa *lt);

void exibe_menu2(int *tarefa, int *dado_alterado);

void alterar_tarefa(lista_tarefa *lt, int *opcao);

// filtros

void filtro_prioridade(lista_tarefa *lt);

void filtro_estado(lista_tarefa *lt, int *opcao);

void filtro_categoria(lista_tarefa *lt);

int compara_prioridade(const void *valor1, const void *valor2);

void filtro_categoria_prioridade(lista_tarefa *lt, int modo);

// exportar

void exportar_prioridade(lista_tarefa *lt);

void exportar_categoria(lista_tarefa *lt);

void exportar_categoria_prioridade(lista_tarefa *lt);

void menu_filtros(int *opcao);

void menu_exportar(int *opcao);

void le_arquivo(lista_tarefa  *lt);

void escreve_arquivo(lista_tarefa *lt);

void clean_buffer();