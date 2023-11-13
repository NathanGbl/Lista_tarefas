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
      case 2:
        deleta_tarefa(&lt, index_tarefa);
        break;
      case 3:
        listar_tarefa(&lt);
        break;
      case 4:
        alterar_tarefa(&lt, &opcao);
        break;
      case 5:
        menu_filtros(&opcao);
        switch(opcao) {
          case 1:
            filtro_prioridade(&lt, 0);
            break;
          case 2:
            filtro_estado(&lt, &opcao);
            break;
          case 3:
            filtro_categoria(&lt, 0);
            break;
          case 4:
            filtro_categoria_prioridade(&lt, 0);
            break;
          default:
            printf("\tOpção inválida.\n");
        }
        break;
      case 6:
        menu_exportar(&opcao);
        switch(opcao) {
          case 1:
            exportar_prioridade(&lt);
            break;
          case 2:
            exportar_categoria(&lt);
            break;
          case 3:
            exportar_categoria_prioridade(&lt);
            break;
          default:
            printf("\tOpção inválida.\n");
        }
        break;
      case 0:
        break;
      default:
        printf("Opção inválida.\n");
    }
  } while(opcao != 0);

  escreve_arquivo(&lt); // Adiciona as mudanças no arquivo
  
  return 0;
}