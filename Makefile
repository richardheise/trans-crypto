# Dante Eleutério dos Santos (GRR20206686)
# Richard Fernando Heise Ferreira (GRR20191053)

CFLAGS  = -Wextra
CC = gcc

#-----------------------------------------------------------------------------#

all : lingxing

encrypt: lingxing
	./lingxing -c

decrypt: lingxing
	./lingxing -d

lingxing: lingxing.o crypt.o

#-----------------------------------------------------------------------------#

clean :
	$(RM) *.o

#-----------------------------------------------------------------------------#

purge:
	$(RM) lingxing *.o