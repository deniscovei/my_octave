# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)

build: $(OBJS)
	$(CC) $(CFLAGS) -o my_octave $(OBJS)

pack:
	zip -FSr 312CA_CoveiDenis_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS) $(OBJS)

.PHONY: pack clean
