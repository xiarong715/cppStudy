CXXFLAG = -std=c++11 -g3		# -glevel    -g equal -g2, The default level is 2
emplace_back: main.o
	g++ -o emplace_back main.o $(CXXFLAG)
main.o: main.cpp
	g++ -o main.o -c main.cpp $(CXXFLAG)
clean:
	rm -rf main.o emplace_back