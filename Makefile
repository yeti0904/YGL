SRC   = $(wildcard source/*.c)
DEPS  = $(wildcard source/*.h)
OBJ   = $(addsuffix .o,$(subst source/,bin/,$(basename ${SRC})))
LIBS  = -lSDL2 -lm
FLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -g -DYGL_USE_SDL -Ofast

compile: ./bin $(OBJ) $(SRC) $(DEPS)
	ar rcs libygl.a bin/*.o

./bin:
	mkdir -p bin

bin/%.o: source/%.c $(DEPS)
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm bin/*.o libygl.a

