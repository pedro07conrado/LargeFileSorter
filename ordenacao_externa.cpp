#include <iostream>
#include <vector>
#include <algorithm>
#include "BufferEntrada.h"
#include "BufferSaida.h"
#include "big_file.h"

// Função para fazer a intercalação k-vias
void intercalar_k_vias(const std::vector<BufferEntrada*>& buffers_entrada, BufferSaida& buffer_saida) {
    std::vector<ITEM_VENDA> heap;

    // Inicializar o heap com o primeiro item de cada buffer de entrada
    for (auto buffer : buffers_entrada) {
        ITEM_VENDA item;
        if (buffer->ler(item)) {
            heap.push_back(item);
        }
    }

    // Função de comparação para o heap (menor elemento no topo)
    auto cmp = [](const ITEM_VENDA& a, const ITEM_VENDA& b) {
        return a.id > b.id;
    };

    // Transformar o vetor em um heap
    std::make_heap(heap.begin(), heap.end(), cmp);

    while (!heap.empty()) {
        // Obter o menor elemento do heap
        std::pop_heap(heap.begin(), heap.end(), cmp);
        ITEM_VENDA menor = heap.back();
        heap.pop_back();

        // Inserir o menor elemento no buffer de saída
        buffer_saida.inserir(menor);

        // Ler o próximo item do mesmo buffer de entrada e inserir no heap
        for (auto buffer : buffers_entrada) {
            if (!buffer->vazio() && buffer->ler(menor)) {
                heap.push_back(menor);
                std::push_heap(heap.begin(), heap.end(), cmp);
                break;
            }
        }
    }

    // Despejar qualquer item restante no buffer de saída
    buffer_saida.despejar();
}

void ordenacao_externa(const char* arquivo_entrada, size_t tamanho_buffer, int num_vias, const char* arquivo_saida) {
    std::vector<BufferEntrada*> buffers_entrada;
    for (int i = 0; i < num_vias; ++i) {
        buffers_entrada.push_back(new BufferEntrada(arquivo_entrada, tamanho_buffer));
    }

    BufferSaida buffer_saida(arquivo_saida, tamanho_buffer);

    // Lógica de ordenação externa
    intercalar_k_vias(buffers_entrada, buffer_saida);

    for (auto buffer : buffers_entrada) {
        delete buffer;
    }
}

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " <ARQUIVO_ENTRADA> <B> <S> <ARQUIVO_SAIDA>" << std::endl;
        return 1;
    }

    const char* arquivo_entrada = argv[1];
    size_t tamanho_buffer = static_cast<size_t>(std::stoull(argv[2]));
    int num_vias = std::stoi(argv[3]);
    const char* arquivo_saida = argv[4];

    ordenacao_externa(arquivo_entrada, tamanho_buffer, num_vias, arquivo_saida);

    return 0;
}