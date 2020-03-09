objets = main.o Graph.o Vertex.o Edge.o

all: $(objets)
	g++ $(objets)
	./a.out


main.o: main.cpp
	g++ -c -o main.o main.cpp


Graph.o: Graph.cpp Graph.h
	g++ -c -o Graph.o Graph.cpp


Vertex.o: Vertex.cpp Vertex.h
	g++ -c -o Vertex.o Vertex.cpp


Edge.o: Edge.cpp Edge.h
	g++ -c -o Edge.o Edge.cpp


clear:
	rm a.out
	rm *.o