CC = gcc
CFLAGS = -g -Wall
#-Wextra -Werror

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
HDR=$(wildcard *.h)
PROG = program

all: $(PROG)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(PROG): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(PROG) $(OBJ_FILES) 