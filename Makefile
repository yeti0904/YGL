SRC      = $(wildcard source/*.c) $(wildcard source/**/*.c)
DEPS     = $(wildcard source/*.h) $(wildcard source/**/*.h)
OBJ      = $(addsuffix .o,$(subst source/,bin/,$(basename ${SRC})))
BIN_DIRS = $(subst source/,bin/,$(sort $(dir $(wildcard source/*/))))
LIBS     = -lm
FLAGS    = -std=c99 -Wall -Wextra -Werror -pedantic -g -Ofast

ifeq ($(backend), SDL)
	FLAGS += -DYGL_USE_SDL
	LIBS  += -lSDL2
endif
ifeq ($(backend), SDL1)
	FLAGS += -DYGL_USE_SDL1
	LIBS  += -lSDL
endif
ifeq ($(backend), custom)
	FLAGS += -DYGL_CUSTOM_BACKEND_COMPONENTS
endif

compile: ./bin $(BIN_DIRS) $(OBJ) $(SRC) $(DEPS)
	ar rcs libygl.a bin/*.o bin/**/*.o

./bin:
	mkdir -p bin

bin/%/:
	mkdir -p $@

bin/%.o: source/%.c $(DEPS)
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm bin/*.o libygl.a

