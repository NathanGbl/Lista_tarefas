#include <stdio.h>
#include "lib.h"

int main() {
  // Projeto feito por: Nathan Gabriel da Fonseca Leite RA: 221230287
  int opcao;
  int index_tarefa;
  lista_tarefa lt;
  lt.qtnd = 0;

  le_arquivo(&lt); // Atualiza o lt.qtnd e as tarefas dentro do tarefa[100]

  do {
    exibe_menu(&opcao);
    switch(opcao) {
      case 1:
        cadastra_tarefa(&lt, &opcao);
        break;
      default:
        printf("Opção inválida.\n");
    }
  } while(opcao != 0);

  escreve_arquivo(&lt); // Adiciona as mudanças no arquivo
  
  return 0;
}