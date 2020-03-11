#include "Graph.hpp"

Graph::Graph(std::string fileName)
{
	load_from_file(fileName);
}

Graph::Graph()
{

}


Graph::~Graph()
{
	 
}

int Graph::load_from_file(std::string fileName)
{
	std::ifstream fileStream;
	char buffer = ' ';
	int readint;
	std::string readString;

	fileStream.open(fileName);
	if (fileStream.fail() || !fileStream.is_open())
        throw std::runtime_error("Cannot open file \"" + fileName +"\"");
	fileStream >> buffer;
	while (!fileStream.eof() && buffer != 'E') 
	{
		Vertex read;

		fileStream >> readint;
		read.setId(readint);
		if (buffer == 'T') 
		{
			fileStream >> readString;
			read.setLine(readString);
		}
		fileStream.get();
		std::getline(fileStream, readString);
		read.setName(readString);
		vertices.emplace(read.getId(), read);
		fileStream >> buffer;
	}
	while (!fileStream.eof()) 
	{
		Edge read;
		int foo;

		fileStream >> readint;
		read.setSource(readint);
		fileStream >> readint;
		read.setDestination(readint);
		if (vertices[read.getDestination()].getName() == vertices[read.getSource()].getName())
			read.setMetro(false);
		fileStream >> readint;
		read.setDuration(readint);
		vertices[read.getSource()].add_edge(read);
		foo = read.getSource();
		read.setSource(read.getDestination());
		read.setDestination(foo);
		vertices[read.getSource()].add_edge(read);
		fileStream >> buffer;
	}
	load_line();
	return 1;
}


void Graph::load_line()
{
	std::stack<unsigned int> to_treat;

	for (auto& station : vertices)
	{
		if (station.second.getLine() == "")
			continue;
		to_treat.push(station.second.getId());
		while (!to_treat.empty())
		{
			Vertex& buffer = vertices[to_treat.top()];
			
			to_treat.pop(); 
			for (auto& e : buffer.getEdges())
			{
				if (e.getMetro() == false || vertices[e.getDestination()].getLine() != "")
					continue;
				vertices[e.getDestination()].setLine(buffer.getLine());
				to_treat.push(e.getDestination());
			}
		}
	}
}

std::map<unsigned int, Vertex>& Graph::getVertices()
{
	return vertices;
}

int Graph::add_vertex(const std::string name, const unsigned int id, std::string line)
{
	auto temp = vertices.find(id);

	if (temp != vertices.end()) {
		std::cout << "[ERROR] : Cannot insert vertex %s with id %i in graph %s" << std::endl;
		std::cout << "\tA vertex with the same id already exist" << std::endl;
		return 0;
	}
	vertices.insert(std::pair<int, Vertex>(id, Vertex(name, id, line)));
	return 1;
}


int Graph::add_edge(const unsigned int id1, const unsigned int id2, const unsigned int duration, bool isMetro)
{	
	auto i = vertices.find(id1);
	auto j = vertices.find(id2);

	if(i == vertices.end() || j == vertices.end()) {
		std::cout << "[ERROR] : Cannot create an edge between id %i and %i\n" << std::endl;
		std::cout << "\tOne of the vertices doesn't exist\n" << std::endl;
		return 0;
	}
	else
	{
		i->second.add_edge(id1, id2, duration, isMetro);
		j->second.add_edge(id2, id1, duration, isMetro);
	}
	return 1;
}

void Graph::dijkstra(unsigned int idSource, unsigned int idDestintion)
{
	////VARIABLE
	unsigned int distance[vertices.size()];
	unsigned int pere[vertices.size()];
	std::vector<unsigned int> V;

	///INITIALISATION
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		distance[i] = UINT_MAX;
		pere[i] = UINT_MAX;
	}
	V.push_back(idSource);

	distance[idSource] = 0;
	std::list<Edge> edges = dijkstra_find_valid_edge(idSource, V);
	for (auto i = edges.begin(); i != edges.end(); ++i)
	{
		distance[i->getDestination()] = i->getDuration();
		pere[i->getDestination()] = i->getSource();
	}

	///BOUCLE PRINCIPAL
	while(V.size() < vertices.size())
	{
		unsigned int indice_min = dijkstra_find_indice_min_distance(distance, V);
		V.push_back(indice_min);

		std::list<Edge> edges = dijkstra_find_valid_edge(indice_min, V);

		for (auto i = edges.begin(); i != edges.end(); ++i)
		{
			unsigned int new_duration = distance[indice_min] + i->getDuration();
			unsigned int old_duration = distance[i->getDestination()];

			if(new_duration < old_duration)
			{
				distance[i->getDestination()] = new_duration;
				pere[i->getDestination()] = indice_min;
			}
		}
	}

	std::list<Vertex> test = dijkstra_get_path(idSource, idDestintion, pere);

	printf("\n");
	for (auto i = test.begin(); i != test.end(); ++i)
	{
		printf("-> %u ", i->getId());
	}
	printf("\n\n");
}


std::list<Edge> Graph::dijkstra_find_valid_edge(const unsigned int id, const std::vector<unsigned int> &V)
{
	std::list<Edge> res;
	std::list<Edge> buffer;

	auto it = vertices.find(id);
  	if (it == vertices.end())
   		throw std::runtime_error("Cannot find id" + id);

	buffer = it->second.getEdges();
	for (auto i = buffer.begin(); i != buffer.end(); ++i)
	{
		bool valid = true;
		for (unsigned int j = 0; j < V.size(); ++j)
			if(i->getDestination() == V[j])
				valid = false;

		if(valid)
			res.push_front(*i);
	}

	return res;
}


unsigned int Graph::dijkstra_find_indice_min_distance(unsigned int *d, const std::vector<unsigned int> &V)
{
	unsigned int min = UINT_MAX, indice_min = 0;
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		bool valid = true;
		for (unsigned int j = 0; j < V.size(); ++j)
			if(i == V[j])
				valid = false;
		if(valid)
		{
			if(min > d[i] && d[i] > 0)
			{
				indice_min = i;
				min = d[i];
			}
		}
	}
	return indice_min;
}


std::list<Vertex> Graph::dijkstra_get_path(const unsigned int idSource, const unsigned int idDestintion, const unsigned int *pere)
{
	std::list<Vertex> res;

	res.push_front(vertices.find(idDestintion)->second);
	unsigned int indice = pere[idDestintion];

	while(indice != idSource)
	{
		res.push_front(vertices.find(indice)->second);
		indice = pere[indice];
	}
	res.push_front(vertices.find(idSource)->second);
	return res;
}


void Graph::render()
{
	std::cout << vertices.size() << std::endl;
	for(auto &i : vertices)
		i.second.print();
}