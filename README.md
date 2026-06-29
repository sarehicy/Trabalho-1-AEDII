# 📂Trabalho-1-AEDII

Sistema de manipulação de arquivos desenvolvido para a disciplina de Algoritmos e Estruturas de Dados II, aplicando conceitos de registros de dados de tamanho fixo e abordagem dinâmica de inserção e remoção de registros.

<br>

## Descrição do projeto

* Neste projeto são manipulados **registros de um arquivo binário** que representam as estações de um metrô. Chamaremos este arquivo de Estacoes.bin.
* Este é o principal arquivo deste projeto, e é sobre ele que são realizadas todas as funcionalidades do sistema. Ele é composto de dois tipos de registros, um para seu cabeçalho e um para as estações.
* Campos do registro de cabeçalho:
  ```
    char status;            // 1 - Consistente | 0 - Inconsistente
    int topo;               // Byteoffset do último registro removido | -1 default
    int proxRRN;            // Próximo RRN disponível
    int totalEstacoes;      // Quantidade de estações diferentes 
   int totalPares;         // Quantidade de pares (codEstacao, codProxEstacao) diferentes
  ```
* Campos do registro de estações:
  ```
    char rem;               // 1 - Removido | 0 - Não Removido
    int prox;               //RRN do prox elemento removido | -1 - Default

    int codEstacao;         
    int codLinha;
    int codProxEstacao;
    int distProxEstacao;
    int codLinhaInteg;
    int codEstacaoInteg;
    
    int tamNomeEstacao;     // Indica o tamanho da string de tamanho variavel "nomeEstacao"
    char nomeEstacao[100];
    int tamNomeLinha;       // Indica o tamanho da string de tamanho variavel "nomeLinha"
    char nomeLinha[100];
  ```

  
* Além do arquivo Estacoes.bin, o sistema também manipula um arquivo binário Estacoes_Indice.bin. Cada registro deste arquivo também representa uma estação, mas contem apenas o código da estação e RRN dentro do arquivo Estacoes.bin
* Para a manipulação dos registros foram desenvovidas 9 funcionalidades, que serão descritas futuramente.

## 🧑🏿‍💻 Operação do sistema
* Para utilizar as funcionalidades do sistema, o usuário deve primeiro escolher uma especificando seu número.
* Toda operação manipula arquivos locais, portanto o usuário deve fornecer o nome dos arquivos que ele deseja manipular.
* Cada operação precisa de arquivos específicos e pode ainda precisar de outros dados, quanto a isso iremos ser mais específicos na próxima seção.
 

<br>

## 🖥️ Funcionalidades
### 1. Criar arquivo binário
* A funcionalidade lê e processa as estações fornecidas por um arquivo.csv transformando-as em registros de dados que são escritos em um arquivo binário.
* Esta funcionalidade cria o arquivo Estacoes.bin
<br>

### 2. Imprimir registros
* A funcionaldiade lê e processa todos os registros de arquivo binário e imprime-os na saída padrão.
<br>

### 3. Busca de registros por campo
* Esta funcionalidade recupera todos os registros no arquivo binário que correspondam a um determinado critério de busca.
<br>

### 4. Busca de registro por RRN

### 5. Criação de um arquivo índice

### 6. Busca por campo com busca indexada

### 7. Remoção de registros

### 8. Inserção de registro

### 9. Atualização de campos de registro
