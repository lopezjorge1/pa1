all: yell

yell: yell.c
	gcc -Wall -Werror -fsanitize=address yell\.c -o yell
	
clean:
	rm -rf yell
