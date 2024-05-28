CC=gcc
CFLAGS=-Wall -Werror -pedantic --std=c17
OBJS=qdme.o elf.o
SRCS=qdme.c elf.c
TARGET=qdme

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(TARGET)

debug: $(SRCS)
	$(CC) $(CFLAGS) -g -o $(TARGET) $^

qdme: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJS)
