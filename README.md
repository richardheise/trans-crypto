# Cifra de Transposição e Ofuscação

Este repositório contém um programa em C que cifrar e decifrar textos usando uma cifra de transposição em matriz 4x4 e ofuscação de caracteres, deslocando-os para o bloco de caracteres chineses, japoneses e coreanos (CJK).

## Autores

*   Dante Eleutério dos Santos (GRR20206686)
*   Richard Fernando Heise Ferreira (GRR20191053)

## Funcionalidades

O programa oferece as seguintes funcionalidades:

*   **Cifragem de texto**: Transforma um texto em um formato ilegível.
*   **Decifragem de texto**: Reverte o texto cifrado para o seu formato original.
*   **Suporte a UTF-8**: O programa consegue lidar com caracteres UTF-8, permitindo o uso de acentos e outros símbolos.

## Como usar

Para compilar o programa, basta executar o comando `make`:

```bash
make
```

Isso irá gerar o executável `lingxing`.

### Cifrar

Para cifrar um texto, utilize a opção `-c`. O programa lerá o texto da entrada padrão (stdin).

```bash
echo "texto a ser cifrado" | ./lingxing -c
```

### Decifrar

Para decifrar um texto, utilize a opção `-d`.

```bash
echo "texto a ser decifrado" | ./lingxing -d
```

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

*   `include/`: Contém os arquivos de cabeçalho.
    *   `cipher.h`: Define as funções para a cifra, conversão de UTF e leitura de texto.
*   `src/`: Contém os arquivos de código fonte.
    *   `cipher.c`: Implementa a cifra de transposição, conversão de UTF e outras funções.
    *   `main.c`: Contém a função principal que lida com os argumentos da linha de comando e o fluxo de cifragem/decifragem.
*   `Makefile`: Arquivo de compilação do projeto.
*   `README.md`: Este arquivo.
