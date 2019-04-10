#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>
#include <string>
#include "hash.hpp"

class BinaryHeap {
	public:
		BinaryHeap (int capacity);

		int insert (std::string const & id, long long key, void * pv = nullptr);
		int deleteMin (std::string * pId = nullptr, long long * pKey = nullptr, void * ppData = nullptr);
		int setKey (std::string const & id, long long key);
		int remove (std::string const & id, long long * pKey = nullptr, void * ppData = nullptr);
	private:
		typedef struct {
			std::string id;
			long long key;
			void * pv;
		} HeapNode;

		int capacity;
		int curSize;

		std::vector<HeapNode> data;

		HashTable * map;

		int getPos (HeapNode * pn);

		void percolateUp (int index);
		void percolateDown (int index);
};

#endif
