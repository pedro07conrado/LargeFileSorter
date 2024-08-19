#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "arquivo.h"
#include "ordenacao.h"

/**************************************
* IMPLEMENTAÇÃO
**************************************/

//--------------- FUNÇÃO DIVIDIR ARQUIVO EM ARQUIVOS TEMPORÁRIOS -------------
void Arquivo_Dividir(const std::string& nome_arq_entrada, int quant_arq_temp, int quant_reg_total) {
    int quant_reg_arqTemp = std::ceil(static_cast<double>(quant_reg_total) / quant_arq_temp);

    ITEM_VENDA* vetor_itens = new ITEM_VENDA[quant_reg_arqTemp];
    std::ifstream arq_entrada(nome_arq_entrada, std::ios::binary);

    for (int i = 0; i < quant_arq_temp; i++) {
        std::string nome_arq_temp = "P" + std::to_string(i) + ".dat";
        std::ofstream arq_temp(nome_arq_temp, std::ios::binary);

        arq_entrada.seekg(i * quant_reg_arqTemp * sizeof(ITEM_VENDA), std::ios::beg);
        int inicio = arq_entrada.tellg();
        arq_entrada.seekg(0, std::ios::end);
        int fim = arq_entrada.tellg();
        int tam_restante_arq_entrada = fim - inicio;
        arq_entrada.seekg(i * quant_reg_arqTemp * sizeof(ITEM_VENDA), std::ios::beg);

        int quant_registros_para_serem_lidos = tam_restante_arq_entrada / 1024;

        if (quant_registros_para_serem_lidos > quant_reg_arqTemp) {
            arq_entrada.read(reinterpret_cast<char*>(vetor_itens), quant_reg_arqTemp * sizeof(ITEM_VENDA));
            QuickSort(vetor_itens, 0, quant_reg_arqTemp - 1);
            arq_temp.write(reinterpret_cast<char*>(vetor_itens), quant_reg_arqTemp * sizeof(ITEM_VENDA));
        } else {
            arq_entrada.read(reinterpret_cast<char*>(vetor_itens), quant_registros_para_serem_lidos * sizeof(ITEM_VENDA));
            QuickSort(vetor_itens, 0, quant_registros_para_serem_lidos - 1);
            arq_temp.write(reinterpret_cast<char*>(vetor_itens), quant_registros_para_serem_lidos * sizeof(ITEM_VENDA));
        }

        arq_temp.close();
    }
    arq_entrada.close();
    delete[] vetor_itens;
}

//--------------- FUNÇÃO REMOVER ARQUIVOS TEMPORÁRIOS -------------
void ArquivosTemporarios_Remover(int quant_arq_temp) {
    for (int i = 0; i < quant_arq_temp; i++) {
        std::string nome = "P" + std::to_string(i) + ".dat";
        std::remove(nome.c_str());
    }
}
