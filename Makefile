CC = gcc
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = 

obj/%.o: src/%.c headers/aocutils.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

day1: obj/day1.o obj/aocutils.o
	mkdir -p exec
	$(CC) $^ -o exec/$(notdir $@)

clean:
	rm -rf ./obj/*.o