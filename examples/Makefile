src  = $(wildcard ./*.c)
prog = $(subst ./,bin/,$(basename $(src)))
arg  = -g -Wall -pedantic -O3 -I../source
lib  = ../libygl.a -lSDL2 -lm

all: $(prog)

$(prog): bin/% : ./%.c
	mkdir -p bin
	$(CC) $(arg) -o $@ $< $(lib)

clean:
	rm -r bin
