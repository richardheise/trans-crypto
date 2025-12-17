// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

#ifndef __CIPHER__
#define __CIPHER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#define MAX_BUFFER_SIZE 500000

/* Todos os comprimentos estão em bytes */

// Calcula o número de bytes que um caractere UTF-32 ocupa em UTF-8.
// Recebe um caractere UTF-32.
// Retorna o número de bytes.
int utf32_len(const uint32_t c);

// Calcula o número de bytes de um caractere UTF-8.
// Recebe o primeiro byte de um caractere UTF-8.
// Retorna o número de bytes.
int utf8_len(const char c);

// Converte um caractere UTF-32 para uma string UTF-8.
// Recebe um caractere UTF-32.
// Retorna uma string com o caractere em UTF-8.
char* to_utf8(const uint32_t c);

// Converte um caractere UTF-8 para um caractere UTF-32.
// Recebe uma string com um caractere em UTF-8.
// Retorna o caractere em UTF-32.
uint32_t to_utf32(const char* c);

// Lê um texto do stdin e o converte para um array de UTF-32.
// Recebe um ponteiro para guardar o tamanho do texto.
// Retorna um ponteiro para o array com o texto em UTF-32.
uint32_t* read_text(int* size);

// Transpõe um array de caracteres UTF-32.
// Recebe um ponteiro para o array e um ponteiro para o seu tamanho.
// Retorna um ponteiro para o array transposto.
uint32_t* transpose(uint32_t* text, int* size);

// Destranspõe um array de caracteres UTF-32.
// Recebe um ponteiro para o array e um ponteiro para o seu tamanho.
// Retorna um ponteiro para o array destransposto.
uint32_t* detranspose(uint32_t* text, int* size);

#endif