all: runpriv

runpriv: runpriv.o
	g++ runpriv.o -o runpriv

runpriv.o: runpriv.cpp
	g++ -c runpriv.cpp

clean:
	rm -rf *o runpriv          
