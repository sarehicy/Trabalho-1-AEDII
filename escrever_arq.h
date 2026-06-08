#ifndef ESCREVER_ARQ_H
#define ESCREVER_ARQ_H

#include <stdio.h>
#include "auxiliares.h"
#include "cabecalhos.h"
#include "escrever_arq.h"
#include "ler_arq.h"
#include "funcionalidades.h"
#include "registros.h"
#include "structs.h"

/* Escreve registro (struct) no arquivo binário */
void escreverRegistro(FILE *arq, reg *registro);

/* Escreve o cabeçalho no arquivo binário   */
void escreverHeader(FILE *arq, header *cabecalho);

/*Escreve cabeçalho no arquivo índice*/
void escreverHeaderIndex(FILE *arq, headerIndex *cabecalho);

#endif