#

CC = gcc

SOURCES = burst.c 
OBJECTS = $(SOURCES:.c=.o)
TARGET = burst

all:
	gcc burst.c -o burst 

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
