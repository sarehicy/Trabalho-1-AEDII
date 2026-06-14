#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliares.h"
#include "cabecalhos.h"
#include "arquivos.h"
#include "funcionalidades.h"
#include "registros.h"
#include "structs.h"


// --- Funcionalidade 1 do programa ---
// Lê um arquivo csv e gera um arquivo bin
void funcUm(dadosHeader *dados);

// --- Funcionalidade 2 do programa ---
// Dado um arquivo .bin, imprime seus registros
void funcDois();

// --- Funcionalidade 3 do programa ---
// Pesquisa e retorna, se econtrar, registros com os campos especificados na busca
void funcTres();

// --- Funcionalidade 4 do programa ---
// Pesquisa e retorna, se encontrar, registro com o RRN específicado
void funcQuatro();

// --- Funcionalidade 5 do programa ---
// Dado um arquivo binário cria um arquivo índice
void funcCinco();

// --- Funcionalidade 6 do programa ---
// Busca por campo, onde se um dos campos buscados for "codEstacao" faz uma busca indexada
void funcSeis();

/*Remove todos os registros que correspondem a um determinado critério de busca*/
void funcSete(dadosHeader *dados);


void funcOito(dadosHeader *dados);  

void funcNove(dadosHeader *dados);

#endif