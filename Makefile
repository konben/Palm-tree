# Compiler
CC := gcc

.PHONY: clean

palm_tree: palm_tree.c
	$(CC) -o palm_tree palm_tree.c

clean:
	rm palm_tree
