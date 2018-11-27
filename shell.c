/*
	0) prints prompt
	1) reads input
	2) skips whitespaces and tabulations
	3) prints appropriate message on an invalid command
	4) exit command
	5) background mode
*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

# define BUFFER_SIZE 1024
# define EXIT_CMD 1
# define NOT_FOUND 0

char buffer[BUFFER_SIZE];


int read_input() {
	int bytes_read = read(1, buffer, BUFFER_SIZE);

	return bytes_read;
}


void write_prompt() {
	// printf ??
	write(0, ">>>", 3);
}

int parse_input(int bytes_read) {
	int cmpresult = strncmp("exit\n", buffer, bytes_read);
	if (cmpresult == 0) {
		return EXIT_CMD;
	}

	return NOT_FOUND;
}



int main() {
	while(1) {
		write_prompt();

		int bytes_read = read_input();

		printf("read input: %s", buffer);

		if (parse_input(bytes_read) == EXIT_CMD) {
			exit(0);
		}


	}

	return 0;
}