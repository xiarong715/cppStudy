CXXFLAGS = -std=c++11 -lpthread -g3
shared_ptr: main.o
	g++ -o shared_ptr $(CXXFLAGS) main.o
main.o: main.cpp
	g++ -o main.o $(CXXFLAGS) -c main.cpp
clean: 
	rm -rf main.o shared_ptr