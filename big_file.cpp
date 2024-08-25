#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "big_file.h"
#include "prandom.h"

// Função auxiliar para trocar dois elementos do tipo ITEM_VENDA.
static inline void trocar(ITEM_VENDA& x, ITEM_VENDA& y){
    ITEM_VENDA aux;
    aux = x;  // Salva o valor de x em uma variável auxiliar.
    x = y;    // Atribui o valor de y a x.
    y = aux;  // Atribui o valor salvo em aux a y.
}

// Função para embaralhar os elementos de um vetor de ITEM_VENDA.
static void embaralhar(ITEM_VENDA* v, int ini, int fim){
    int i, j;

    // Itera sobre o vetor de trás para frente, trocando elementos aleatoriamente.
    for(i = fim-1; i > ini; i--){
        j = (rand_() % (i + 1));  // Gera um índice aleatório j entre ini e i.
        j = j <= ini ? ini+1 : j; // Garante que j seja maior que ini.
        trocar(v[i], v[j]);       // Troca os elementos v[i] e v[j].
    }
}

// Função para gerar um array de ITEM_VENDA, preencher com valores e embaralhar, depois salvar em um arquivo.
void gerar_array_iv(const char* arquivo_saida, unsigned int n_registros, int seed){
    ITEM_VENDA* iv;
    FILE* saida;
    uint32_t i;
    time_t t = time(NULL);  // Obtém o tempo atual para uso na geração de dados.

    srand(seed);  // Inicializa o gerador de números aleatórios com a semente fornecida.

    // Aloca memória para armazenar n_registros de ITEM_VENDA.
    iv = (ITEM_VENDA*) malloc(sizeof(ITEM_VENDA) * n_registros);

    // Preenche o array iv com dados simulados.
    for(i = 0; i < n_registros; i++){
        iv[i].id = i;  // Atribui o índice i como id.
        iv[i].id_venda = i + (rand() % 2);  // Atribui um id_venda, que pode ser i ou i+1.
        iv[i].desconto = (rand() % 10) / (float)100;  // Atribui um desconto aleatório entre 0.00 e 0.09.
        iv[i].data = t + ((-1 * (rand() % 30)) * 86400); // Atribui uma data aleatória dentro dos últimos 30 dias.
        iv[i].desc[0] = '\0';  // Inicializa a string desc como vazia.
    }

    // Embaralha o array de ITEM_VENDA.
    embaralhar(iv, 0, n_registros);

    // Abre o arquivo para escrita em modo binário.
    saida = fopen(arquivo_saida, "wb");
    if(saida == NULL){
        perror("Erro");  // Imprime uma mensagem de erro caso a abertura do arquivo falhe.
        exit(1);  // Encerra o programa com código de erro 1.
    }

    // Escreve o conteúdo do array iv no arquivo.
    fwrite(iv, sizeof(ITEM_VENDA), n_registros, saida);
    fclose(saida);  // Fecha o arquivo.
    free(iv);  // Libera a memória alocada para o array iv.

    return;  // Retorna da função (desnecessário, pois o retorno é void).
}

