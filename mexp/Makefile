all: mexp

mexp: mexp.c
	gcc -Wall -Werror -fsanitize=address mexp\.c -o mexp

clean:
	rm -rf mexp
