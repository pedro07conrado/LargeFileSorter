#include "BufferSaida.h"   // Inclui a definição da classe BufferSaida e seus métodos.
#include <cstdio>          // Inclui funções para manipulação de arquivos.
#include <cstdlib>         // Inclui funções para controle de execução, como exit().

BufferSaida::BufferSaida(const char* nome_arquivo, size_t num_registros)
    : tamanho_buffer(num_registros) {
    // Construtor da classe BufferSaida que inicializa um buffer de saída para escrita de registros.
    // Recebe o nome do arquivo de saída e o número de registros que o buffer deve conter.

    arquivo = fopen(nome_arquivo, "wb");  // Abre o arquivo em modo binário para escrita.
    if (!arquivo) {
        // Se o arquivo não for aberto corretamente, exibe uma mensagem de erro e encerra o programa.
        perror("Erro ao abrir arquivo de saída");
        exit(1);
    }
    buffer.reserve(num_registros);  // Reserva espaço para num_registros elementos no buffer.
}

BufferSaida::~BufferSaida() {
    // Destrutor da classe, que garante que o conteúdo do buffer seja escrito no arquivo
    // antes de fechar o arquivo.

    despejar();  // Despeja (escreve) qualquer dado restante no buffer para o arquivo.

    if (arquivo) {
        fclose(arquivo);  // Fecha o arquivo de saída.
    }
}

void BufferSaida::inserir(const ITEM_VENDA& item) {
    // Método que insere um item (registro) no buffer.
    buffer.push_back(item);  // Adiciona o item ao final do buffer.

    if (buffer.size() >= tamanho_buffer) {
        // Se o buffer atingir o tamanho máximo, escreve seu conteúdo no arquivo.
        escrever_buffer();
    }
}

void BufferSaida::despejar() {
    // Método que força a escrita de todos os dados do buffer para o arquivo.
    if (!buffer.empty()) {
        // Só escreve se o buffer não estiver vazio.
        escrever_buffer();
    }
}

void BufferSaida::escrever_buffer() {
    // Método que escreve o conteúdo do buffer no arquivo e depois limpa o buffer.
    fwrite(buffer.data(), sizeof(ITEM_VENDA), buffer.size(), arquivo);
    // Escreve todos os registros armazenados no buffer no arquivo de saída.

    buffer.clear();  // Limpa o buffer, removendo todos os elementos.
}