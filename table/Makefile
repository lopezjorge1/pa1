all: table

table: table.c

	gcc -Wall -Werror -fsanitize=address table\.c -o table

clean:

	rm -rf table
