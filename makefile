SFFLAGS = -g -Wall -Werror -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio


all: ThickLine.o
	g++ -c -o main.o $(SFFLAGS) main.cpp
	g++ -o sfml $(SFFLAGS) main.o ThickLine.o
	./sfml


main.o: main.cpp ThickLine.cpp ThickLine.hpp
	g++ -c -o main.o $(SFFLAGS) main.cpp


ThickLine.o: ThickLine.cpp ThickLine.hpp
	g++ -c -o ThickLine.o $(SFFLAGS) ThickLine.cpp 


clear:
	rm sfml
	rm *.o