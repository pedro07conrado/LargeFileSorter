#ifndef ITEM_VENDA_H
#define ITEM_VENDA_H

#include <cstdint>  

struct ITEM_VENDA {
    uint32_t id;
    uint32_t id_venda;
    uint32_t data;
    float desconto;
    char desc[1008];
};

#endif 