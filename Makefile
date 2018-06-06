all: runpriv

runpriv: runpriv.o
	g++ -std=c++11 runpriv.o -o runpriv

runpriv.o: runpriv.cpp
	g++ -std=c++11 -c runpriv.cpp

clean:
	rm -rf *o runpriv          
