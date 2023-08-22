SRC   = $(wildcard source/*.c)
DEPS  = $(wildcard source/*.h)
OBJ   = $(addsuffix .o,$(subst source/,bin/,$(basename ${SRC})))
LIBS  = -lm
FLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -g -Ofast

ifeq ($(backend), SDL)
	FLAGS += -DYGL_USE_SDL
	LIBS  += -lSDL2
endif
ifeq ($(backend), SDL1)
	FLAGS += -DYGL_USE_SDL1
	LIBS  += -lSDL
endif

compile: ./bin $(OBJ) $(SRC) $(DEPS)
	ar rcs libygl.a bin/*.o

./bin:
	mkdir -p bin

bin/%.o: source/%.c $(DEPS)
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm bin/*.o libygl.a

