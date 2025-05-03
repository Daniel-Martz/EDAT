CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
OBJS_A = p4_e1.o vertex.o bstree.o
OBJS_B = p4_e2.o vertex.o bstree.o search_queue.o file_utils.o
OBJS_C = p4_e3.o vertex.o bstree.o search_queue.o file_utils.o
EJS = p4_e1 p4_e2 p4_e3

all: $(EJS)

p4_e1: $(OBJS_A)
	$(CC) -o $@ $^

p4_e2: $(OBJS_B)
	$(CC) -o $@ $^

p4_e3: $(OBJS_C)
	$(CC) -o $@ $^

p4_e1.o: p4_e1.c bstree.h types.h vertex.h
	$(CC) $(CFLAGS) -c -o $@ $<

p4_e2.o: p4_e2.c bstree.h types.h vertex.h search_queue.h file_utils.h
	$(CC) $(CFLAGS) -c -o $@ $<

p4_e3.o: p4_e3.c bstree.h types.h vertex.h search_queue.h file_utils.h
	$(CC) $(CFLAGS) -c -o $@ $<

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

bstree.o: bstree.c bstree.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

search_queue.o: search_queue.c types.h bstree.h search_queue.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS_A)  $(OBJS_B) $(OBJS_C) $(EJS) *.o

.PHONY: clean

include Makefile_ext 
