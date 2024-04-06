SRCS = wcat.c

TARG = wcat

CC = gcc
OPTS = -Wall -Wextra -Werror -Wpedantic

OBJS = $(SRCS:.c=.o)

all : $(TARG)

$(TARG) : $(OBJS)
	$(CC) -o $(TARG) $(OBJS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARG)
