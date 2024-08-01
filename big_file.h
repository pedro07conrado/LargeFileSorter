#ifndef BIG_FILE_H
#define BIG_FILE_H

#include "ITEM_VENDA.h"  // Inclui o cabeçalho que define ITEM_VENDA
#include <cstdio>

class BigFile {
public:
    BigFile(const char* nome_arquivo);
    ~BigFile();

    void adicionarItem(const ITEM_VENDA& item);
    void lerItem(ITEM_VENDA& item);
    void limpar();

private:
    FILE* arquivo;
};

#endif // BIG_FILE_H