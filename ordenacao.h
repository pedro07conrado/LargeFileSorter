#pragma once

#include <cstdio>    // Para funções como printf, etc.
#include <cstdlib>   // Para funções como malloc, free, etc.
#include <cstring>   // Para funções como strcpy, strcmp, etc.
#include <cstdbool>  // Para o tipo bool

#include "big_file.h"
#include "Buffer.h"

/**************************************
* PROTÓTIPOS
**************************************/

void Trocar(ITEM_VENDA* item_venda, int maior, int i);
int Partition(ITEM_VENDA* item_venda, int inicio, int fim);
void QuickSort(ITEM_VENDA* item_venda, int inicio, int fim);

void Merge_K_Vias(Buffer** vetor_buffers, Buffer* buffer_saida, int quant_reg_buffer_saida, const char* nome_arq_saida, int quant_reg_total);