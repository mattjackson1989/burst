#

CC = gcc

SOURCES = burst.c 
OBJECTS = $(SOURCES:.c=.o)
TARGET = burst *.txt.

all:
	gcc -pthread -o burst burst.c 

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
