all: rle

rle: rle.c
	gcc -Wall -Werror -fsanitize=address rle\.c -o rle

clean:
	rm -rf rle
