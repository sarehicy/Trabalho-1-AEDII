#include "escrever_arq.h"

void escreverRegistro(FILE *arq, reg *registro){
    verificarArq(arq);

    /*    #   Escrevendo Campos do Registro  #  */

    fwrite(&(registro->rem), sizeof(char), 1, arq);
    
    fwrite(&(registro->prox), sizeof(int), 1, arq);

    fwrite(&(registro->codEstacao), sizeof(int), 1, arq);

    fwrite(&(registro->codLinha), sizeof(int), 1, arq); 

    fwrite(&(registro->codProxEstacao), sizeof(int), 1, arq);
    
    fwrite(&(registro->distProxEstacao), sizeof(int), 1, arq);

    fwrite(&(registro->codLinhaInteg), sizeof(int), 1, arq);
    
    fwrite(&(registro->codEstacaoInteg), sizeof(int), 1, arq);

    fwrite(&(registro->tamNomeEstacao), sizeof(int), 1, arq);

    fwrite(&(registro->nomeEstacao), sizeof(char), registro->tamNomeEstacao, arq);

    fwrite(&(registro->tamNomeLinha), sizeof(int), 1, arq);

    fwrite(&(registro->nomeLinha), sizeof(char), registro->tamNomeLinha, arq);

    /*   #   Preenchendo com Lixo    # */

    int qtdBytesLixo = tamRegistro - (bytesFixos + registro->tamNomeEstacao + registro->tamNomeLinha);
    char lixoSign = '$';

    //  Enquanto houver espaço vazio, escreve '$' no arquivo
    while(qtdBytesLixo > 0){
        fwrite(&lixoSign, sizeof(char), 1, arq);

        qtdBytesLixo--;
    }
}

void escreverHeader(FILE *arq, header *cabecalho){
    verificarArq(arq); 
    fseek(arq, 0, SEEK_SET);

    // Escreve os dados do cabeçalho da memória no arquivo

    fwrite(&(cabecalho->status), sizeof(char), 1, arq);

    fwrite(&(cabecalho->topo), sizeof(int), 1, arq);
    
    fwrite(&(cabecalho->proxRRN), sizeof(int), 1, arq);
    
    fwrite(&(cabecalho->totalEstacoes), sizeof(int), 1, arq);
    
    fwrite(&(cabecalho->totalPares), sizeof(int), 1, arq);
}

void escreverHeaderIndex(FILE *arq, headerIndex *cabecalho){
    verificarArq(arq);
    verificarHeaderIndex(cabecalho);
    fseek(arq, 0, SEEK_SET);

    fwrite(&(cabecalho->status), sizeof(char), 1, arq);
}