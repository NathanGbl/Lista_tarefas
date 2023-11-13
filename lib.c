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

// gerencia_tarefa

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

  printf("\tDigite o número da tarefa para deletá-la: ");
  scanf("%d", &tarefa);
  
  if (tarefa < 0 || tarefa > lt->qtnd) {
    printf("\tTarefa não existe.\n");
  }
  else {
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
  
}

void exibe_menu2(int *tarefa, int *dado_alterado) {

  // Exibe as opções de alteração de tarefa e recebe a tarefa que precisa ser alterada e o dado a ser alterado
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

void alterar_tarefa(lista_tarefa *lt, int *opcao) {

  int tarefa;
  int dado_alterado;
  int prioridade;
  char estado[20];
  exibe_menu2(&tarefa, &dado_alterado);

  if (dado_alterado == 1) {
    printf("\tDigite a nova descrição: ");
    clean_buffer(); // Para que o scanf não registre o \n como input
    scanf("%[^\n]", lt->tarefa[tarefa].descricao); // Altera a descricao para a nova descricao digitada pelo usuário
    printf("\n\tMudança realizada com sucesso!\n");
  }
  else if (dado_alterado == 2) {
    printf("\tDigite a nova categoria: ");
    clean_buffer();
    scanf("%[^\n]", lt->tarefa[tarefa].categoria); // Altera a categoria para a nova categoria digitada pelo usuário
    printf("\n\tMudança realizada com sucesso!\n");
  }
  else if (dado_alterado == 3) {
    printf("\tDigite a nova prioridade: ");
    scanf("%d", &prioridade);
    if (prioridade >= 0 && prioridade <= 10) {
      // verifica se a prioridade está no intervalo correto
      lt->tarefa[tarefa].prioridade = prioridade; // Altera a prioridade para a nova prioridade digitada pelo usuário
      printf("\n\tMudança realizada com sucesso!\n");
    }
    else {
      printf("\n\tDados inválidos. Mudança cancelada.\n"); // Tratamento de erro
    }
  }
  else if (dado_alterado == 4) {
    menu_estado(opcao, 2);
    switch(*opcao) {
      // De acordo com a opcao digitada pelo usuário, altera o estado da tarefa
      case 1:
        strcpy(lt->tarefa[tarefa].estado, "Completo");
        break;
      case 2:
        strcpy(lt->tarefa[tarefa].estado, "Em andamento");
        break;
      case 3:
        strcpy(lt->tarefa[tarefa].estado, "Não iniciado");
        break;
      default:
        printf("\n\tOpção inválida\n"); // Tratamento de erro
    }
    printf("\n\tMudança realizada com sucesso!\n");
  }
  
}
  

// filtros

void filtro_prioridade(lista_tarefa *lt, int modo) {

  tarefa lt_prioridade[100];
  int lt_prioridade_qtnd = 0;
  int prioridade;
  printf("\t\tDigite a prioridade desejada: ");
  scanf("%d", &prioridade);

  if (prioridade < 0 || prioridade > 10) {
    printf("\t\tPrioridade inválida.\n");
  }
  else {
    for (int i = 0; i < lt->qtnd; i++) {
      // Loop que itera sobre todas as tarefas do struct lista_tarefa. Caso a tarefa tenha a prioridade digitada pelo usuário, adiciona no array lt_prioridade.
      if (lt->tarefa[i].prioridade == prioridade) {
        strcpy(lt_prioridade[lt_prioridade_qtnd].descricao, lt->tarefa[i].descricao);
        strcpy(lt_prioridade[lt_prioridade_qtnd].categoria, lt->tarefa[i].categoria);
        lt_prioridade[lt_prioridade_qtnd].prioridade = lt->tarefa[i].prioridade;
        strcpy(lt_prioridade[lt_prioridade_qtnd].estado, lt->tarefa[i].estado);
        lt_prioridade_qtnd += 1; // Aumenta a quantidade para apontar para a última tarefa
      }
    }
    if (lt_prioridade_qtnd == 0) {
      printf("\t\tNão há tarefas com a prioridade %d.\n", prioridade);
    }
    if (modo == 0) {
      // Se for para filtrar apenas, imprime
      for (int i = 0; i < lt_prioridade_qtnd; i++) {
        // Loop que itera sobre todas as tarefas do struct lista_tarefa. Caso a tarefa tenha a prioridade digitada pelo usuário, a exibe.
        printf("\t\tTarefa %d\n", i);
        printf("\t\t\tDescrição: %s\n", lt_prioridade[i].descricao);
        printf("\t\t\tCategoria: %s\n", lt_prioridade[i].categoria);
        printf("\t\t\tPrioridade: %d\n", lt_prioridade[i].prioridade);
        printf("\t\t\tEstado: %s\n", lt_prioridade[i].estado);
      }
    }
    else if (modo == 1) {
      // Se for para escrever no arquivo, abrirá o arquivo Lista_tarefa.txt para escrever
      // O loop itera sobre a lista lt_prioridade e escreve as tarefas dentro dela no arquivo
      FILE *f = fopen("Lista_tarefas.txt", "w");
      fprintf(f, "Tarefa           Prioridade               Categoria               estado         descricao\n"); // Digita a primeira linha do arquivo

      for (int i = 0; i < lt_prioridade_qtnd; i++) {
        fprintf(f, "Tarefa %d:            %d                    %s                 %s           %s\n", i, lt_prioridade[i].prioridade, lt_prioridade[i].categoria, lt_prioridade[i].estado, lt_prioridade[i].descricao);
      }
      fclose(f); // Fecha o arquivo
    }
  }
  
}

void filtro_estado(lista_tarefa *lt, int *opcao) {

  int cont = 0;
  menu_estado(opcao, 1);
  // Em cada if muda apenas a comparação entre os estados
  // De acordo com a opcao, o loop dentro dos if/else if verifica se a tarefa tem o estado escolhido e exibe em caso afirmativo
  if (*opcao == 1) {
    for (int i = 0; i < lt->qtnd; i++) {
      if (strcmp(lt->tarefa[i].estado, "Completo") == 0) {
        printf("\t\tTarefa %d\n", i);
        printf("\t\t\tDescrição: %s\n", lt->tarefa[i].descricao);
        printf("\t\t\tCategoria: %s\n", lt->tarefa[i].categoria);
        printf("\t\t\tPrioridade: %d\n", lt->tarefa[i].prioridade);
        printf("\t\t\tEstado: %s\n", lt->tarefa[i].estado);
        cont += 1;
      }
    }
    if (cont == 0) {
      printf("\t\tNão existe tarefa registrada com esse estado.\n");
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
        cont += 1;
      }
    }
    if (cont == 0) {
      printf("\t\tNão existe tarefa registrada com esse estado.\n");
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
        cont += 1;
      }
    }
    if (cont == 0) {
      printf("\t\tNão existe tarefa registrada com esse estado.\n");
    }
  }
  else {
    printf("\t\t\tOpção inválida\n"); // Tratamento de erro
  }
  
}

