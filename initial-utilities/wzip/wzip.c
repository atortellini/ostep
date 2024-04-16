#include <stdio.h>
#include <stdlib.h>



int strLen(const char *str) {
	int count = 0;
	while (*str++ != '\0') {
		count++;
	}
	return count;
}



int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}

	const char *file_name;
	FILE *fp;
	char *line_buffer = NULL, *compare_char, carry_c = '\0';
	size_t buffer_size;
	int count = 0;
	for (int i = 1; i < argc; i++) {
		file_name = argv[i];
		fp = fopen(file_name, "r");
		if (fp == NULL) {
			printf("wzip: unable to open file\n");
			exit(1);
		}

		while (getline(&line_buffer, &buffer_size, fp) != -1) {
			compare_char = line_buffer;
			char c;
			if (carry_c != '\0') {
				c = carry_c;
			} else c = *compare_char;
		
			while (*compare_char != '\0') {
				if (c == *compare_char)
					count++;
				if (c != *compare_char) {
					fwrite(&count, sizeof(int), 1, stdout);
					fwrite(&c, sizeof(char), 1, stdout);
					c = *compare_char;
					count = 1;
				}
				compare_char++;
			}
			carry_c = c;
		}
	}

	fwrite(&count, sizeof(int), 1, stdout);
	fwrite(&carry_c, sizeof(char), 1, stdout);
	if (line_buffer != NULL) {
		free(line_buffer);
	}
	return 0;
}
