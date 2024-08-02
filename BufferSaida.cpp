#include "BufferSaida.h"
#include <cstdio>
#include <cstdlib>
#include <cstring> 

BufferSaida::BufferSaida(const char* nome_arquivo, size_t tamanho_buffer)
    : tamanho_buffer(tamanho_buffer), pos_atual(0) {
    arquivo = fopen(nome_arquivo, "wb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }
    buffer = new ITEM_VENDA[tamanho_buffer];
}

BufferSaida::~BufferSaida() {
    despejar();
    if (arquivo) {
        fclose(arquivo);
    }
    delete[] buffer;
}

void BufferSaida::inserir(const ITEM_VENDA& item) {
    if (pos_atual >= tamanho_buffer) {
        despejar();
    }
    buffer[pos_atual++] = item;
}

void BufferSaida::despejar() {
    if (pos_atual > 0) {
        fwrite(buffer, sizeof(ITEM_VENDA), pos_atual, arquivo);
        pos_atual = 0;
    }
}