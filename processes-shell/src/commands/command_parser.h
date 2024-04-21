#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdio.h>

int parser(struct Queue_Manager *qmanager, char **line_buff, size_t *lbuff_size, FILE *restrict fp, char **file_out);

#endif
