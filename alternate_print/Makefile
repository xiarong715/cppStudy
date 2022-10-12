all: alternate_print
alternate_print: main.o
	g++ -o alternate_print main.o -lpthread

main.o: main.cpp
	g++ -c main.cpp -o main.o -lpthread

.PHONY: clean

clean:
	rm -rf main.o alternate_print