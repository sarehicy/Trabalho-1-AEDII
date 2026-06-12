#include "funcionalidades.h"


void funcNove(dadosHeader *dados){
    /*      # structs #     */
    reg *registro = malloc(sizeof(reg));
    verificarReg(registro);

    header *cabecalho = malloc(sizeof(header));
    verificarHeader(cabecalho);

    headerIndex *cabecalhoIndex = malloc(sizeof(headerIndex));
    verificarHeaderIndex(cabecalhoIndex);


    /*      # User Input #      */
    char inBin[100];
    char inBinIndex[100];
    int n;
    scanf("%s", inBin);
    scanf("%s", inBinIndex);
    scanf("%d", &n);


    // # Abertura e verificação de arquivos # // 
    FILE *arqBin = fopen(inBin, "rb+");
    verificarArq(arqBin);

    FILE *arqBinIndex = fopen(inBinIndex, "rb+");
    verificarArq(arqBinIndex);

    montarDadosHeader(arqBin, registro, dados);

    lerCabecalhoIndex(arqBinIndex, cabecalhoIndex);
    lerCabecalho(arqBin, cabecalho);

    /*      # Buscas #       */

    cabecalho->status = inconsistente; // porque vai escrever no arq
    escreverHeader(arqBin, cabecalho);
    cabecalhoIndex->status = inconsistente;
    escreverHeaderIndex(arqBinIndex, cabecalhoIndex);

    int qtdCampos, qtdAtualizacoes;
    while(n--){
        scanf("%d", &qtdCampos);
        char *linhaBusca[qtdCampos*2];           // Vetor com os *pares "campo" e "valor" 
        montarBusca(linhaBusca, qtdCampos);

        scanf("%d", &qtdAtualizacoes);
        char *linhaAtualizacoes[qtdAtualizacoes*2];
        montarBusca(linhaAtualizacoes, qtdAtualizacoes);


        /*  #   Busca Indexada    #   */
        int RRN = -2;
        for(int i = 0; i<(qtdCampos*2); i+=2){
            if (!(strcmp(linhaBusca[i], "codEstacao"))){     // Se algum campo for codEstacao faz a busca indexada
                RRN = buscaIndexada(arqBinIndex, atoi(linhaBusca[i+1]));

                if (RRN != -1){  // Encontrou registro
                    // Lê registro
                    movePonteiroRRN(arqBin, RRN);
                    inicializarRegistro(registro);
                    if (lerRegistro(arqBin, registro)) break;

                    // Compara demais campos
                    if (buscaRegistro(registro, linhaBusca, qtdCampos)){  

                        /* Chama função atualizarHeader() como se uma remoção houvesse acontecido,
                        pois se os campos "nomeEstacao", "codEstacao" ou "codProxEstacao" forem alterados, 
                        existe a possibilidade de que o o total número de estações ou o total número de pares seja afetado.*/
                        atualizarHeader(cabecalho, dados, registro, rmv); 
                        atualizarRegistro(registro, linhaAtualizacoes, qtdAtualizacoes);

                        // Escreve registro atualizado
                        movePonteiroRRN(arqBin, RRN);
                        escreverRegistro(arqBin, registro);
                        atualizarHeader(cabecalho, dados, registro, insert);
                    } else break;

                }


            }


        }


    }


}