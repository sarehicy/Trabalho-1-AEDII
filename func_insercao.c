#include "funcionalidades.h"

void funcOito(dadosHeader *dados){
    reg *registro = malloc(sizeof(reg));
    verificarReg(registro);
    header *cabecalho = malloc(sizeof(header));
    verificarHeader(cabecalho);
    headerIndex *cabecalhoIndex = malloc(sizeof(headerIndex));
    verificarHeaderIndex(cabecalhoIndex);
    regIndex *registroIndex = malloc(sizeof(regIndex));
    verificarRegIndex(registroIndex);

    char inBin[100];
    char inBinIndex[100];
    int n;

    scanf("%s", inBin);
    scanf("%s", inBinIndex);

    scanf("%d", &n);

    FILE *arqBin = fopen(inBin, "rb+");

    verificarArq(arqBin);

    FILE *arqBinIndex = fopen(inBinIndex, "rb+");

    verificarArq(arqBinIndex);

    lerCabecalho(arqBin, cabecalho);

    lerCabecalhoIndex(arqBin, cabecalhoIndex);

    montarDadosHeader(arqBin, registro, dados);

    dados->qtdPares = cabecalho->totalPares;

    // Para cada inserção
    for(int i = 0; i<n; i++){
        // Se não tiver registros lógicamente removidos
        if(cabecalho->topo == -1){

            montarRegistroCmd(registro);

            registroIndex->codEstacao = registro->codEstacao;
            registroIndex->RRN = cabecalho->proxRRN;

            //movePonteiroRRN(arqBin, cabecalho->proxRRN);
            fseek(arqBin, 0, SEEK_END);

            escreverRegistro(arqBin, registro);
            atualizarHeader(cabecalho, dados, registro, add);

            fseek(arqBinIndex, 0, SEEK_END);
            escreverRegIndex(arqBinIndex, registroIndex);
        }
        else{
            int RRNInserir = cabecalho->topo;
            movePonteiroRRN(arqBin, RRNInserir);
            lerRegistro(arqBin, registro);
            int RRNTopoNovo = registro->prox;

            inicializarRegistro(registro);

            montarRegistroCmd(registro);

            registroIndex->codEstacao = registro->codEstacao;
            registroIndex->RRN = RRNInserir;

            movePonteiroRRN(arqBin, RRNInserir);
            escreverRegistro(arqBin, registro);
            cabecalho->topo = RRNTopoNovo;
            atualizarHeader(cabecalho, dados, registro, insert);

            fseek(arqBinIndex, 0, SEEK_END);
            escreverRegIndex(arqBinIndex, registroIndex);
        }
    }
    escreverHeader(arqBin, cabecalho);

    // Depois de todas as inserções
    reordenarArqIndex(arqBinIndex);

    fclose(arqBin);
    fclose(arqBinIndex);
    BinarioNaTela(inBin);
    BinarioNaTela(inBinIndex);
}
