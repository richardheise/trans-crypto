// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

// Este código foi *fortemente* inspirado em https://rosettacode.org/wiki/UTF-8_encode_and_decode#C

#include "cipher.h"

typedef struct {
    char mask;
    char lead;
    uint32_t beg;
    uint32_t end;
    int bits_stored;
} utf_info_t;

static utf_info_t* UTF_INFO[] = {
    [0] = &(utf_info_t){0b00111111, 0b10000000, 0, 0, 6},
    [1] = &(utf_info_t){0b01111111, 0b00000000, 0000, 0177, 7},
    [2] = &(utf_info_t){0b00011111, 0b11000000, 0200, 03777, 5},
    [3] = &(utf_info_t){0b00001111, 0b11100000, 04000, 0177777, 4},
    [4] = &(utf_info_t){0b00000111, 0b11110000, 0200000, 04177777, 3},
    &(utf_info_t){0},
};

int utf32_len(const uint32_t c) {
    int len = 0;
    for (utf_info_t** p = UTF_INFO; *p; ++p) {
        if (c >= (*p)->beg && c <= (*p)->end) {
            break;
        }
        ++len;
    }
    if (len > 4) exit(1);
    return len;
}

int utf8_len(const char c) {
    int len = 0;
    for (utf_info_t** p = UTF_INFO; *p; ++p) {
        if ((c & ~(*p)->mask) == (*p)->lead) {
            break;
        }
        ++len;
    }
    if (len > 4) exit(1);
    return len;
}

char* to_utf8(const uint32_t c) {
    static char ret[5];
    const int bytes = utf32_len(c);

    int shift = UTF_INFO[0]->bits_stored * (bytes - 1);
    ret[0] = (c >> shift & UTF_INFO[bytes]->mask) | UTF_INFO[bytes]->lead;
    shift -= UTF_INFO[0]->bits_stored;
    for (int i = 1; i < bytes; ++i) {
        ret[i] = (c >> shift & UTF_INFO[0]->mask) | UTF_INFO[0]->lead;
        shift -= UTF_INFO[0]->bits_stored;
    }
    ret[bytes] = '\0';
    return ret;
}

uint32_t to_utf32(const char* c) {
    int bytes = utf8_len(*c);
    int shift = UTF_INFO[0]->bits_stored * (bytes - 1);
    uint32_t codep = (*c++ & UTF_INFO[bytes]->mask) << shift;

    for (int i = 1; i < bytes; ++i, ++c) {
        shift -= UTF_INFO[0]->bits_stored;
        codep |= ((*c) & UTF_INFO[0]->mask) << shift;
    }

    return codep;
}

uint32_t* transpose(uint32_t* text, int* size) {
    // Adiciona caracteres para formar uma matriz quadrada.
    switch ((*size) % 4) {
        case 1:
            text[(*size)++] = '~';
        case 2:
            text[(*size)++] = '~';
        case 3:
            text[(*size)++] = '~';
        default:
            break;
    }

    uint32_t* transposed_array = calloc(*size, sizeof(uint32_t));
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j + i < *size; j += 4) {
            transposed_array[k++] = text[j + i];
        }
    }

    uint32_t* shifted_array = calloc(*size, sizeof(uint32_t));
    int shift_amount = (*size) / 4;
    for (int i = 0; i < *size; i++) {
        shifted_array[i] = transposed_array[(i + shift_amount) % *size];
    }

    free(transposed_array);
    return shifted_array;
}

uint32_t* detranspose(uint32_t* text, int* size) {
    uint32_t* unshifted_array = calloc(*size, sizeof(uint32_t));
    int shift_amount = *size / 4;
    int j = *size - shift_amount;
    for (int i = 0; i < *size; i++) {
        unshifted_array[i] = text[j % *size];
        j++;
    }

    uint32_t* detransposed_array = calloc(*size, sizeof(uint32_t));
    int k = 0;
    for (int i = 0; i < shift_amount; i++) {
        for (int j = 0; j + i < *size; j += shift_amount) {
            detransposed_array[k++] = unshifted_array[j + i];
        }
    }

    // Remove os caracteres '~' e ajusta o tamanho.
    int current_size = *size;
    *size = 0;
    for (int i = 0; i < current_size; i++) {
        if (detransposed_array[i] != '~') {
            detransposed_array[*size] = detransposed_array[i];
            (*size)++;
        }
    }
    
    free(unshifted_array);
    return detransposed_array;
}

uint32_t* read_text(int* size) {
    uint32_t* text_utf32 = malloc(sizeof(uint32_t) * MAX_BUFFER_SIZE);
    unsigned char buffer[MAX_BUFFER_SIZE];
    fgets((char*)buffer, MAX_BUFFER_SIZE - 1, stdin);

    unsigned char* in = buffer;
    for (size_t i = 0; i < strlen((char*)buffer) - 1; i++) {
        text_utf32[(*size)++] = to_utf32((char*)in);
        in += utf8_len(*in);
    }

    return text_utf32;
}
