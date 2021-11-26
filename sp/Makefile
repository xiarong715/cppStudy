CXXFLAGS := -std=c++11 -O0 -g3
main: main.o
	g++ -o main $(CXXFLAGS) main.o
main.o: main.cpp
	g++ -o main.o -c $(CXXFLAGS) main.cpp
clean:
	rm -rf main.o main