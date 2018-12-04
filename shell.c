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

int trim(char* source, int length) {
    int first_idx = 0;
    int last_idx = length - 1;
    int length_source = length;

    char at_index = source[first_idx];
    while(first_idx < length_source  && (at_index == ' ' || at_index == '\t' || at_index == '\n')) {
       first_idx++;
       at_index = source[first_idx];
    }

    at_index = source[last_idx];
    while(last_idx >= 0 && (at_index == ' ' || at_index == '\t' || at_index == '\n')) {
        last_idx--;
        at_index = source[last_idx];
    }

    for (int i = 0; i < last_idx - first_idx + 1; i++) {
      source[i] = source[i + first_idx];
    }

    source[last_idx - first_idx + 1] = 0;
    return last_idx - first_idx + 1;
}

int strip_chars(char* source, int length) {
  int idx_source = 0;
  int idx_result = 0;
  int length_source = length;
  int result_length = 0;
  char at_index = source[idx_source];

  while (idx_source < length_source) {
    at_index = source[idx_source];
    if (at_index == ' ' || at_index == '\t' || at_index == '\n') {
        source[idx_result] = at_index;
        idx_source++;
        idx_result++;
        result_length++;

        if (idx_source >= length_source) {
            break;
        }

        at_index = source[idx_source];
    }

    while (at_index == ' ' || at_index == '\t' || at_index == '\n') {
      idx_source++;
      at_index = source[idx_source];
    }

    source[idx_result] = at_index;
    idx_source++;
    idx_result++;
    result_length++;
  }

  source[idx_result] = 0;
  return result_length;
}

/*
	STATE 1: While reading \t, \n \s skip ahead.
	STATE 2:
*/


void write_prompt() {
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

		printf("read input: %s\n", buffer);

		strncpy(clean_input, buffer, bytes_read);

		int new_length = trim(clean_input, bytes_read);
		new_length = strip_chars(clean_input, new_length);

		printf("After stripping: >>%s<<\n", clean_input);

		int input_type = parse_input(clean_input, strlen(clean_input));
		if (input_type == EXIT_CMD) {
			exit(0);
		}
	}

	return 0;
}