cc = g++
CFLAGS = -Wall -g
SFFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

objdir = obj
graphdir = $(objdir)/Graph
graphicdir = $(objdir)/Graphics

headers = headers
graphheaders = $(headers)/Graph
graphicheaders = $(headers)/Graphics

src = src
graphsrc = $(src)/Graph
graphicsrc = $(src)/Graphics

GRAPHOBJ = Graph.o Vertex.o Edge.o
GRAPHICSOBJ = GraphDrawer.o Station.o ThickLine.o Button.o ButtonColor.o ButtonTexture.o MenuDrawer.o SearchBox.o
_GRAPH_OBJ = $(patsubst %,$(graphdir)/%,$(GRAPHOBJ))
_GRAPHICS_OBJ = $(patsubst %,$(graphicdir)/%,$(GRAPHICSOBJ))


run: MetroFinder
	./MetroFinder

MetroFinder: $(graphdir) $(graphicdir) $(_GRAPH_OBJ) $(_GRAPHICS_OBJ)
	$(cc) -I$(graphicheaders) -I$(graphheaders)  $(CFLAGS) $(SFFLAGS) src/main.cpp $(_GRAPH_OBJ) $(_GRAPHICS_OBJ) -o MetroFinder

$(graphdir)/%.o: $(graphsrc)/%.cpp $(graphheaders)/%.hpp
	$(cc) -c -I$(graphheaders) $(CFLAGS)  $< $2 -o $@

$(graphicdir)/%.o: $(graphicsrc)/%.cpp $(graphicheaders)/%.hpp
	$(cc) -c -I$(graphicheaders) -I$(graphheaders) $(CFLAGS)  $(SFFLAGS) $< $2 -o $@

$(graphdir) : $(objdir)
	mkdir $(graphdir)

$(graphicdir) : $(objdir)
	mkdir $(graphicdir)

$(objdir) :
	mkdir $(objdir)

clear:
	rm -rf obj
	rm MetroFinder