#pragma once

/*FUNÇÃO QUE CRIA PARTIÇÕES DE UM ARQUIVO MAIOR
*@param: arquivo = arquivo que queremos particionar
*@param: qtdParticoes = quantidade de partições
*@return: vetor de strings que contém os nomes do arquivo de cada partição
*/
char **criarParticao(char *arquivo, int qtdParticoes);

/*FUNÇÃO QUE VERIFICA SE PARTIÇÃO ESTÁ ORDENADA
*@param: arquivo = arquivo que queremos verificar se está ordenado
*/
void teste_ordenacao_particao (char *arquivo);