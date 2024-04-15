#include <stdio.h>
#include <stdlib.h>

void printCharTimes(const char c, int num_times) {
	while (num_times--) {
		printf("%c", c);
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}


	int count;
	char c;
	size_t char_read, count_read;
	const char *filename;
	FILE *fp;

	for (int i=1;i<argc;i++) {
		filename = argv[i];
		fp = fopen(filename, "r");
		if (fp == NULL) {
			printf("wunzip: unable to open file\n");
			exit(1);
		}
		do {
			count_read = fread(&count, sizeof(int), 1, fp);
			if (count_read) {
				char_read = fread(&c, sizeof(char), 1, fp);
				if (char_read) {
					printCharTimes(c, count);
				}
			}
		} while (count_read && char_read);

	}
	return 0;

}
