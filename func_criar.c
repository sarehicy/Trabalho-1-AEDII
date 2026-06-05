#include "funcionalidades.h"

void funcUm(dadosHeader *dados){

    header *cabecalho = criarHeader();
    reg *registro = malloc(sizeof(reg));
    verificarReg(registro);

    // Lê os nomes dos arquivos .csv e .bin
    char inCsv[100], outBin[100];
    scanf("%s %s", &inCsv, &outBin);


    /*----------------------------------------------------------
                 ABRINDO E VERIFICANDO ARQUIVOS
    ----------------------------------------------------------*/

    FILE *arqCsv = fopen(inCsv, "r");
    verificarArq(arqCsv);
    pularCabecalhoCsv(arqCsv);

    FILE *arqBin = fopen(outBin, "wb");
    verificarArq(arqBin);

    /*----------------------------------------------------------
                     LENDO CSV E ESCREVENDO BIN
    ----------------------------------------------------------*/

    // Muda status do arquivo para inconsistente enquanto são realizadas escritas
    cabecalho->status = '0';

    // Escreve um cabeçalho inicial no arquivo bin
    escreverHeader(arqBin, cabecalho);

    while(check_eof(arqCsv)){
        inicializarRegistro(registro);                  // "Zera" campos do registro 
        montarRegistro(arqCsv, registro);               // Copia registro do csv para a struct registro
        atualizarHeader(cabecalho, dados, registro, 1); // Atualiza cabeçalho indicando que foi feita uma escrita
        escreverRegistro(arqBin, registro);             // Escreve registro no binário
    }

    cabecalho->status = '1';

    // Escreve o cabeçalho final no arquivo bin
    escreverHeader(arqBin, cabecalho);
   
    /*-------------------------------------------------------------
        FINALIZANDO A FUNÇÃO (FECHANDO ARQUIVOS E BINARIO NA TELA)
    ----------------------------------------------------------*/
    free(registro);
    free(cabecalho);
    fclose(arqCsv);
    fclose(arqBin);

    BinarioNaTela(outBin);
}

void funcCinco(){
    reg *registro = malloc(sizeof(reg)*1);
    verificarReg(registro);
    header *cabecalho = malloc(sizeof(header)*1);
    verificarHeader(cabecalho);

    headerIndex *cabecalhoIndex = malloc(sizeof(headerIndex)*1);

    // Entrada com nome dos arquivos
    char inBin[100], inBinIndex[100];

    scanf("%s", &inBin);
    scanf("%s", inBinIndex);

    // Abertura de arquivos
    FILE *arqBin = fopen(inBin, "rb");
    FILE *arqBinIndex = fopen(inBinIndex, "wb");
    verificarArq(arqBin);
    verificarArq(arqBinIndex);

    lerCabecalho(arqBin, cabecalho);

    // vetores para par(codEstacao, RRN)
    int capacidade = 10;
    regIndex *vetRegistroIndex = malloc(sizeof(regIndex)*capacidade);

    // Loop até o final do arquivo binario
    int i = 0;
    int rrnAtual = -1;
    while(check_eof(arqBin)){
        rrnAtual++;

        // Se a capacidade for atingida, aloca mais memória
        if(i >= capacidade-1){
            capacidade *= 2;
            vetRegistroIndex = realloc(vetRegistroIndex, sizeof(regIndex)*capacidade);
        }

        // Le registro e guarda Estacao e RRN nos vetores
        if(lerRegistro(arqBin, registro) == 1) {
            continue;
        }
        vetRegistroIndex[i].codEstacao = registro->codEstacao;
        vetRegistroIndex[i].RRN = rrnAtual;

        i++;
    }
    ordenarIndiceHeap(vetRegistroIndex, i);

    cabecalhoIndex->status = '0';
    fwrite(&(cabecalhoIndex->status), sizeof(char), 1, arqBinIndex);

    for(int j=0; j<i; j++){
        fwrite(&(vetRegistroIndex[j].codEstacao), sizeof(int), 1, arqBinIndex);
        fwrite(&(vetRegistroIndex[j].RRN), sizeof(int), 1, arqBinIndex);
    }

    cabecalhoIndex->status = '1';
    fseek(arqBinIndex, 0, SEEK_SET);
    fwrite(&(cabecalhoIndex->status), sizeof(char), 1, arqBinIndex);

    fclose(arqBin);
    fclose(arqBinIndex);

    BinarioNaTela(inBinIndex);
}


