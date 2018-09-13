#compiler variable
CC=g++ -std=c++14

#compiler flags
CFLAGS=-Wall -I. -c -g -O3

all: PA9

OBJ= PA9.o stemmer.o main.o exceptions.o similarities.o

PA9: $(OBJ)
	$(CC) -o PA9 PA9.o main.o stemmer.o exceptions.o similarities.o

main.o: main.cpp PA9.h stemmer.h exceptions.h similarities.h
	$(CC) $(CFLAGS) main.cpp

PA9.o: PA9.cpp PA9.h
	$(CC) $(CFLAGS) PA9.cpp
	
stemmer.o: stemmer.cpp stemmer.h
	$(CC) $(CFLAGS) stemmer.cpp
	
exceptions.o: exceptions.cpp exceptions.h
	$(CC) $(CFLAGS) exceptions.cpp
	
similarities.o: similarities.cpp similarities.h
	$(CC) $(CFLAGS) similarities.cpp
	
clean:
	rm *.o PA9
	
