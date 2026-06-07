#ifndef LER_ARQ_H
#define LER_ARQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliares.h"
#include "cabecalhos.h"
#include "escrever_arq.h"
#include "ler_arq.h"
#include "funcionalidades.h"
#include "registros.h"
#include "structs.h"

/* Verifica ponteiro do arquivo */
void verificarArq(FILE *arq);

/* Lê um registro do arquivo .csv e monta um registro na memória (struct)*/
void montarRegistro(FILE *arq, reg *registro);

/* Lê registro do arquivo .bin e monta um registro na memória (struct).
 Retorna 0 se a leitura for bem sucedida, retorna 1 se não conseguir ler*/
int lerRegistro(FILE *arq, reg *registro);

/* Lê cabeçalho do arquivo binario e verifica consistência do arquivo*/
int lerCabecalho(FILE *arq, header *cabecalho);

/* Lê cabeçalho do arquivo binario índice e verifica consistência do arquivo*/
lerCabecalhoIndex(FILE *arq, headerIndex *cabecalho);


#endif