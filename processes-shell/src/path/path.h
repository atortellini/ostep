#ifndef PATH_H
#define PATH_H

struct Path {
	char **path_arr;
	unsigned num_paths;
	unsigned max_paths;
};


void initializePath(struct Path *pth, char const *default_path);

void clearPath(struct Path *pth); 

void setPath(struct Path *pth, char **paths, unsigned num_new_paths);

#endif
