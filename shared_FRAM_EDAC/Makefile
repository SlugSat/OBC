CC = gcc
TARGET = edac
CFLAGS = -std=c99 -Wall -g
DEPS = hamming.h edac.h
OBJ = main.o edac.o hamming.o

%.o: %.c $(DEPS)
	${CC} -c -o $@ $< ${CFLAGS}

${TARGET}: ${OBJ}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm ${OBJ}

mclean:
	rm ${OBJ} ${TARGET}
