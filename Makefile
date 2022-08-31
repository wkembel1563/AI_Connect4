CXXFLAGS += --std=c++20

maxconnect4: maxconnect4.o main.o *.h 
	g++ maxconnect4.o main.o -o maxconnect4

maxconnect4.o: maxconnect4.cpp
	g++ -c maxconnect4.cpp -o maxconnect4.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm -f *.o *~ maxconnect4 a.out
