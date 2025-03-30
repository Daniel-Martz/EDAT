CC = gcc
CFLAGS = -Wall -pedantic -ansi

OBJ_A = p3_e1.o vertex.o delivery.o
EJS = p3_e1

all: $(EJS)

p3_e1: $(OBJ_A)
	$(CC) -o $@ $^ -L. -lqueue

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

delivery.o: delivery.c delivery.h types.h queue.h
	$(CC) $(CFLAGS) -c -o $@ $<

p3_e1.o: p3_e1.c delivery.h types.h queue.h vertex.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_A) $(EJS)

.PHONY: all clean
