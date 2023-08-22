src  = $(wildcard ./*.c)
prog = $(subst ./,bin/,$(basename $(src)))
arg  = -g -Wall -pedantic -O3 -I../source
lib  = ../libygl.a -lSDL2 -lm -Ofast

ifeq ($(backend), SDL)
	arg += -DYGL_USE_SDL
	lib += -lSDL2
endif
ifeq ($(backend), SDL1)
	arg += -DYGL_USE_SDL1
	lib += -lSDL
endif

all: $(prog)

$(prog): bin/% : ./%.c
	mkdir -p bin
	$(CC) $(arg) -o $@ $< $(lib)

clean:
	rm -r bin
