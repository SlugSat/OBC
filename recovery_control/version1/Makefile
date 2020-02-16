CC=gcc
CFLAGS=-std=c99 -Wall
DEPS=state.h arth.h
OBJ=main.o state.o arth.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm $(OBJ)

