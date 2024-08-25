#include "BufferEntrada.h"  // Inclui a definição da classe BufferEntrada e seus métodos.
#include <cstdio>           // Inclui funções para manipulação de arquivos.
#include <cstdlib>          // Inclui funções para controle de execução, como exit().

BufferEntrada::BufferEntrada(const char* nome_arquivo, size_t num_registros) 
    : posicao_atual(0), tamanho_buffer(num_registros), buffer_vazio(false) {
    // Construtor da classe BufferEntrada que inicializa um buffer de entrada para leitura de registros.
    // Recebe o nome do arquivo de entrada e o número de registros que o buffer deve conter.

    arquivo = fopen(nome_arquivo, "rb");  // Abre o arquivo em modo binário para leitura.
    if (!arquivo) {
        // Se o arquivo não for aberto corretamente, exibe uma mensagem de erro e encerra o programa.
        perror("Erro ao abrir arquivo de entrada");
        exit(1);
    }

    buffer.resize(num_registros);  // Redimensiona o vetor buffer para conter num_registros elementos.
    carregar_buffer();             // Carrega os primeiros registros do arquivo no buffer.
}

BufferEntrada::~BufferEntrada() {
    // Destrutor da classe, que fecha o arquivo se ele ainda estiver aberto.
    if (arquivo) {
        fclose(arquivo);  // Fecha o arquivo de entrada.
    }
}

void BufferEntrada::carregar_buffer() {
    // Método responsável por carregar o buffer com registros do arquivo.
    size_t lidos = fread(buffer.data(), sizeof(ITEM_VENDA), tamanho_buffer, arquivo);
    // Lê num_registros registros do arquivo e os armazena no buffer.

    posicao_atual = 0;  // Reseta a posição atual para o início do buffer.
    
    if (lidos < tamanho_buffer) {
        // Se o número de registros lidos for menor que o tamanho do buffer, significa que
        // o arquivo tem menos registros disponíveis do que o tamanho do buffer, ou o arquivo acabou.
        buffer.resize(lidos);  // Redimensiona o buffer para o número de registros realmente lidos.
        buffer_vazio = true;   // Define que o buffer está vazio após consumir os registros lidos.
    }
}

ITEM_VENDA BufferEntrada::proximo() {
    // Retorna o próximo item no buffer sem consumir (avançar) a posição atual.
    return buffer[posicao_atual];
}

ITEM_VENDA BufferEntrada::consumir() {
    // Retorna o próximo item no buffer e avança a posição atual.
    ITEM_VENDA item = buffer[posicao_atual];  // Armazena o item atual.
    posicao_atual++;                          // Avança a posição atual no buffer.

    if (posicao_atual >= buffer.size()) {
        // Se a posição atual atingir ou ultrapassar o tamanho do buffer, carrega o próximo conjunto de registros.
        carregar_buffer();
    }

    return item;  // Retorna o item armazenado.
}

bool BufferEntrada::vazio() {
    // Verifica se o buffer está vazio.
    // O buffer é considerado vazio se todos os registros foram consumidos e não há mais registros para carregar.
    return buffer_vazio && posicao_atual >= buffer.size();
}