#include "funcionalidades.h"

void funcSete(dadosHeader *dados){
    /*      # structs #     */
    reg *registro = malloc(sizeof(reg));
    verificarReg(registro);

    header *cabecalho = malloc(sizeof(header));
    verificarHeader(cabecalho);

    headerIndex *cabecalhoIndex = malloc(sizeof(headerIndex));
    if (!cabecalhoIndex) exit(0);



    /*      # User Input #      */
    char inBin[100], inBinIndex[100]; int n;
    scanf("%s %s %d", inBin, inBinIndex, &n);
    


    /*      # Abrindo Arquivos #      */
    FILE *arqBin = fopen(inBin, "rb+");
    verificarArq(arqBin);
    FILE *arqBinIndex = fopen(inBinIndex, "rb");
    verificarArq(arqBinIndex);

    lerCabecalhoIndex(arqBinIndex, cabecalhoIndex);
    lerCabecalho(arqBin, cabecalho);
    montarDadosHeader(arqBin, registro, dados);
    //Pois a função montarDados header move ponteiro para o final do arquivo
    fseek(arqBin, tamCabecalho, SEEK_SET); 

    /*      # Buscas #       */

    cabecalho->status = inconsistente; // porque vai escrever no arq
    escreverHeader(arqBin, cabecalho);

    int qtdCampos;
    while(n--){

        scanf("%d", &qtdCampos);
        char *linha[qtdCampos*2]; 
        montarBusca(linha, qtdCampos);

        //cabecalho->status = inconsistente; // porque vai escrever no arq
        //escreverHeader(arqBin, cabecalho);

        int RRN = 0;    //Guarda RRN do registro cujos campos estão sendo comparados


        /*      # Busca por codEstacao #        */

        for (int i = 0; i < (qtdCampos*2); i+=2){
            if (!(strcmp(linha[i], "codEstacao"))){
                RRN = buscaIndexada(arqBinIndex, atoi(linha[i+1]));

                // registro com codEstacao encontrado, compara demais campos da busca
                if (RRN != -1){
                    movePonteiroRRN(arqBin, RRN);
                    inicializarRegistro(registro);
                    if (lerRegistro(arqBin, registro)) break;

                    if(buscaRegistro(registro, linha, qtdCampos)){
                        registro->rem = '1';

                        registro->prox = cabecalho->topo;
                        cabecalho->topo = RRN;

                        // Move ponteiro para inicio do registro de rrn removido p escrever
                        movePonteiroRRN(arqBin, RRN);
                        escreverRegistro(arqBin, registro);
                        atualizarHeader(cabecalho, dados, registro, rmv);
                        fclose(arqBinIndex);
                        arqBinIndex = removeRegistroIndex(inBinIndex, RRN);

                        RRN = -1;
                    } else break;

                } else break;

            }
        }

        // De alguma forma, a busca por codEstacao foi realizada, então não realiza a busca normal
        if (RRN != 0 ) continue;

       /* # Busca Normal # */
        RRN = -1; fseek(arqBin, tamCabecalho, SEEK_SET); 
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

       desalocaVetorDePonteiros(linha, qtdCampos*2);
    }
    cabecalho->status = consistente;
    escreverHeader(arqBin, cabecalho);

    fclose(arqBin);
    fclose(arqBinIndex);
    free(registro);
    free(cabecalho);
    
    BinarioNaTela(inBin);
    BinarioNaTela(inBinIndex);
    // Realiza busca e remove arquivo
    // É necessário atualizar cabeçalho do arqBin
    // É necessário atualizar arquivo inBinIndex
}