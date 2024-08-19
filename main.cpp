#include <cmath>
#include <ctime>
#include <vector>
#include <memory>

#include "big_file.h"   // Presumindo que esta biblioteca possui funções para lidar com arquivos grandes
#include "Buffer.h"     // Presumindo que esta biblioteca contém a classe Buffer e suas funções associadas
#include "arquivo.h"    // Presumindo que esta biblioteca contém funções para manipulação de arquivos
#include "ordenacao.h"  // Presumindo que esta biblioteca contém as funções de ordenação necessárias

int main() {
    //------------------- DEFINIÇÃO DOS CONTROLES -------------------

    int QUANT_REGISTROS_TOTAL = 256000;                         // N - Quantidade de registros
    int TAM_MAXIMO_BUFFER_ENTRADA = 8388608;                    // B - Tamanho máximo do buffer de entrada
    int TAM_MAX_BUFFER_SAIDA = TAM_MAXIMO_BUFFER_ENTRADA / 8;   // S - Tamanho máximo do buffer de saída

    //------------------- DEFINIÇÃO DOS SUBCONTROLES -------------------
    int TAM_ARQUIVO_ENTRADA = 1024 * QUANT_REGISTROS_TOTAL;
    int QUANT_ARQUIVOS_TEMPORARIOS = std::ceil(static_cast<double>(TAM_ARQUIVO_ENTRADA) / TAM_MAXIMO_BUFFER_ENTRADA) + 1;
    int QUANT_REGISTROS_BUFFER_SAIDA = TAM_MAX_BUFFER_SAIDA / 1024;
    int QUANT_REGISTROS_BUFFER_ENTRADA = std::ceil(static_cast<double>((TAM_MAXIMO_BUFFER_ENTRADA - TAM_MAX_BUFFER_SAIDA) / QUANT_ARQUIVOS_TEMPORARIOS) / 1024);

    //------------------- DECLARAÇÃO DE VARIÁVEIS --------------------------------------
    clock_t t_inicio, t_fim;
    double tempo_execucao;

    //--------------- DENIFIR NOME DOS ARQUIVOS ----------------------------------------
    std::string nome_arquivo_entrada = "entrada.dat";
    std::string nome_arquivo_saida = "saida.dat";

    //--------------- GERAR ARQUIVO DE ENTRADA -----------------------------------------
    gerar_array_iv(nome_arquivo_entrada.c_str(), QUANT_REGISTROS_TOTAL, 42);
    std::cout << "Arquivo de entrada gerado com sucesso!" << std::endl;

    //--------------- INICIAR CRONOMETRO -----------------------------------------------
    t_inicio = clock();

    //--------------- DIVIDIR ARQUIVO DE ENTRADA EM ARQUIVOS TEMPORARIOS ---------------
    Arquivo_Dividir(nome_arquivo_entrada.c_str(), QUANT_ARQUIVOS_TEMPORARIOS, QUANT_REGISTROS_TOTAL);
    std::cout << "Arquivos temporarios gerados com sucesso!" << std::endl;

    //--------------- CRIAR BUFFERS DE ENTRADA -----------------------------------------
    auto vetor_buffers_entrada = BE_CriarVetor(QUANT_ARQUIVOS_TEMPORARIOS, QUANT_REGISTROS_BUFFER_ENTRADA);
    std::cout << "Buffers de entrada criados com sucesso!" << std::endl;

    //--------------- CRIAR ARQUIVO DE SAÍDA -------------------------------------------
    {
        std::ofstream arquivo_saida(nome_arquivo_saida, std::ios::binary);
    }
    std::cout << "Arquivo de saida criado com sucesso!" << std::endl;

    //--------------- CRIAR BUFFERS DE SAIDA --------------------------------------------
    auto buffer_saida = std::make_unique<Buffer>(BS_Criar(nome_arquivo_saida.c_str(), QUANT_REGISTROS_BUFFER_SAIDA));
    std::cout << "Buffer de saida criado com sucesso!" << std::endl;

   //--------------- INTERCALAÇÃO DE K VIAS --------------------------------------------
    Merge_K_Vias(vetor_buffers_entrada.data(), &buffer_saida, QUANT_REGISTROS_BUFFER_SAIDA, nome_arquivo_saida.c_str(), QUANT_REGISTROS_TOTAL);
    std::cout << "Intercalacao de k vias concluida com sucesso!" << std::endl;

    //--------------- REMOVER ARQUIVOS TEMPORARIOS --------------------------------------
    ArquivosTemporarios_Remover(QUANT_ARQUIVOS_TEMPORARIOS);
    std::cout << "Arquivos temporarios removidos com sucesso!" << std::endl;

    //--------------- DESTRUIR VETOR DE BUFFERS ----------------------------------------------
    BE_Destruir(vetor_buffers_entrada);
    std::cout << "Vetor de buffers de entrada destruido com sucesso!" << std::endl;

    //--------------- DESTRUIR BUFFER DE SAIDA -------------------------------------------------
    BS_Destruir(buffer_saida.get());
    std::cout << "Buffer de saida destruido com sucesso!" << std::endl;

    //--------------- FINALIZAR CRONOMETRO ----------------------------------------------
    t_fim = clock();
    tempo_execucao = static_cast<double>(t_fim - t_inicio) / CLOCKS_PER_SEC;
    std::cout << "Tempo de execucao: " << tempo_execucao << " segundos" << std::endl;

    std::cout << "FIM" << std::endl;
    return 0;
}