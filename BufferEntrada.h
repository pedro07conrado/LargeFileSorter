#ifndef BUFFERENTRADA_H
#define BUFFERENTRADA_H

#include <cstdio>
#include <cstddef> 
#include "ITEM_VENDA.h"
#include <cstring>

class BufferEntrada {
public:
    BufferEntrada(const char* nome_arquivo, size_t tamanho_buffer);
    ~BufferEntrada();
    bool ler(ITEM_VENDA& item);
    bool vazio() const;

private:
    FILE* arquivo;
    ITEM_VENDA* buffer;
    size_t tamanho_buffer;
    size_t pos_atual;
};

#endif // BUFFERENTRADA_H