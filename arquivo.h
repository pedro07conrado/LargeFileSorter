#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "big_file.h"

/**
PROTÓTIPOS
**/

void Arquivo_Dividir(const std::string& nome_arq_entrada, int quant_arq_temp, int quant_reg_total);
void ArquivosTemporarios_Remover(int quant_arq_temp);