#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <string>
#include <vector>

#include "big_file.h"

/**
DADOS
**/

enum Status {
    ATIVO,
    INATIVO
};

struct Buffer {
    int quant_registros_buffer;
    int quant_max_registros_buffer;
    int quant_buffers;
    int bloco;
    Status status_buffer;
    Status status_arquivo;
    std::string arq_nome;
    ITEM_VENDA* itens;
};

/**
PROTÓTIPOS
**/

// PROTOTIPOS DO BUFFER ENTRADA
std::vector<Buffer> BE_CriarVetor(int quant_arq_temp, int quant_reg_buffer_entrada);
Buffer BE_Criar(const std::string& nome_arq_temp, int quant_reg_buffer_entrada, int quant_arq_temp);

void BE_Reencher(Buffer* buffer);
void BE_Proximo(Buffer* buffer);
ITEM_VENDA BE_Consumir(Buffer* buffer);
void BE_Destruir(std::vector<Buffer>& vetor_buffers);

bool BE_Vazio(Buffer buffer_entrada);
bool BE_VetorVazio(const std::vector<Buffer>& buffer_entrada);

// PROTOTIPOS DO BUFFER SAIDA
Buffer BS_Criar(const std::string& nome_arq_saida, int quant_reg_buffer_saida);
void BS_Inserir(Buffer* buffer_saida, ITEM_VENDA menor_item);
void BS_Despejar(Buffer* buffer_saida);
void BS_Destruir(Buffer* buffer_saida);