void filtro_categoria(lista_tarefa *lt, int modo) {

  tarefa lt_categoria[100];
  int lt_categoria_qtnd = 0;
  char categoria[101];
  int prioridade;
  printf("\t\tDigite a categoria desejada: ");
  clean_buffer(); // Para que o scanf não registre o \n como input
  scanf("%[^\n]", categoria);

  for (int i = 0; i < lt->qtnd; i++) {
    // Loop que itera sobre todas as tarefas do struct lista_tarefa
    // Se a categoria por a digita pelo usuário, adiciona-a no array lt_categoria
    if (strcmp(lt->tarefa[i].categoria, categoria) == 0) {
      strcpy(lt_categoria[lt_categoria_qtnd].descricao, lt->tarefa[i].descricao);
      strcpy(lt_categoria[lt_categoria_qtnd].categoria, lt->tarefa[i].categoria);
      lt_categoria[lt_categoria_qtnd].prioridade = lt->tarefa[i].prioridade;
      strcpy(lt_categoria[lt_categoria_qtnd].estado, lt->tarefa[i].estado);
      lt_categoria_qtnd += 1; // Aumenta a quantidade para apontar para a última tarefa
    }
  }
  
  qsort(lt_categoria, lt_categoria_qtnd, sizeof(tarefa), compara_prioridade); // Ordena de forma decrescente o array lt_categoria com base na prioridade
  
  if (lt_categoria_qtnd == 0) {
    printf("\t\tCategoria não existe\n");
  }

  if (modo == 0) {
    // Se for para filtrar, imprime as tarefas dentro de lt_categoria
    for (int i = 0; i < lt_categoria_qtnd; i++) {
      printf("\t\tTarefa %d\n", i);
      printf("\t\t\tDescrição: %s\n", lt_categoria[i].descricao);
      printf("\t\t\tCategoria: %s\n", lt_categoria[i].categoria);
      printf("\t\t\tPrioridade: %d\n", lt_categoria[i].prioridade);
      printf("\t\t\tEstado: %s\n", lt_categoria[i].estado);
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
  int prioridade;

  printf("\t\tCategoria desejada: ");
  clean_buffer(); // Para que o scanf não registre o \n como input
  scanf("%[^\n]", categoria);

  printf("\n\t\tPrioridade desejada: ");
  scanf("%d", &prioridade);

  if (prioridade < 0 || prioridade > 10) {
    printf("\t\tPrioridade inválida\n");
  }
  else {
    for (int i = 0; i < lt->qtnd; i++) {
      // Loop que itera sobre todas as tarefas do struct lista_tarefa
      // Caso a categoria for igual a digitada pelo usuário, adiciona-a na lista lt_categoria
      if (strcmp(lt->tarefa[i].categoria, categoria) == 0 && lt->tarefa[i].prioridade == prioridade) {
      strcpy(lt_categoria[lt_categoria_qtnd].descricao, lt->tarefa[i].descricao);
      strcpy(lt_categoria[lt_categoria_qtnd].categoria, lt->tarefa[i].categoria);
      lt_categoria[lt_categoria_qtnd].prioridade = lt->tarefa[i].prioridade;
      strcpy(lt_categoria[lt_categoria_qtnd].estado, lt->tarefa[i].estado);
      lt_categoria_qtnd += 1; // Aumenta a quantidade para apontar para a última tarefa
      }
    }
    if (lt_categoria_qtnd == 0) {
      printf("\t\tCategoria não existe\n");
    }
    if (modo == 0) {
      // Se for apenas para imprimir, o loop itera sobre a lista lt_categoria e imprime as tarefas dentro dela
      for (int i = 0; i < lt_categoria_qtnd; i++) {
        printf("\t\tTarefa %d\n", i);
        printf("\t\t\tDescrição: %s\n", lt_categoria[i].descricao);
        printf("\t\t\tCategoria: %s\n", lt_categoria[i].categoria);
        printf("\t\t\tPrioridade: %d\n", lt_categoria[i].prioridade);
        printf("\t\t\tEstado: %s\n", lt_categoria[i].estado);
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
    }
  }

}

// exportar

void exportar_prioridade(lista_tarefa *lt) {

  filtro_prioridade(lt, 1); // Chama a função no modo de escrever txt
  
}

void exportar_categoria(lista_tarefa *lt) {

  filtro_categoria(lt, 1); // Chama a função no modo de escrever txt
  
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