cc = g++
headers = -Iheaders
CFLAGS = -Wall -g
SFFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

objdir = obj
OBJ = main.o Graph.o Vertex.o Edge.o GraphDrawer.o Station.o ThickLine.o Button.o ButtonColor.o ButtonTexture.o
_OBJ = $(patsubst %,$(objdir)/%,$(OBJ))


all: $(_OBJ)
	$(cc) $(headers) $(CFLAGS) $(SFFLAGS) $(_OBJ) -o MetroFinder
	./MetroFinder

$(objdir)/%.o: src/%.cpp
	$(cc) -c $(headers) $(CFLAGS)  $(SFFLAGS) $< -o $@	

clear:
	rm obj/*
	rm MetroFinder