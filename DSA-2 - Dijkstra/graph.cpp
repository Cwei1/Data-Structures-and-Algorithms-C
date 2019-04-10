#include <climits>
#include <iterator>
#include "graph.hpp"

Graph::Graph (long const & capacity) {
	graphIndex = new HashTable (capacity * 2);
	this->capacity = 0;
}

bool Graph::Dijkstra (std::string const & begin) {
	int i;
	Node * start = (Node *) graphIndex->getPointer (begin);
	start->dist = 0; 
	start->path.push_back (begin);
	
	BinaryHeap helper (capacity);
	helper.insert (begin, start->dist, start); 
	for (std::list<Node *>::const_iterator it = nodeList.begin (), end = nodeList.end (); it != end; ++it) {
		if ((*it)->name != begin) {
			helper.insert ((*it)->name, (*it)->dist, *it);
		}
	}

	Node * temp;

	for (i = 0; i < capacity; ++i) {
		helper.deleteMin (nullptr, nullptr, &temp);
		for (std::list<Edge>::const_iterator it = temp->adj.begin (), end = temp->adj.end (); it != end && temp->dist != LLONG_MAX; ++it) {
			if (!it->dest->known && it->dest->dist > (it->cost + temp->dist)) {
				
				it->dest->path.clear ();
				it->dest->path.insert (it->dest->path.begin (), temp->path.begin (), temp->path.end ());
				it->dest->path.push_back (it->dest->name);

				
				it->dest->dist = (it->cost + temp->dist);
				helper.setKey (it->dest->name, (it->cost + temp->dist));
			}
		}
		temp->known = true;
	}
	
	return true;
}

bool Graph::hasNode (std::string const & node) {
	return graphIndex->contains (node);
}

bool Graph::insert (std::string const & v1, std::string const & v2, long long dist) {
	Node * temp1, * temp2;
	Edge e;

	if (!graphIndex->contains (v1)) {
		temp1 = new Node; 
		temp1->name = v1;
		temp1->known = false;
		temp1->dist = LLONG_MAX; 
		nodeList.push_back (temp1); 
		graphIndex->insert (v1, temp1); 
		++capacity;
	} else { 
		temp1 = (Node *) graphIndex->getPointer (v1);
	}

	if (!graphIndex->contains (v2)) {
		temp2 = new Node; 
		temp2->name = v2;
		temp2->known = false;
		temp2->dist = LLONG_MAX; 
		nodeList.push_back (temp2); 
		graphIndex->insert (v2, temp2);
		++capacity;
	} else { 
		temp2 = (Node *) graphIndex->getPointer (v2);
	}

	e.cost = dist;
	e.dest = temp2;
	temp1->adj.push_back (e); 

	return true;
}

bool Graph::exportFile (std::ofstream & out) {
	for (std::list<Node *>::const_iterator it = nodeList.begin (), end = nodeList.end (); it != end; ++it) {
		out << (*it)->name << ": ";

		if ((*it)->dist == LLONG_MAX) {
			out << "NO PATH" << std::endl;
		} else {
			out << (*it)->dist << " [";
			for (std::list<std::string>::const_iterator ju = (*it)->path.begin(), foe = (*it)->path.end (); ju != foe; ++ju) {
				out << *ju;
				if (std::next (ju, 1) != foe) out << ", "; 
			}
			out << "]" << std::endl;
		}
	}
	
	return true;
}

bool Graph::importFile (std::ifstream & in) {
	std::string v1, v2;
	long dist;

	while (in >> v1 >> v2 >> dist) {
		insert (v1, v2, dist);
	}

	return true;
}
