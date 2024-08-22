#pragma once

#include "big_file.h"
#include <cstdio>
#include <vector>

class BufferEntrada {
public:
    BufferEntrada(const char* nome_arquivo, size_t num_registros);
    ~BufferEntrada();
    
    ITEM_VENDA proximo();
    ITEM_VENDA consumir();
    bool vazio();

private:
    FILE* arquivo;
    std::vector<ITEM_VENDA> buffer;
    size_t posicao_atual;
    size_t tamanho_buffer;
    bool buffer_vazio;

    void carregar_buffer();
};
