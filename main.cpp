#include <iostream>
#include <cstdlib>
#include <ctime>
#include "big_file.h"
#include "ordenacao.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

using namespace std;

int main(int argc, char** argv) {
    unsigned long int qtdRegistros;
    unsigned long int maximoMemoria;
    unsigned long int tamBufferSaida;
    int div;
    clock_t tempo;

    // Verifica se os parâmetros foram passados pela linha de comando
    if (argc != 4) {
        qtdRegistros = 512000;
        maximoMemoria = 67108864;
        tamBufferSaida = maximoMemoria / 2;
    } else {
        qtdRegistros = static_cast<unsigned long int>(atoi(argv[1]));
        maximoMemoria = static_cast<unsigned long int>(atoi(argv[2]));
        div = atoi(argv[3]);
        tamBufferSaida = maximoMemoria / div;
    }

    // Interface diferenciada de saída no terminal
    cout << "##############################################\n";
    cout << "#         INICIANDO PROCESSO...              #\n";
    cout << "##############################################\n\n";

    cout << "[1] Fase 1: Gerando arquivo de dados 'teste.dat'...\n";
    gerar_array_iv("teste.dat", qtdRegistros, 42);

    cout << "[2] Fase 2: Executando ordenação externa...\n";
    cout << "   - Configurações:\n";
    cout << "      > Quantidade de registros: " << qtdRegistros << endl;
    cout << "      > Memória máxima: " << maximoMemoria << " bytes\n";
    cout << "      > Tamanho do buffer de saída: " << tamBufferSaida << " bytes\n";
    
    tempo = clock();
    ordenacao_externa("teste.dat", maximoMemoria, tamBufferSaida, "saida");
    tempo = clock() - tempo;

    cout << "\n[3] Fase 3: Ordenação finalizada! Verificando integridade...\n";

    int resposta = isSaidaOrdenada("saida");
    cout << "\n##############################################\n";
    if (resposta) {
        cout << "# Resultado: O arquivo 'saida' está ordenado #\n";
    } else {
        cout << "# Resultado: O arquivo 'saida' NÃO está ordenado #\n";
    }
    cout << "##############################################\n";

    // Tempo total da execução
    cout << "\nTempo total de processamento: " << static_cast<float>(tempo) / CLOCKS_PER_SEC << " segundos\n";

    cout << "\n########## FINALIZAÇÃO ##########\n";

    #ifdef _WIN32
    // Checagem de vazamento de memória no Windows
    _CrtDumpMemoryLeaks();
    #endif

    return 0;
}
