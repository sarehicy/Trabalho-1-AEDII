#include "ler_arq.h"

void verificarArq(FILE *arq){
    if (!arq){
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
}

void montarRegistro(FILE *arq, reg *registro){
    verificarArq(arq);
    
    // string que irá conter uma linha (registro) lido do arquivo csv
    char *line = malloc(sizeof(char)*90);       
    if(!line){
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    // Ponteiro para dar free() na line
    char *aux = line;                       
    

    size_t n = 90;                              
    getline(&line, &n, arq);                    // lê uma linha no arqCsv
    line[strcspn(line, "\r\n")] = '\0';


   /*========================================================
            Campos no Arquivo -> Campos da Struct
    ========================================================*/

    char *p = strsep(&line, ",");               // lê código da estação na string
    if(p && *p)                                 // verifica se p e o ponteiro de p existem
        registro->codEstacao = atoi(p);         // guarda código da estação no registro (struct)

    p = strsep(&line, ",");                     // lê nome da estação
    strcpy(registro->nomeEstacao, p);           //copia nome da estação para o registro (struct)

    p = strsep(&line, ",");                     
    if(p && *p)                                 
        registro->codLinha = atoi(p);           

    p = strsep(&line, ",");                     
    strcpy(registro->nomeLinha, p);            

    p = strsep(&line, ",");                     
    if(p && *p)                                 
        registro->codProxEstacao = atoi(p);     

    p = strsep(&line, ",");               
    if(p && *p)                       
        registro->distProxEstacao = atoi(p);  

    p = strsep(&line, ",");                     
    if(p && *p)                      
        registro->codLinhaInteg = atoi(p);     
    
    p = strsep(&line, "\0");                     //se coloca isso pega o valor certo, mas imprime 0 no nulo
    if(p && *p)                                  //verifica se p e o ponteiro de p existem
        registro->codEstacaoInteg = atoi(p);    // guarda código da estação integ (?) no registro (struct)


    registro->tamNomeEstacao = strlen(registro->nomeEstacao);
    registro->tamNomeLinha = strlen(registro->nomeLinha);
    
    free(aux);
}

int lerRegistro(FILE *arq, reg *registro){
    verificarArq(arq);
    verificarReg(registro);


    /*   #   Verificando se Registro foi Removido   # */

    fread(&(registro->rem), sizeof(char), 1, arq);
    fread(&(registro->prox), sizeof(int), 1, arq);


    if(registro->rem == '1' ){
        fseek(arq, tamRegistro-5, SEEK_CUR); // Move ponteiro do arquivo para o próximo registro
        return 1;
    }
    
    /*   #   Leituras dos Campos do Registro    # */

    /* Campos de tamanho fixo */
    fread(&(registro->codEstacao), sizeof(int), 1, arq);
    fread(&(registro->codLinha), sizeof(int), 1, arq); 
    fread(&(registro->codProxEstacao), sizeof(int), 1, arq);
    fread(&(registro->distProxEstacao), sizeof(int), 1, arq);
    fread(&(registro->codLinhaInteg), sizeof(int), 1, arq);
    fread(&(registro->codEstacaoInteg), sizeof(int), 1, arq);


    /*# Para cada um dos campos de tamanho variável:
        1) Lê o especificador de tamanho;
        2) Aloca dinâmicamente um vetor do tamanho especificado no registro;
        3) Lê campo de tamanho variável e salva no vetor dinâmico;
        4) Copia conteúdo do vetor dinâmico no respectivo campo do registro; */

    fread(&(registro->tamNomeEstacao), sizeof(int), 1, arq);
    
    char *aux = malloc(sizeof(char)*(registro->tamNomeEstacao+1)); if(!aux) exit(0);
    fread(aux, sizeof(char), registro->tamNomeEstacao, arq);

    aux[registro->tamNomeEstacao] = '\0';   // Adiciona '\0' no fim da string para que a função strcpy funcione
    strcpy(registro->nomeEstacao, aux);

    free(aux);


    fread(&(registro->tamNomeLinha), sizeof(int), 1, arq);
    
    if (registro->tamNomeLinha > 0){        // Nome Linha pode ser nulo -> tamNomeLinha == 0
        char *aux = malloc(sizeof(char)*(registro->tamNomeLinha+1)); if(!aux) exit(0);
        fread(aux, sizeof(char), registro->tamNomeLinha, arq);

        aux[registro->tamNomeLinha] = '\0';
        strcpy(registro->nomeLinha, aux);

        free(aux);
    }
    
    /*   #   Tratamento do Lixo    # 
    
     1) Calcula a quantidade de lixo: tamanho do registro - bytes utilizados
     2) Move o ponteiro com fseek para o inicio do próximo registro*/

    int qtdBytesLixo = tamRegistro - (bytesFixos + registro->tamNomeEstacao + registro->tamNomeLinha);
    fseek(arq, qtdBytesLixo, SEEK_CUR);

    return 0;
}

void lerCabecalho(FILE *arq, header *cabecalho){
    verificarArq(arq);
    verificarHeader(cabecalho);

    // Garante que está no começo do arquivo
    fseek(arq, 0, SEEK_SET);

    fread(&(cabecalho->status), sizeof(char), 1, arq);

    // Finaliza o programa se o arquivo for inconsistente
    if(cabecalho->status == '0'){
        printf("Falha no processamento do arquivo.");
        exit(0);
    }

    // Lê e guarda os campos do cabecalho
    fread(&(cabecalho->topo), sizeof(int), 1, arq);
    fread(&(cabecalho->proxRRN), sizeof(int), 1, arq);
    fread(&(cabecalho->totalEstacoes), sizeof(int), 1, arq);
    fread(&(cabecalho->totalPares), sizeof(int), 1, arq);
}

void lerCabecalhoIndex(FILE *arq, headerIndex *cabecalho){
    verificarArq(arq);
    if(!cabecalho) exit(0);

    // Garante que está no começo do arquivo
    fseek(arq, 0, SEEK_SET);

    fread(&(cabecalho->status), sizeof(char), 1, arq);

    if(cabecalho->status == inconsistente){
        printf("Falha no processamento do arquivo.");
        exit(0);
    }
}