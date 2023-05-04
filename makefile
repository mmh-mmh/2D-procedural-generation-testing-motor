CC = gcc
CFLAGS = -lmenu -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c
all: valley

valley:	$(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./valley

clean:
	rm valley
