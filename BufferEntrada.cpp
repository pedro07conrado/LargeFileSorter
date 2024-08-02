#include "BufferEntrada.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

BufferEntrada::BufferEntrada(const char* nome_arquivo, size_t tamanho_buffer)
    : tamanho_buffer(tamanho_buffer), pos_atual(0) {
    arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de entrada");
        exit(EXIT_FAILURE);
    }
    buffer = new ITEM_VENDA[tamanho_buffer];
    // Carrega os primeiros dados
    fread(buffer, sizeof(ITEM_VENDA), tamanho_buffer, arquivo);
}

BufferEntrada::~BufferEntrada() {
    if (arquivo) {
        fclose(arquivo);
    }
    delete[] buffer;
}

bool BufferEntrada::ler(ITEM_VENDA& item) {
    if (pos_atual >= tamanho_buffer) {
        size_t lidos = fread(buffer, sizeof(ITEM_VENDA), tamanho_buffer, arquivo);
        if (lidos == 0) {
            return false;
        }
        pos_atual = 0;
        tamanho_buffer = lidos;
    }
    item = buffer[pos_atual++];
    return true;
}

bool BufferEntrada::vazio() const {
    return pos_atual >= tamanho_buffer && feof(arquivo);
}