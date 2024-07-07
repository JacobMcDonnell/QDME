CC=gcc
CFLAGS=-Wall -Werror -pedantic --std=c17
OBJS=qdme.o elf.o instruction.o load.o
SRCS=qdme.c elf.c instruction.c load.c
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

