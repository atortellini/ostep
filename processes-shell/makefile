# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror

# Directories
SRCDIR = src
BUILDDIR = build
INCLUDEDIR = $(SRCDIR)


SRCS = $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)

OBJS = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

TARGET = wish

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@


clean:
	rm -rf $(BUILDDIR)/* $(TARGET)