#include <cstdio>
#include "big_file.h"

void gerar_array_iv(const char* filename, int size, int value); // Function declaration

int main(int argc, char** argv) {
    printf("sizeof(ITEM_VENDA) = %ld\n", sizeof(ITEM_VENDA));
    gerar_array_iv("teste.dat", 512000, 42);
}

void gerar_array_iv(const char* filename, int size, int value) {
    // Function implementation
    // ...
}