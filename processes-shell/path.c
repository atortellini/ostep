#include "path.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATHS 3


void initializePath(struct Path *pth, char const *default_path) {
	if (pth == NULL) return;
	pth->path_arr = (char **)malloc(sizeof(char *) * MAX_PATHS);

	if (pth->path_arr == NULL) {
		fprintf(stderr, "Malloc failed to create path arr.\n");
		return;
	}
	char *dflt = strdup(default_path);
	if (dflt == NULL) {
		fprintf(stderr, "Failed to dup default path.\n");
		return;
	}
	pth->path_arr[0] = dflt;
	pth->num_paths = 1;
	pth->max_paths = MAX_PATHS;
}

void clearPath(struct Path *pth) {
	if (pth == NULL) return;

	for (unsigned i=0;i<pth->num_paths;i++) {
		free(pth->path_arr[i]);
		pth->path_arr[i] = NULL;
	}
	pth->num_paths = 0;
}



static void expandPaths(struct Path *pth, unsigned num_new_paths) {
	if (pth == NULL) return;
	unsigned new_size = (num_new_paths + (MAX_PATHS - num_new_paths%MAX_PATHS));
	pth->path_arr = realloc(pth->path_arr, sizeof(char *) * new_size);
	if (pth->path_arr == NULL) {
		fprintf(stderr, "Realloc failed to increase path arr.\n");
		return;
	}
	pth->max_paths = new_size;

}

void setPath(struct Path *pth, char **paths, unsigned num_new_paths) {
	if (pth->num_paths) clearPath(pth);
	if (num_new_paths > pth->max_paths) {
		expandPaths(pth, num_new_paths);
	}
	char *temp;
	for (unsigned i=0;i<num_new_paths;i++) {
		temp = strdup(paths[i]);
		if (temp == NULL) {
			fprintf(stderr, "Failed to dup new path.\n");
			return;
		}
		pth->path_arr[i] = temp;
	}
	pth->num_paths = num_new_paths;
}


