#include "Buffer.h"
#include "arquivo.h"
#include <vector>
#include <memory>

/**************
* IMPLEMENTAÇÃO
**************/

//--------------- CRIAR VETOR DE BUFFERS DE ENTRADA -----------------------------------
std::vector<std::unique_ptr<Buffer>> BE_CriarVetorBuffer(int quant_arq_temp, int quant_reg_buffer_entrada)
{
    std::vector<std::unique_ptr<Buffer>> vetor_buffer_entrada;

    for (int i = 0; i < quant_arq_temp; i++)
    {
        std::string nome_arq_temp = "P" + std::to_string(i) + ".dat";
        vetor_buffer_entrada.push_back(BE_CriarBuffer(nome_arq_temp, quant_reg_buffer_entrada, quant_arq_temp));
    }

    return vetor_buffer_entrada;
}

//--------------- CRIAR BUFFERS DE ENTRADA --------------------------------------------
std::unique_ptr<Buffer> BE_CriarBuffer(const std::string& nome_arq_temp, int quant_reg_buffer_entrada, int quant_arq_temp)
{
    auto buffer_entrada = std::make_unique<Buffer>();
    auto itens = std::make_unique<ITEM_VENDA[]>(quant_reg_buffer_entrada);
    FILE *arq_temp = fopen(nome_arq_temp.c_str(), "rb");

    fread(itens.get(), sizeof(ITEM_VENDA), quant_reg_buffer_entrada, arq_temp);

    buffer_entrada->quant_registros_buffer = quant_reg_buffer_entrada;
    buffer_entrada->quant_max_registros_buffer = quant_reg_buffer_entrada;
    buffer_entrada->quant_buffers = quant_arq_temp;
    buffer_entrada->bloco = 1;
    buffer_entrada->status_buffer = Status::ATIVO;
    buffer_entrada->status_arquivo = Status::ATIVO;
    buffer_entrada->arq_nome = nome_arq_temp;
    buffer_entrada->itens = itens.release();

    fclose(arq_temp);

    return buffer_entrada;
}

//--------------- REENCHER BUFFER ----------------------------------------------
void BE_Reencher(Buffer *buffer)
{
    FILE *arq_temp = fopen(buffer->arq_nome.c_str(), "rb");
    std::unique_ptr<ITEM_VENDA[]> itens;

    fseek(arq_temp, buffer->bloco * buffer->quant_max_registros_buffer * sizeof(ITEM_VENDA), SEEK_SET);
    int inicio = ftell(arq_temp);
    fseek(arq_temp, 0, SEEK_END);
    int fim = ftell(arq_temp);
    int tam_restante = fim - inicio;
    fseek(arq_temp, buffer->bloco * buffer->quant_max_registros_buffer * sizeof(ITEM_VENDA), SEEK_SET);

    if (tam_restante <= buffer->quant_max_registros_buffer * sizeof(ITEM_VENDA))
    {
        itens = std::make_unique<ITEM_VENDA[]>(tam_restante / sizeof(ITEM_VENDA));
        fread(itens.get(), sizeof(ITEM_VENDA), tam_restante / sizeof(ITEM_VENDA), arq_temp);
        buffer->quant_registros_buffer = tam_restante / sizeof(ITEM_VENDA);

        buffer->status_arquivo = Status::INATIVO;
        delete[] buffer->itens;
        buffer->itens = itens.release();
    }
    else
    {
        itens = std::make_unique<ITEM_VENDA[]>(buffer->quant_max_registros_buffer);
        fread(itens.get(), sizeof(ITEM_VENDA), buffer->quant_max_registros_buffer, arq_temp);
        buffer->quant_registros_buffer = buffer->quant_max_registros_buffer;

        delete[] buffer->itens;
        buffer->itens = itens.release();
        buffer->bloco++;
    }

    fclose(arq_temp);
}

void BE_Proximo(Buffer *buffer)
{
    for (int i = 0; i < buffer->quant_registros_buffer - 1; i++)
    {
        buffer->itens[i] = buffer->itens[i + 1];
    }
}
//--------------- CONSUMIR ITEM VENDA DO BUFFER ----------------------------------------------
ITEM_VENDA BE_Consumir(Buffer *buffer)
{
    ITEM_VENDA item = buffer->itens[0];

    buffer->quant_registros_buffer--;

    if (buffer->quant_registros_buffer == 0 && buffer->status_arquivo == Status::ATIVO)
    {
        BE_Reencher(buffer);
    }
    else
    {
        BE_Proximo(buffer);
    }

    return item;
}

//--------------- BUFFER VAZIO --------------------------------------------------------
bool BE_Vazio(const Buffer *buffer_entrada)
{
    return buffer_entrada->quant_registros_buffer == 0;
}

//--------------- VETOR DE BUFFERS VAZIO ----------------------------------------------
bool BE_VetorVazio(const std::vector<std::unique_ptr<Buffer>>& vetor_buffer_entrada)
{
    for (const auto& buffer : vetor_buffer_entrada)
    {
        if (!BE_Vazio(buffer.get()))
        {
            return false;
        }
    }

    return true;
}

//--------------- DESTRUIR VETORES DE BUFFERS ----------------------------------------------
void BE_Destruir(std::vector<std::unique_ptr<Buffer>>& vetor_buffers)
{
    vetor_buffers.clear();
}