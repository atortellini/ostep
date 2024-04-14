#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Returns length of string excluding null byte
int strLen(const char *str1) {
	int count = 0;
	while (*str1++ != '\0') {
		count++;
	}
	return count;
}

// Helper function for strContainsExpr
// Returns true if expr is contained within the rest of str1
bool compareStrs(const char *str1, const char *expr) {
	while (*str1 != '\0' && *expr != '\0') {
		if (*str1 != *expr) return false;
		str1++; expr++;
	}

	if (*expr == '\0') return true;			// If reached end of expr without returning false, str1 contains expr

	return false;					// Otherwise str1 reached end before expr, meaning it could not contain expr
}



// Returns true if expr found within str
bool strContainsExpr(const char *str, const char *expr) {
	int str_len = strLen(str), expr_len = strLen(expr);

	while (str_len > expr_len) {			// Guard to prevent unneccessary calls to compareStrs, otherwise impossible scenarios (like str_len < expr_len containing expr)
		if (*str == *expr) {			// would still result in call to compareStrs as long as *str == *expr
			if (compareStrs(str, expr))	
				return true;
			}
		str++; str_len--;
	}

	if (str_len < expr_len) return false;		// Not possible for str to contain expr

	if (str_len == expr_len) return compareStrs(str, expr);

	return false;
}


void processInput(const char *expr, char **buff, size_t *buff_size, FILE *fp) {
	while (getline(buff, buff_size, fp) != -1) {
		if (strContainsExpr(*buff, expr)) {
			printf("%s", *buff);
		}
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}


	const char *expr = argv[1];
	FILE *fp;
	char *buff = NULL;
	size_t buff_size;

	if (argc == 2) {
		fp = stdin;
		processInput(expr, &buff, &buff_size, fp);
	}

	else {
		for (int i = 2; i < argc; i++) {
			fp = fopen(argv[i], "r");
			if (fp == NULL) {
				printf("wgrep: cannot open file\n");
				exit(1);
			}
			processInput(expr, &buff, &buff_size, fp);
		}
			
	}
	free(buff);
	return 0;


}
