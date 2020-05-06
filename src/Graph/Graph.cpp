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
			read.setTerminus(true);
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
	spread_line();
	return 1;
}

void Graph::spread_line()
{
	// Pile pour stocker les ids des stations a traiter
	std::stack<unsigned int> to_treat;
	// Pour chaque station dans le graph
	for (auto& station : vertices)
	{
		// Si la station a une ligne définie et n'est pas marqué 
		// (correspond a un terminus)
		if (station.second.getLine() == "" || station.second.getMarked())
			continue;
		station.second.setMarked(1);
		// on rajoute la station sur la pile
		to_treat.push(station.second.getId());
		// parcours en profondeur
		while (!to_treat.empty())
		{
			Vertex& buffer = vertices[to_treat.top()];
			to_treat.pop(); 
			// pour chaque connexions de la station courantes
			for (auto& e : buffer.getEdges())
			{
				//Si la liaison n'est pas de la marche (meme ligne) et que la station n'a pas de ligne définie
				if (e.getMetro() == false || vertices[e.getDestination()].getLine() != "" || vertices[e.getDestination()].getMarked())
					continue;
				// on définie la ligne et on push la nouvelle station sur la pile
				Vertex& tmp = vertices[e.getDestination()];
				tmp.setLine(buffer.getLine());
				tmp.setMarked(1);
				to_treat.push(e.getDestination());
			}
		}
	}
	unmarkAll();
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

std::list<Vertex> Graph::dijkstra(unsigned int idSource, unsigned int idDestintion)
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
	int a = 0;
	while(V.size() < vertices.size())
	{
		a++;
		unsigned int indice_min = dijkstra_find_indice_min_distance(distance, V);
		V.push_back(indice_min);

		std::list<Edge> edges = dijkstra_find_valid_edge(indice_min, V);

		for (auto& i  : edges)
		{
			unsigned int new_duration = distance[indice_min] + i.getDuration();
			unsigned int old_duration = distance[i.getDestination()];

			if(new_duration < old_duration)
			{
				distance[i.getDestination()] = new_duration;
				pere[i.getDestination()] = indice_min;
			}
		}
		if(vertices.find(idDestintion)->second.getName() == vertices.find(indice_min)->second.getName())
			break;
	}

	std::list<Vertex> vert = dijkstra_get_path(idSource, idDestintion, pere);
	return vert;
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


std::list<std::string> Graph::vertex_to_string(std::list<Vertex>& vertices_path)
{
	std::list<std::string> res;
	unsigned int duration = 0;

	std::string prendre_ligne("- Prendre la ligne "), ensuite("- Ensuite prendre la ligne "),\
		jusqua(" jusqu'a ");

	auto head = vertices_path.begin();

	std::string line;
	std::string station;
	int oldDestination = -1;
	int oldOldDestination = -1;

	while(head != vertices_path.end())
	{	
		line = head->getLine();
		station = head->getName();
		oldDestination = head->getId();

		while(line == head->getLine())
		{

			unsigned int idDestintion = head->getId();
			head++;


			if(head == vertices_path.end())
				break;
			unsigned int idSource = head->getId();

			unsigned int bufferDuration = get_duration_edge_list(head->getEdges(), idSource, idDestintion);
			if(!bufferDuration)
				printf("edge not find\n");
			duration += bufferDuration;
			
			if(head->getName() != vertices[oldDestination].getName())
			{
				if(vertices[oldOldDestination].getName() != vertices[oldDestination].getName())
					oldOldDestination = oldDestination;
				oldDestination = head->getId();
			}
		}

		head--;
		std::string terminus;
		if(oldOldDestination == -1)
			terminus = calcul_terminus(oldDestination, head->getId());
		else
			terminus = calcul_terminus(oldOldDestination, oldDestination);
		if(res.empty())
		{
			res.push_back(prendre_ligne + line + " a " + station + " direction " +  terminus + jusqua + head->getName());
		}
		else if (terminus == head->getName())
		{
			res.push_back(ensuite + line + " direction " + terminus + " jusqu'au terminus");
		} else
			res.push_back(ensuite + line + " direction " + terminus + jusqua + head->getName());
		
		head++;
	}
	if(station == vertices_path.back().getName())
		res.pop_back();
	for (auto& i : res)
	{
		for (unsigned int j = 40; j < i.size(); j += 40)
		{	
			int u;
			for (u = j; u > 0 && i[u] != ' '; u--);
			if (u == 0)
				continue;
			i.insert(u, 1, '\n');
		}
	}
	unmarkAll();
	res.push_back("\n== Duree estimee du trajet : " + convert_second_to_string(duration) + " ==");
	res.push_back("\n\nAlertes voyageurs :\nNous vous rapellons l'importance du port du \nmasque");
	return res;
}


unsigned int Graph::get_duration_edge_list(std::list<Edge>& edges, const unsigned int idSource, const unsigned int idDestination)
{
	for(auto& i : edges)
		if(i.getDestination() == idDestination && i.getSource() == idSource)
			return i.getDuration();
	return 0;
}


std::string Graph::convert_second_to_string(const unsigned int duration)
{
	std::string time;
	unsigned int minute = duration / 60;
	unsigned int second = duration % 60;
	unsigned int heure = minute / 60;
	minute = minute % 60;

	if(heure)
		time += std::to_string(heure) + "h";
	if(minute)
		time += std::to_string(minute) + "m";
	if(second)
		time += std::to_string(second) + "s";

	return time;
}


std::string Graph::calcul_terminus(unsigned int id1, unsigned int id2)
{
	std::stack<unsigned int> pile;
	vertices[id1].setMarked(1);
	vertices[id2].setMarked(1);
	pile.push(id2);

	while (!pile.empty())
	{
		int current = pile.top();
		pile.pop();
		if (vertices[current].getTerminus())
			return vertices[current].getName();
		for (auto& i : vertices[current].getEdges())
		{
			if (!(vertices[i.getDestination()].getMarked()) && vertices[i.getDestination()].getLine() == vertices[current].getLine())
			{
				if (vertices[i.getDestination()].getTerminus())
					return vertices[i.getDestination()].getName();
				pile.push(i.getDestination());
				vertices[i.getDestination()].setMarked(1);
			}
		}
	}
	throw std::runtime_error("Unknown terminus :) !");
}


void Graph::unmarkAll()
{
	for(auto& i : vertices)
		i.second.setMarked(0);
}