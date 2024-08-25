#include "particao.h"
#include "big_file.h"
#include "quickSort.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <inttypes.h>
#include <iostream>

using namespace std;

/**
 * Função para criar múltiplas partições de um arquivo grande.
 * Cada partição é uma divisão do arquivo original, onde os dados são lidos, ordenados e salvos em arquivos separados.
 * 
 * @param arquivo O nome do arquivo original que será particionado.
 * @param qtdParticoes O número de partições que serão criadas a partir do arquivo original.
 * @return Um vetor de strings contendo os nomes dos arquivos de partição criados.
 */
char **criarParticao(char *arquivo, int qtdParticoes) {
  // Alocando uma array de ponteiros para strings, onde cada string será o nome de uma partição criada.
  char **nomes = (char**)calloc(qtdParticoes, sizeof(char*));
  
  // Abre o arquivo original em modo binário.
  FILE *arq = fopen(arquivo, "rb");
  
  // Calcula a quantidade de dígitos necessários para representar o número de partições.
  // Exemplo: se o número de partições for 100, precisaremos de 3 dígitos.
  int qtdDigitosVersao = 0;
  int auxCount = qtdParticoes;
  while(auxCount > 1) {
    qtdDigitosVersao++;
    auxCount /= 10;
  }

  // Calcula o tamanho do arquivo original.
  // 'ftell' move o cursor para o final do arquivo para obter o tamanho total em bytes.
  fseek(arq, 0, SEEK_END);
  int resto = ftell(arq);  // Guarda o tamanho total do arquivo.
  
  // Calcula o tamanho de cada partição dividindo o tamanho do arquivo pelo número de partições.
  // O tamanho de cada partição é ajustado conforme o tamanho de `ITEM_VENDA`.
  unsigned long int tamanho = ftell(arq)/(sizeof(ITEM_VENDA)*qtdParticoes);
  fseek(arq, 0, SEEK_SET);  // Retorna o cursor para o início do arquivo.
  
  // Loop para criar cada uma das partições.
  for(int i = 0; i < qtdParticoes; i++) {
    // Inicializa o nome do arquivo de partição. Cada partição terá um nome único, como "particao/p1.dat".
    char versao[qtdDigitosVersao];  // Armazena o número da partição.
    char extensao[] = ".dat";  // Extensão padrão para os arquivos de partição.
    
    // Formata o número da partição como uma string.
    sprintf(versao, "%d", i+1);
    
    // Calcula o tamanho total do nome do arquivo, incluindo a pasta, número e extensão.
    int x = strlen(versao) + strlen(extensao) + 11;
    char *nome_arquivo = (char*)calloc(x, sizeof(char));  // Aloca memória para o nome do arquivo.
    
    // Monta o nome do arquivo de partição.
    strcat(nome_arquivo, "particao/p");
    strcat(nome_arquivo, versao);
    strcat(nome_arquivo, extensao);
    
    // Salva o nome do arquivo de partição na lista de nomes.
    nomes[i] = (char*)malloc(strlen(nome_arquivo) + 1);
    memcpy(nomes[i], nome_arquivo, strlen(nome_arquivo) + 1);

    // Cria o arquivo de partição e lê uma parte do arquivo original correspondente ao tamanho da partição.
    FILE *destino = fopen(nome_arquivo, "wb");  // Abre o arquivo de destino para escrita em modo binário.
    
    // Aloca espaço para os registros da partição, que serão lidos do arquivo original.
    ITEM_VENDA *aux = (ITEM_VENDA*)calloc(tamanho, sizeof(ITEM_VENDA));
    
    // Atualiza o valor restante do arquivo. 
    resto -= tamanho;
    
    // Calcula a quantidade de registros a serem lidos. Se o resto for menor que zero, ajusta o tamanho.
    int tam = (resto < 0) ? resto + tamanho : tamanho;
    
    // Lê os registros do arquivo original.
    fread(aux, sizeof(ITEM_VENDA), tam, arq);
    
    // Ordena os registros da partição utilizando QuickSort.
    quickSort(aux, 0, tam-1);
    
    // Escreve os registros ordenados no arquivo de partição.
    fwrite(aux, sizeof(ITEM_VENDA), tam, destino);
    
    // Fecha o arquivo de partição e libera a memória alocada.
    fclose(destino);
    free(aux);
    free(nome_arquivo);

    // Se o valor restante do arquivo for negativo, significa que todas as partições já foram criadas.
    if(resto < 0) break;
  }

  // Fecha o arquivo original e retorna a lista com os nomes das partições criadas.
  fclose(arq);
  return nomes;
}

/**
 * Função de teste para verificar a ordenação de uma partição.
 * Lê o arquivo de partição e exibe o ID dos itens contidos nele.
 * 
 * @param arquivo O nome do arquivo de partição a ser verificado.
 */
void teste_ordenacao_particao (char *arquivo) {
  unsigned long int i;
  ITEM_VENDA *itens;

  // Abre o arquivo de partição em modo binário para leitura.
  FILE *arq = fopen(arquivo, "rb");

  // Move o cursor para o final do arquivo para calcular o tamanho total.
  fseek(arq, 0, SEEK_END);
  unsigned long int tamanho = ftell(arq)/1024;  // Obtém o tamanho em kilobytes.
  
  // Retorna o cursor ao início do arquivo.
  fseek(arq, 0, SEEK_SET);

  // Aloca espaço na memória para armazenar os itens que serão lidos.
  itens = (ITEM_VENDA*)calloc(tamanho, sizeof(ITEM_VENDA));

  // Lê os itens do arquivo de partição.
  fread(itens, sizeof(ITEM_VENDA), tamanho, arq);

  // Exibe os IDs dos itens lidos.
  for (i = 0; i < tamanho; i++) {
    cout << "ID: " << itens[i].id << endl;
  }

  // Fecha o arquivo e libera a memória alocada.
  fclose(arq);
}
