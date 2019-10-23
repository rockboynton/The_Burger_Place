CC=gcc
CFLAGS=-c -Wall -Wextra -g -00 -pthread -ggdb
LDFLAGS= -pthread -ggdb
SOURCES= burger_place.c ll.c main.c test_burger_place.c
OBJECTS=$(SOURCES: .c=.o)
EXECUTABLE=sim

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE) : $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 
	
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)