//Cardy Wei
//DSA2
//Professor Sable

// Based off code excerpts given by Professor Sable

#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>
#include <string>
#include "hash.h"

class BinaryHeap {
	public:
		BinaryHeap (int newcapacity);

		int insert (std::string const & id, int key, void * pv = nullptr);
		int deleteMin (std::string * pId = nullptr, int * pKey = nullptr, void * ppData = nullptr);
		int setKey (std::string const & id, int key);
		int remove (std::string const & id, int * pKey = nullptr, void * ppData = nullptr);
	private:
		typedef struct {
			std::string id;
			signed int key;
			void * pv;
		} node;

		int capacity;
		int curSize;

		std::vector<node> data;

		HashTable *mapping;

		int getPos (node * pn);

		void percolateUp (int index);
		void percolateDown (int index);
};

#endif