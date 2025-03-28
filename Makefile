CC = gcc
CFLAGS = -Wall -pedantic -ansi

OBJ_A = p2_e1a.o 
OBJ_B = p2_e1b.o vertex.o
OBJ_C = p2_e2.o vertex.o graph.o
EJS = p2_e1a p2_e1b p2_e2 p2_e1a_bis p2_e1b_bis p2_e2_bis




all: $(EJS)

p2_e1a: $(OBJ_A)
	$(CC) -o $@ $^ -L. -lstack

p2_e1b: $(OBJ_B)
	$(CC) -o $@ $^ -L. -lstack

p2_e2: $(OBJ_C)
	$(CC) -o $@ $^ -L. -lstack


p2_e1a_bis: $(OBJ_A) stack.o
	$(CC) -o $@ $^

p2_e1b_bis: $(OBJ_A) stack.o
	$(CC) -o $@ $^

p2_e2_bis: $(OBJ_A) stack.o
	$(CC) -o $@ $^
	
	
p2_e1a.o: p2_e1a.c types.h stack.h file_utils.h
	$(CC) $(CFLAGS) -c -o $@ $<

p2_e1b.o: p2_e1b.c stack.h types.h file_utils.h vertex.h
	$(CC) $(CFLAGS) -c -o $@ $<

p2_e2.o: p2_e2.c graph.h vertex.h types.h stack.h
	$(CC) $(CFLAGS) -c -o $@ $<


vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

graph.o: graph.c graph.h vertex.h types.h stack.h
	$(CC) $(CFLAGS) -c -o $@ $<

stack.o: stack.c stack.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_A)$(OBJ_B) $(EJS)

.PHONY: all clean
