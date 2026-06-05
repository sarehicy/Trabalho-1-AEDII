#ifndef REGISTROS_H
#define REGISTROS_H

#include "auxiliares.h"
#include "cabecalhos.h"
#include "escrever_arq.h"
#include "ler_arq.h"
#include "funcionalidades.h"
#include "registros.h"
#include "structs.h"

#define bytesFixos 37       // Soma da quantidade de bytes dos campos fixos do registro
#define tamRegistro 80      // Tamanho em bytes do registro

/* Verifica ponteiro da struct registro */
void verificarReg(reg *registro);

/* Inicializa registro de dados com valores default */
void inicializarRegistro(reg *registro);

/* Imprime campos do registro de dados na saída padrão */
void imprimirRegistro(reg *registro);

/*Dado um Registro, compara todos os campos buscados.
   Retorna 1 se o registro corresponder a busc, 0 se não.*/
int buscaRegistro(reg *registro, char **linha, int qtdCampos);

/* Compara o valor de um campo do registro de dados com o valor do campo buscado.
    Retorna 1 se os campos forem iguais, 0 se forem diferentes.*/
int buscaCampo(reg *registro, char campo[], char valor[]);

void lerRegistroIndex(FILE *arqBinIndex, regIndex *registroIndex);

#endif