
FLAGS= -Wall -Wextra -fsanitize=address,undefined -g
SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=build/%.o)

compile:
	mkdir -p build/src
	make test

test:$(OBJ)
	gcc $(FLAGS) -o build/build $^ test.c

run:
	./build/build

clean : 
	rm -rf build

build/%.o:%.c
	gcc $(FLAGS) -c -o $@ $<
