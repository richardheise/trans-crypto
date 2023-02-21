// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

#include "crypt.h"

int main(int argc, char* argv[]) {

    // Usage of inputs
    if (argc <= 1) {
        printf("Usage:\n  encrypting: %s -c\n  decrypting: %s -d\n", argv[0], argv[0]);
        return 1;
    }

    // Allocating arrays
    uint32_t* inputUTF32 = alloca(sizeof(uint32_t) * MAX_ALLOC);

    int inputSize = 0;

    // Reading from stdin
    inputUTF32 = readText(&inputSize);

    // Encrypting/Decrypting
    char encrypt = !strcmp(argv[1], "-c");

    // If we have to encrypt
    if (encrypt) {
        // First we transpose function
        inputUTF32 = transpose(inputUTF32, &inputSize);

        // Add Hex values so it becomes mapped for "mandarim"
        for (int i = 0; i < inputSize; i++) {
            inputUTF32[i] += (0x6122);
        }

    } else {
        // Since we are reading more bytes from the terminal, we have to adjust the input size
        inputSize = inputSize/3;

        // We map it back from "mandarim" to our alphabet
        for (int i = 0; i < inputSize; i++) {
            inputUTF32[i] -= (0x6122);
        }

        // Then we detranspose the encryption
        inputUTF32 = detranspose(inputUTF32, &inputSize);
    }

    // Prints output in UTF-8 so terminal can understand it
    for (int i = 0; i < inputSize; i++) {
        printf("%s", to_utf8(inputUTF32[i]));
    }
    printf("\n");

    return 0;
}