#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "auxiliares.h"
#include "cabecalhos.h"
#include "escrever_arq.h"
#include "ler_arq.h"
#include "funcionalidades.h"
#include "registros.h"
#include "structs.h"

/* Lê critérios da busca e guarda em um vetor */
void montarBusca(char **linha, int qtdCampos);

/* Desaloca strings dentro de um vetor*/
void desalocaVetorDePonteiros(char **v, int n);

void ScanQuoteString(char *str);

/* Imprime os campos inteiros do registro*/
void printInt(int n);

/* Imprime os campos string do registro*/
void printString(char string[], int tamanho);

/* Move o ponteiro do arquivo até o registro de RRN desejado*/
void movePonteiroRRN(FILE *arq, int rrn);


/* Lê e descarta a primeira linha do arquivo (header) */
void pularCabecalhoCsv(FILE *arq);

void BinarioNaTela(char *arquivo);

char check_eof(FILE* f);

// Faz uma busca em um arquivo indice, retorna o RRN do codEstacao

void ordenarIndiceHeap(regIndex *vetRegistroIndex, int n);
void heapifyIndice(regIndex *vetRegistroIndex, int n, int i);
void troca(regIndex *a, regIndex *b);
void printArray(int arr[], int n);

/* Realiza busca binária no arquivo e retorna RRN do registro com determinado código estação.
Retorna -1 se não conseguir encontrar o registro.*/
int buscaIndexada(FILE *arq, int codEstacao);

/*Remove registro com um determinado RRN do arquivo Index*/
void removeRegistroIndex(char *nomeArq, int RRN);


#endif