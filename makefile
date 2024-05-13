CC=gcc
CFLAGS=-Wall -Werror -pedantic --std=c17
OBJS=qdme.o
SRCS=qdme.c
TARGET=qdme

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $@ $<

all: $(TARGET)

debug: $(SRCS)
	$(CC) $(CFLAGS) -g -o $(TARGET) $^

mips: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJS)
