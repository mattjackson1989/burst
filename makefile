#

CC = gcc

SOURCES = burst.c 
OBJECTS = $(SOURCES:.c=.o)
TARGET = burst outputfile.txt

all:
	gcc burst.c -o burst 

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
