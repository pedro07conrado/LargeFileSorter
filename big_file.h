#pragma once

#include <cstdint>
#include <string>

struct ITEM_VENDA {
    uint32_t id;
    uint32_t id_venda;
    uint32_t data;
    float desconto;
    char obs[1008];
};

void gerar_array_iv(const std::string& arquivo_saida, unsigned int n_registros, int seed);