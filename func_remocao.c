#include "funcionalidades.h"

void funcSete(dadosHeader *dados){

    reg *registro = malloc(sizeof(reg));
    verificarReg(registro);

    header *cabecalho = malloc(sizeof(header));
    verificarHeader(cabecalho);

    /* # User Input #*/
    char inBin[100], inBinIndex[100]; int n;
    scanf("%s %s %d", inBin, inBinIndex, &n);
    
    /* # Abrindo Arquivos #*/
    FILE *arqBin = fopen(inBin, "rb+");
    verificarArq(arqBin);
    FILE *arqBinIndex = fopen(inBinIndex, "wb");
    verificarArq(arqBinIndex);

    //debug printf("oi\n");
    lerCabecalho(arqBin, cabecalho);
    montarDadosHeader(arqBin, registro, dados);

    
    //Pois a função montarDados header move ponteiro para o final do arquivo
    fseek(arqBin, tamCabecalho, SEEK_SET); 


    int qtdCampos;
    while(n--){

        scanf("%d", &qtdCampos);
        char *linha[qtdCampos*2]; 

        montarBusca(linha, qtdCampos);

        cabecalho->status = inconsistente; // pq vai escrever no arq
        escreverHeader(arqBin, cabecalho);

        int RRN = -1;   //RRN do registro lido

        while(check_eof(arqBin)){
            RRN++;
            //debug printf("Registro de rrn %d\n", RRN);

            inicializarRegistro(registro);

            if(lerRegistro(arqBin, registro))
                continue;
            
            //Se registro corresponder a busca, removê-lo
            if(buscaRegistro(registro, linha, qtdCampos)){
                //debug printf("Registro encontrado\n");
                //debug imprimirRegistro(registro);

                registro->rem = '1';
                //debug printf("Registro rem: %c\n", registro->rem);
                
                registro->prox = cabecalho->topo;
                cabecalho->topo = RRN;


                // Move ponteiro para inicio do registro de rrn removido p escrever
                movePonteiroRRN(arqBin, RRN);
                escreverRegistro(arqBin, registro);
                atualizarHeader(cabecalho, dados, registro, rmv);
                
            }

        }

        cabecalho->status = consistente; // pq vai escrever no arq
        escreverHeader(arqBin, cabecalho);


       desalocaVetorDePonteiros(linha, qtdCampos*2);
    }

    fclose(arqBin);
    fclose(arqBinIndex);
    free(registro);
    free(cabecalho);
    
    BinarioNaTela(inBin);
    // Realiza busca e remove arquivo
    // É necessário atualizar cabeçalho do arqBin
    // É necessário atualizar arquivo inBinIndex
}