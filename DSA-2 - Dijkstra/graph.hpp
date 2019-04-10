#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <fstream>
#include <list>
#include <string>

#include "hash.hpp"
#include "heap.hpp"

class Graph {
	public:
		Graph (long const & capacity = 500000); 

		bool Dijkstra (std::string const & start);
		bool hasNode (std::string const & node);
		bool insert (std::string const & v1, std::string const & v2, long long dist);

		bool exportFile (std::ofstream & out); 
		bool importFile (std::ifstream & in);
	private:
		long capacity;
		struct Node;

		typedef struct Edge {
			long long cost;
			Node * dest;
		} Edge;

		typedef struct Node {
				std::string name; 
				std::list<Edge> adj; 

				
				bool known;
				long long dist;
				std::list<std::string> path;
		} Node;

		std::list<Node *> nodeList;
		HashTable * graphIndex; 
};

#endif
