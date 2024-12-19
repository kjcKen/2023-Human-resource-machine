main: main.cpp function.cpp function.o
	g++ main.cpp function.cpp function.o -o main

function.o: function.cpp function.h
	g++ -c function.cpp -o function.o

clean:
	rm -f main function.o