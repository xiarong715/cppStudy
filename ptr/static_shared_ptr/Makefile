CXXFLAGS = --std=c++11 -g3 -O0
static_shared_ptr : main.o
	g++ -o static_shared_ptr main.o $(CXXFLAGS)
main.o : main.cpp
	g++ -o main.o -c main.cpp $(CXXFLAGS)
clean :
	rm -rf main.o static_shared_ptr