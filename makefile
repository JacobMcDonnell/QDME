CC=gcc
CFLAGS=-Wall -Werror -pedantic --std=c17
OBJS=mips.o
TARGET=mips

%.o: %.c
	$(CC) $(CFLAGS) -c $@ $^

all: $(TARGET)

mips: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

