CC=gcc
CFLAGS=-std=c99 -Wall
DEPS=state.h util.h 
OBJ=main.o state.o util.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm $(OBJ)

