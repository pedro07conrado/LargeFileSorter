#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "BufferEntrada.h"
#include "BufferSaida.h"

using namespace std;

void intercalacao_k_vias(std::vector<BufferEntrada*>& buffers_entrada, BufferSaida& buffer_saida) {
    int qtd_buffers_vazios = 0;
    int qtd_buffer_entrada = buffers_entrada.size();

    while (qtd_buffers_vazios < qtd_buffer_entrada) {
        BufferEntrada* menor = nullptr;
        uint32_t auxmenor = UINT32_MAX;

        qtd_buffers_vazios = 0;
        for (int i = 0; i < qtd_buffer_entrada; i++) {
            if (!buffers_entrada[i]->vazio()) {
                if (auxmenor > buffers_entrada[i]->proximo().id) {
                    auxmenor = buffers_entrada[i]->proximo().id;
                    menor = buffers_entrada[i];
                }
            } else {
                qtd_buffers_vazios++;
            }
        }

        if (auxmenor != UINT32_MAX) {
            ITEM_VENDA menor_item = menor->consumir();
            buffer_saida.inserir(menor_item);
        }
    }
    buffer_saida.despejar();
}

void ordenacao_externa(const char* entrada, size_t bytes_registros, size_t bytes_buffer_saida, const char* nome_saida) {
    FILE* arq = fopen(entrada, "rb");
    fseek(arq, 0, SEEK_END);
    long int e = ftell(arq);
    fclose(arq);

    int k = ceil((float)e / bytes_registros);
    size_t qtd_registro_entrada = floor(((float)(bytes_registros - bytes_buffer_saida) / k) / sizeof(ITEM_VENDA));

    cout << "Tamanho do arquivo: " << (e / sizeof(ITEM_VENDA)) / sizeof(ITEM_VENDA) << " MB's" << endl;
    cout << "Particionaremos em " << k << " vezes, cada um com " 
         << (float)((e / sizeof(ITEM_VENDA)) / sizeof(ITEM_VENDA)) / k << " MB's" << endl;
    cout << "Teremos " << k << " buffers de entrada, cada um com " 
         << (float)(qtd_registro_entrada) / sizeof(ITEM_VENDA) << " MB's" << endl;
    cout << "Teremos 1 buffer de saida, com " 
         << (float)bytes_buffer_saida / (sizeof(ITEM_VENDA) * sizeof(ITEM_VENDA)) << " MB's" << endl;
    cout << "====================================" << endl;

    cout << "1 - Criando particoes, por favor aguarde..." << endl;
    vector<string> arquivos_temporarios;
    for (int i = 0; i < k; ++i) {
        vector<ITEM_VENDA> buffer(bytes_registros / sizeof(ITEM_VENDA));
        FILE* arquivo = fopen(entrada, "rb");
        fseek(arquivo, i * bytes_registros, SEEK_SET);
        size_t lidos = fread(buffer.data(), sizeof(ITEM_VENDA), buffer.size(), arquivo);
        fclose(arquivo);
        buffer.resize(lidos);

        sort(buffer.begin(), buffer.end(), [](const ITEM_VENDA& a, const ITEM_VENDA& b) {
            return a.id < b.id;
        });

        string nome_temp = "temp_" + to_string(i) + ".dat";
        FILE* temp = fopen(nome_temp.c_str(), "wb");
        fwrite(buffer.data(), sizeof(ITEM_VENDA), buffer.size(), temp);
        fclose(temp);
        arquivos_temporarios.push_back(nome_temp);
    }

    cout << "2 - Preenchendo buffers, por favor aguarde..." << endl;
    vector<BufferEntrada*> buffers_entrada;
    for (const auto& nome_temp : arquivos_temporarios) {
        buffers_entrada.push_back(new BufferEntrada(nome_temp.c_str(), qtd_registro_entrada));
    }
    BufferSaida buffer_saida(nome_saida, bytes_buffer_saida / sizeof(ITEM_VENDA));

    cout << "3 - Ordenando arquivos, por favor aguarde..." << endl;
    intercalacao_k_vias(buffers_entrada, buffer_saida);

    for (auto buffer : buffers_entrada) {
        delete buffer;
    }

    for (const auto& nome_temp : arquivos_temporarios) {
        remove(nome_temp.c_str());
    }

    cout << "\n====================================" << endl;
}

int isSaidaOrdenada(const char* nome_arquivo) {
    ITEM_VENDA item_anterior, item_atual;

    FILE* arq = fopen(nome_arquivo, "rb");

    if (arq == NULL) {
        cout << "ImpossÃ­vel abrir o arquivo!" << endl;
        return -1;
    }

    fread(&item_anterior, sizeof(ITEM_VENDA), 1, arq);

    while (fread(&item_atual, sizeof(ITEM_VENDA), 1, arq) == 1) {
        if (item_atual.id < item_anterior.id) {
            fclose(arq);
            return 0;
        }
        item_anterior = item_atual;
    }

    fclose(arq);
    return 1;
}