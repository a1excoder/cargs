CC = gcc
CFLAGS = -Wall --std=c99 -o0
ENDFILENAME = cargs_example
MAINFILE = example.c

build_first:
	$(CC) $(MAINFILE) $(CFLAGS) -o $(ENDFILENAME)
