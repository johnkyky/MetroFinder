cc = g++
headers = -Iheaders
CFLAGS = -Wall -g
SFFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

objdir = obj
OBJ = main.o Graph.o Vertex.o Edge.o
_OBJ = $(patsubst %,$(objdir)/%,$(OBJ))


all: $(_OBJ)
	$(cc) $(headers) $(CFLAGS) $(_OBJ) -o MetroFinder
	./MetroFinder

run:
	./MetroFinder

$(objdir)/%.o: src/%.cpp $(objdir)
	$(cc) -c $(headers) $(CFLAGS) $(SFFLAGS) $< -o $@	

$(objdir) :
	mkdir $(objdir)

clear:
	rm MetroFinder
	rm obj/*