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
    uint32_t* key = alloca(sizeof(uint32_t) * MAX_ALLOC);
    uint32_t* inputUTF32 = alloca(sizeof(uint32_t) * MAX_ALLOC);

    // Generating key
    // key = generateKey();

    int inputSize = 0;

    // Reading from stdin
    inputUTF32 = readText(&inputSize);

    // Encrypting/Decrypting

    char encrypt = !strcmp(argv[1], "-c");

    if (encrypt) {
        inputUTF32 = transpose(inputUTF32, &inputSize);
    } else {
        inputUTF32 = detranspose(inputUTF32, inputSize);
    }

    for (int i = 0; i < inputSize; i++) {
        if (encrypt) { // If it's encryption

            // Sum to UTF-32 so the text becomes "japanese"
            inputUTF32[i] += (0x6122);
        } else {

            // Subtraction from UTF-32 so the text is not "japanese" anymore
            inputUTF32[i] -= (0x6122);
        }
    }

    // Prints output in UTF-8 so terminal can understand it
    for (int i = 0; i < inputSize; i++) {
        printf("%s", to_utf8(inputUTF32[i]));
    }
    printf("\n");

    return 0;
}