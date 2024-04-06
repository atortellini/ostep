#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int num_files = argc - 1;
	if (num_files == 0) return 0;
	

	char buffer[100];

	for (int i=1;i<=num_files;i++) {
		char *file_name = argv[i];
		
		FILE *fp = fopen(file_name, "r");
		if (fp == NULL) {
			printf("wcat: cannot open file\n");
			exit(1);
		}
		
		while (fgets(buffer, 100, fp) != NULL) {
			printf("%s", buffer);
		}
	}

	return 0;
}
