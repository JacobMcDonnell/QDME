CC=gcc
CFLAGS=-Wall -Werror -pedantic --std=c17
OBJS=qdme.o
TARGET=qdme

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $@ $<

all: $(TARGET)

mips: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET)
