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
# define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];


int read_input() {
	int bytes_read = read(1, buffer, BUFFER_SIZE);

	return bytes_read;
}



int main() {
	while(1) {
		int bytes_read = read_input();

		printf("read input %s", buffer);
	}

	return 0;
}