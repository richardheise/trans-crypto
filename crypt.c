// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

// THIS CODE IS *HEAVILY* INSPIRED BY https://rosettacode.org/wiki/UTF-8_encode_and_decode#C

#include "crypt.h"

typedef struct {
    char mask;    /* char data will be bitwise AND with this */
    char lead;    /* start bytes of current char in utf-8 encoded character */
    uint32_t beg; /* beginning of codepoint range */
    uint32_t end; /* end of codepoint range */
    int bits_stored; /* the number of bits from the codepoint that fits in char */
}utf_t;

utf_t* utf[] = {
    /*             mask        lead        beg      end       bits */
    [0] = &(utf_t){0b00111111, 0b10000000, 0,       0,        6    },
    [1] = &(utf_t){0b01111111, 0b00000000, 0000,    0177,     7    },
    [2] = &(utf_t){0b00011111, 0b11000000, 0200,    03777,    5    },
    [3] = &(utf_t){0b00001111, 0b11100000, 04000,   0177777,  4    },
    [4] = &(utf_t){0b00000111, 0b11110000, 0200000, 04177777, 3    },
    &(utf_t){0},
};

int utf32_len(const uint32_t utf32_char) {

    int len = 0;
    for(utf_t **char_p = utf; *char_p; ++char_p) {
        if((utf32_char >= (*char_p)->beg) && (utf32_char <= (*char_p)->end)) {
            break;
        }
        ++len;
    }
    if(len > 4) /* Out of bounds */
        exit(1);

    return len;
}

int utf8_len(const char utf8_char) {

    int len = 0;
    for(utf_t **char_p = utf; *char_p; ++char_p) {
        if((utf8_char & ~(*char_p)->mask) == (*char_p)->lead) {
            break;
        }
        ++len;
    }
    if(len > 4) { /* Malformed leading byte */
        exit(1);
    }
    return len;
}


char *to_utf8(const uint32_t utf32_char) {

    static char ret[5];
    const int bytes = utf32_len(utf32_char);

    int shift = utf[0]->bits_stored * (bytes - 1);
    ret[0] = (utf32_char >> shift & utf[bytes]->mask) | utf[bytes]->lead;
    shift -= utf[0]->bits_stored;
    for(int i = 1; i < bytes; ++i) {
        ret[i] = (utf32_char >> shift & utf[0]->mask) | utf[0]->lead;
        shift -= utf[0]->bits_stored;
    }
    ret[bytes] = '\0';
    return ret;
}


uint32_t to_utf32(const char chr[4]) {

    int bytes = utf8_len(*chr);
    int shift = utf[0]->bits_stored * (bytes - 1);
    uint32_t codep = (*chr++ & utf[bytes]->mask) << shift;

    for(int i = 1; i < bytes; ++i, ++chr) {
        shift -= utf[0]->bits_stored;
        codep |= ((char)*chr & utf[0]->mask) << shift;
    }

    return codep;
}

uint32_t* generateKey() {
    uint32_t* key = malloc(sizeof(uint32_t)*MAX_ALLOC);

    unsigned char date[10];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(date, "%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    unsigned char* in;
    int x = 0;
    for (in = date; *in != '\0'; in += utf8_len(*in)) {
        key[x++] = to_utf32(in);
    }

    return key;
}


uint32_t* transpose(uint32_t* input, int *size) {

    switch ((*size) % 4) {
        case 3:
            input[(*size)] = '~';
            input[(*size)+1] = '\0';
            (*size) += 1;
            break;
        case 2:
            input[(*size)] = '~';
            input[(*size)+1] = '~';
            input[(*size)+2] = '\0';
            (*size) += 2;
            break;
        case 1:
            input[(*size)] = '~';
            input[(*size)+1] = '~';
            input[(*size)+2] = '~';
            input[(*size)+3] = '\0';
            (*size) += 3;
            break;
        default:
            break;
    }

    uint32_t trans_array[MAX_ALLOC];

    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j+i < (*size); j += 4) {
            trans_array[k] = input[j+i];
            k++;
        }
    }

    uint32_t* shift_arr = calloc(MAX_ALLOC, sizeof(uint32_t));

    int shift_amount = (*size) / 4;
    for (int i = 0; i < (*size); i++) {
        shift_arr[i] = trans_array[((i + (shift_amount)) % (*size))];
    }

    return shift_arr;
}

uint32_t* detranspose(uint32_t* input, int (*size)) {


    uint32_t unshift_arr[MAX_ALLOC];

    int shift_amount = (*size) / 4;
    int j = (*size) - (shift_amount);

    for (int i = 0; i < (*size); i++) {
        unshift_arr[i] = input[j % (*size)];
        j++;
    }


    uint32_t* detrans_array = calloc(MAX_ALLOC, sizeof(uint32_t));

    int k = 0;
    for (int i = 0; i < shift_amount; i++) {
        for (int j = 0; j+i < (*size); j += (shift_amount)) {
            detrans_array[k] = unshift_arr[j+i];
            k++;
        }
    }

    for (int i = 0; i < (*size); i++) {
        if (detrans_array[i] == '~') {
            for(int j = i; j < (*size); j++) {
			    detrans_array[j] = detrans_array[j + 1];
            }
		(*size) -= 1;
		i -= 1;	
        }
    }

    return detrans_array;
}

uint32_t* readText(int* n) {
    uint32_t* inputUTF32 = malloc(sizeof(uint32_t) * MAX_ALLOC);
    unsigned char buffer[MAX_ALLOC];
    fgets(buffer, MAX_ALLOC-1, stdin);

    unsigned char* in = buffer;
    for (size_t i = 0; i != strlen(buffer) - 1; i++) {
        inputUTF32[(*n)++] = to_utf32(in);
        in += utf8_len(*in);
    }

    return inputUTF32;
}
