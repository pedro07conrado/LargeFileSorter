#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> // Para std::memset e std::strcpy

class ItemVenda {
public:
    int id;
    int id_venda;
    double desconto;
    long data;
    char obs[100]; // Tamanho fixo

    ItemVenda() : id(0), id_venda(0), desconto(0), data(0) {
        std::memset(obs, 0, sizeof(obs));
    }
};

class Buffer {
private:
    std::vector<ItemVenda> itens;
    int quant_max_registros_buffer;
    int bloco;
    bool status_buffer;
    bool status_arquivo;
    std::string arq_nome;

public:
    Buffer(const std::string& nome_arq_saida, int quant_reg_buffer_saida)
        : quant_max_registros_buffer(quant_reg_buffer_saida), bloco(0),
          status_buffer(true), status_arquivo(true), arq_nome(nome_arq_saida) {
        itens.reserve(quant_reg_buffer_saida); // Reservando espaço para os itens
    }

    void inserir(const ItemVenda& menor_item) {
        if (itens.size() < quant_max_registros_buffer) {
            itens.push_back(menor_item);
        } else {
            std::cerr << "Buffer cheio, não é possível inserir mais itens." << std::endl;
        }
    }

    void despejar() {
        std::ofstream arq_saida(arq_nome, std::ios::binary | std::ios::app);

        if (!arq_saida) {
            std::cerr << "Erro ao abrir o arquivo: " << arq_nome << std::endl;
            return;
        }

        arq_saida.write(reinterpret_cast<const char*>(itens.data()), itens.size() * sizeof(ItemVenda));

        if (itens.size() < quant_max_registros_buffer) {
            status_buffer = false;
        }

        itens.clear(); // Limpando o buffer após despejar
        bloco++;
    }

    ~Buffer() {
        if (!itens.empty()) {
            despejar();
        }
    }
};

int main() {
    // Exemplo de uso
    Buffer buffer("saida.dat", 100);

    ItemVenda item;
    item.id = 1;
    item.id_venda = 10;
    item.desconto = 5.0;
    std::strcpy(item.obs, "Observação exemplo");

    buffer.inserir(item);
    buffer.despejar();

    return 0;
}