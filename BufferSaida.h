#ifndef BUFFERSAIDA_H
#define BUFFERSAIDA_H

#include <cstdio>  
#include <cstddef> 
#include "ITEM_VENDA.h"
#include <cstring> 

class BufferSaida {
public:
    BufferSaida(const char* nome_arquivo, size_t tamanho_buffer);
    ~BufferSaida();
    void inserir(const ITEM_VENDA& item);
    void despejar();

private:
    FILE* arquivo;
    ITEM_VENDA* buffer;
    size_t tamanho_buffer;
    size_t pos_atual;
};

#endif // BUFFERSAIDA_H