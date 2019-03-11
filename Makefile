# Makefile boilerplate version 0.0.1 (20190204)

TARGET = bf-run

CC = gcc
LFLAGS = -L/usr/local/lib -lpotados

SOURCE = $(wildcard *.c)
OBJECT = $(SOURCE:.c=.o)

$(TARGET): $(OBJECT)
	$(LINK.c) -o $@ $^ $(LFLAGS)

# Object file wildcard rule.
%.o: %.c
	$(COMPILE.c) $<

clean:
	rm *.o $(TARGET)
