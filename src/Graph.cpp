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


void Graph::dijkstra(unsigned int source, unsigned int destination)
{
	std::cout << "---------------Dijkstra---------------" << std::endl;
	

	////VARIABLE
	unsigned int d[6];
	unsigned int pere[6];
	std::vector<unsigned int> V;


	///INITIALISATION
	for (int i = 0; i < 6; ++i)
	{
		d[i] = 100;
		pere[i] = 100;
	}

	d[source] = 0;
	std::list<Edge> edges = vertices.find(source)->second.getEdges();
	for (auto i = edges.begin(); i != edges.end(); ++i)
	{
		d[i->getDestination()] = i->getDuration();
		pere[i->getDestination()] = i->getSource();
	}
	V.push_back(source);

	
	///affichage
	for (int i = 0; i < 6; ++i)
		printf("%4d ", i);
	printf("\n");
	for (int i = 0; i < 6; ++i)
		printf("%4d ", d[i]);
	printf("\n");
	for (int i = 0; i < 6; ++i)
		printf("%4d ", pere[i]);
	printf("\n");
	for (auto i = V.begin(); i != V.end(); ++i)
		printf("%4d ", *i);
	printf("\n\n");


	///BOUCLE PRINCIPAL
	while(V.size() < 6)
	{
		///on cherche le d min dans le tableau d en excluant les element dans V
		unsigned int min = 100000, indice_min = 0;
		for (unsigned int i = 0; i < 6; ++i)
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
		V.push_back(indice_min);

		std::list<Edge> edges = vertices.find(indice_min)->second.getEdges();
		for (auto i = edges.begin(); i != edges.end(); ++i)
		{
			bool valid = true;
			for (unsigned int j = 0; j < V.size(); ++j)
			{
				if(i->getDestination() == V[j])
					valid = false;
			}
			if(valid)
			{
				unsigned int new_duration = d[indice_min] + i->getDuration();
				unsigned int old_duration = d[i->getDestination()];

				if(new_duration < old_duration)
				{
					d[i->getDestination()] = new_duration;
					pere[i->getDestination()] = indice_min;
				}
			}
		}

		///affichage
		for (int i = 0; i < 6; ++i)
			printf("%4d ", i);
		printf("\n");
		for (int i = 0; i < 6; ++i)
			printf("%4d ", d[i]);
		printf("\n");
		for (int i = 0; i < 6; ++i)
			printf("%4d ", pere[i]);
		printf("\n");
		for (auto i = V.begin(); i != V.end(); ++i)
			printf("%4d ", *i);
		printf("\n\n");
	}
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


void Graph::render()
{
	std::cout << vertices.size() << std::endl;
	for(auto &i : vertices)
		i.second.print();
}