CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJS_A = p4_e1.o vertex.o bstree.o
EJS = p4_e1

all: $(EJS)

p4_e1: $(OBJS_A)
	$(CC) -o $@ $^



p4_e1.o: p4_e1.c bstree.h types.h vertex.h
	$(CC) $(CFLAGS) -c -o $@ $<

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

bstree.o: bstree.c bstree.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f $(OBJS_A) $(EJS) *.o

.PHONY: clean

include Makefile_ext 
