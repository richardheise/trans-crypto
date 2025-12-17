// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

#include "cipher.h"
#include <alloca.h>

int main(int argc, char* argv[]) {
    // Verifica os argumentos de entrada.
    if (argc <= 1) {
        printf("Uso:\n  cifrar: %s -c\n  decifrar: %s -d\n", argv[0], argv[0]);
        return 1;
    }

    // Aloca memória para o texto de entrada.
    uint32_t* text_utf32 = alloca(sizeof(uint32_t) * MAX_BUFFER_SIZE);
    int text_size = 0;

    // Lê o texto do stdin.
    text_utf32 = read_text(&text_size);

    // Verifica se o modo é de cifragem ou decifragem.
    char is_encrypt_mode = !strcmp(argv[1], "-c");

    if (is_encrypt_mode) {
        // Cifra o texto.
        // Primeiro, transpõe o texto.
        text_utf32 = transpose(text_utf32, &text_size);

        // Adiciona um valor hexadecimal para mapear para o bloco "mandarim".
        for (int i = 0; i < text_size; i++) {
            text_utf32[i] += 0x6122;
        }
    } else {
        // Decifra o texto.
        // Ajusta o tamanho do texto, pois os caracteres "mandarim" ocupam mais bytes.
        text_size = text_size / 3;

        // Mapeia de volta do "mandarim" para o alfabeto original.
        for (int i = 0; i < text_size; i++) {
            text_utf32[i] -= 0x6122;
        }

        // Destranspõe o texto.
        text_utf32 = detranspose(text_utf32, &text_size);
    }

    // Imprime o resultado em UTF-8.
    for (int i = 0; i < text_size; i++) {
        printf("%s", to_utf8(text_utf32[i]));
    }
    printf("\n");

    return 0;
}
