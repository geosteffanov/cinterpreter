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
# define COMMAND 2

char buffer[BUFFER_SIZE];
char clean_input[BUFFER_SIZE];

int read_input() {
	int bytes_read = read(1, buffer, BUFFER_SIZE);

	return bytes_read;
}

void strip_chars(char* source) {
	int idx_source = 0;
	int idx_result = 0;
	int length_source = strlen(source);

	while (idx_source < length_source) {
		char at_index = source[idx_source];
		if (at_index == ' ' || at_index == '\t' || at_index == '\n') {
		    source[idx_result] = at_index;
		    idx_source++;
		    idx_result++;
		}
		while (at_index == ' ' || at_index == '\t' || at_index == '\n') {
			idx_source++;
			at_index = source[idx_source];
		}

		source[idx_result] = at_index;
		idx_source++;
		idx_result++;
	}

	source[idx_result] = 0;
}

/*
	STATE 1: While reading \t, \n \s skip ahead.
	STATE 2:
*/


void write_prompt() {
	// printf ??
	write(0, ">>>", 3);
}

int parse_input(char* input, int length) {
	int cmpresult = strncmp("exit", input, length);
	if (cmpresult == 0) {
		return EXIT_CMD;
	}

	return COMMAND;
}

int main() {
	while(1) {
		write_prompt();

		int bytes_read = read_input();
		printf("read input: %s", buffer);


		strncpy(clean_input, buffer, bytes_read);
		printf("copied: %s\n", clean_input);
		strip_chars(clean_input);
		printf("After stripping: %s\n", clean_input);

		int input_type = parse_input(clean_input, strlen(clean_input));
		if (input_type == EXIT_CMD) {
			exit(0);
		}
	}

	return 0;
}