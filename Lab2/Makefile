CC=g++
CFLAGS=-c -std=c++17 -g
LDFLAGS=-lncurses -ltinfo
SOURCES=main.cpp Coordinate.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=amazing

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:	
	rm -f *.o $(EXECUTABLE) 
	touch *
