
FLAGS= -Wall -Wextra -fsanitize=address,undefined -g
SRC = $(wildcard src/*.c)
SRC += external/list/list.c
OBJ = $(SRC:src/%.c=build/obj/%.o)

compile: $(OBJ)
	mkdir -p build
	gcc $(FLAGS) -o build/build $^ test.c

run:
	./build/build

clean : 
	rm -rf build

build/obj/%.o:src/%.c
	mkdir -p build/obj
	gcc $(FLAGS) -c -o $@ $<
