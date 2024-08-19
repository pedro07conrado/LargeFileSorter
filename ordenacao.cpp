#include "ordenacao.h"
#include <climits>  // Para INT_MAX

/**************
* IMPLEMENTAÇÃO
**************/

//--------------- FUNÇÃO DE TROCA ----------------------------------------
void Trocar(ITEM_VENDA* vetor_itens, int i, int j) {
    ITEM_VENDA aux = vetor_itens[i];
    vetor_itens[i] = vetor_itens[j];
    vetor_itens[j] = aux;
}

//--------------- FUNÇÃO PARTITION ---------------------------------------
int Partition(ITEM_VENDA* vetor_itens, int inicio, int fim) {
    int x = vetor_itens[fim].id;
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++) {
        if (vetor_itens[j].id <= x) {
            i++;
            Trocar(vetor_itens, i, j);
        }
    }

    Trocar(vetor_itens, i + 1, fim);
    return i + 1;
}

//--------------- FUNÇÃO QUICKSORT ----------------------------------------
void QuickSort(ITEM_VENDA* vetor_itens, int inicio, int fim) {
    if (inicio < fim) {
        int q = Partition(vetor_itens, inicio, fim);
        QuickSort(vetor_itens, inicio, q - 1);
        QuickSort(vetor_itens, q + 1, fim);
    }
}

//--------------- FUNÇÃO DE MENOR VALOR ----------------------------------------
void Menor_Valor(Buffer** vetor_buffers, int* id_menor, int* indice_menor) {
    int id = INT_MAX;
    int indice = -1; // Inicializado para -1 para indicar que nenhum valor foi encontrado.

    for (int i = 0; i < vetor_buffers[0]->quant_buffers; i++) {
        if (vetor_buffers[i]->quant_registros_buffer == 0) {
            continue;
        }

        if (vetor_buffers[i]->itens[0].id < id) {
            indice = i;
            id = vetor_buffers[i]->itens[0].id;
        }
    }

    *id_menor = id;
    *indice_menor = indice;
}

//--------------- FUNÇÃO MERGE EM K VIAS ------------------------------------
void Merge_K_Vias(Buffer** vetor_buffers, Buffer* buffer_saida, int quant_reg_buffer_saida, const char* nome_arq_saida, int quant_reg_total) {
    if (vetor_buffers == nullptr || buffer_saida == nullptr) return;

    for (int i = 1; i <= quant_reg_total; i++) {

        // Encontrar o menor valor do primeiro item dos buffers
        int id_menor, indice_menor;
        Menor_Valor(vetor_buffers, &id_menor, &indice_menor);
        if (indice_menor == -1) break; // Se nenhum valor foi encontrado, sai do loop.

        // Consumir o menor valor do buffer
        ITEM_VENDA item_menor = BE_Consumir(vetor_buffers[indice_menor]);

        // Adicionar o menor valor no buffer de saída
        BS_Inserir(buffer_saida, item_menor);

        // Despejar o buffer de saída se estiver cheio ou se os buffers de entrada estiverem vazios
        if (buffer_saida->quant_registros_buffer == buffer_saida->quant_max_registros_buffer || BE_VetorVazio(vetor_buffers)) {
            BS_Despejar(buffer_saida);
        }
    }
}