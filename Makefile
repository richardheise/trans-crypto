# Autores:
# Dante Eleutério dos Santos (GRR20206686)
# Richard Fernando Heise Ferreira (GRR20191053)

CFLAGS = -Wextra
CC = gcc
RM = rm -f

#-----------------------------------------------------------------------------#

all: lingxing

encrypt: lingxing
	./lingxing -c

decrypt: lingxing
	./lingxing -d

lingxing: src/main.o src/cipher.o
	$(CC) $(CFLAGS) -o lingxing src/main.o src/cipher.o

src/main.o: src/main.c src/cipher.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/cipher.o: src/cipher.c src/cipher.h
	$(CC) $(CFLAGS) -c src/cipher.c -o src/cipher.o

#-----------------------------------------------------------------------------#

clean:
	$(RM) src/*.o

#-----------------------------------------------------------------------------#

purge: clean
	$(RM) lingxing
