#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "big_file.h"


static inline void trocar(ITEM_VENDA* x, ITEM_VENDA* y) {
    ITEM_VENDA aux = *x;
    *x = *y;
    *y = aux;
}

static void embaralhar(ITEM_VENDA* v, int ini, int fim) {
    for (int i = fim - 1; i > ini; i--) {
        int j = rand() % (i + 1);
        j = j <= ini ? ini + 1 : j;
        trocar(&v[i], &v[j]);
    }
}

void gerar_array_iv(const std::string& arquivo_saida, unsigned int n_registros, int seed) {
    ITEM_VENDA* iv = new ITEM_VENDA[n_registros];
    std::ofstream saida(arquivo_saida, std::ios::binary);
    time_t t = time(nullptr);

    srand(seed);

    for (uint32_t i = 0; i < n_registros; i++) {
        iv[i].id = i;
        iv[i].id_venda = i + (rand() % 2);
        iv[i].desconto = (rand() % 10) / 100.0f;
        iv[i].data = t + ((-1 * (rand() % 30)) * 86400);
        iv[i].obs[0] = '\0';
    }

    embaralhar(iv, 0, n_registros);

    if (!saida) {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
        exit(1);
    }

    saida.write(reinterpret_cast<char*>(iv), sizeof(ITEM_VENDA) * n_registros);
    saida.close();

    delete[] iv;
}