cc = g++
headers = -Iheaders
CFLAGS = -Wall -g
SFFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

objdir = obj
OBJ = main.o Graph.o Vertex.o Edge.o GraphDrawer.o Station.o
_OBJ = $(patsubst %,$(objdir)/%,$(OBJ))


all: $(_OBJ)
	$(cc) $(headers) $(CFLAGS) $(SFFLAGS) $(_OBJ) -o MetroFinder
	./MetroFinder

$(objdir)/%.o: src/%.cpp
	$(cc) -c $(headers) $(CFLAGS)  $(SFFLAGS) $< -o $@	

clear:
	rm MetroFinder
	rm obj/*