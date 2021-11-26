CCFLAG := -std=c++11

main: main.o
	g++ -o main $(CCFLAG) main.o
main.o: main.cpp
	g++ -o main.o -c $(CCFLAG) main.cpp
clean:
	rm -rf main.o main