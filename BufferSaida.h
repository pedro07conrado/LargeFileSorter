#pragma once

#include "big_file.h"
#include <cstdio>
#include <vector>

class BufferSaida {
public:
    BufferSaida(const char* nome_arquivo, size_t num_registros);
    ~BufferSaida();

    void inserir(const ITEM_VENDA& item);
    void despejar();

private:
    FILE* arquivo;
    std::vector<ITEM_VENDA> buffer;
    size_t tamanho_buffer;

    void escrever_buffer();
};
