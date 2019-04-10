#include "heap.hpp"

BinaryHeap::BinaryHeap (int capacity) {
	curSize = 0;
	this->capacity = capacity;
	data.resize (capacity + 1);
	map = new HashTable (capacity * 2);
}

int BinaryHeap::insert (std::string const & id, long long key, void * pv) {
	if (!(curSize < capacity)) return 1;
	else if (map->contains (id)) return 2;
	else {
		HeapNode temp;
		temp.id = id;
		temp.key = key;
		temp.pv = pv;
		data[++curSize] = temp;
		map->insert (id, &(data[curSize]));
		percolateUp (curSize);

		return 0;
	}
}

int BinaryHeap::deleteMin (std::string * pId, long long * pKey, void * ppData) {
	if (!curSize) return 1;
	else {
		if (pId != nullptr) *pId = data[1].id;
		if (pKey != nullptr) *pKey = data[1].key;
		if (ppData != nullptr) *((void **) ppData) = data[1].pv;

		map->remove (data[1].id);         
		data[1] = data[curSize--];  
		percolateDown (1);                      

		return 0;
	}
}

int BinaryHeap::setKey (std::string const & id, long long newKey) {
	if (!map->contains (id)) return 1;
	else {
		HeapNode * pn = (HeapNode *) map->getPointer (id);

		long long oldKey = pn->key;
		pn->key = newKey;

		int index = getPos (pn);
		if (oldKey < newKey) percolateDown (index);
		else if (oldKey > newKey) percolateUp (index);

		return 0;
	}
}

int BinaryHeap::remove (std::string const & id, long long * pKey, void * ppData) {
	if (!map->contains (id)) return 1;
	else {
		HeapNode * pn = (HeapNode *) map->getPointer (id);

		if (pKey != nullptr) *pKey = pn->key;
		if (ppData != nullptr) *((void **) ppData) = pn->pv;

		map->remove (id);

		long long oldKey = pn->key;

		*pn = data[curSize--];

		long long newKey = pn->key;

		int index = getPos (pn);
		if (oldKey < newKey) percolateDown (index);
		else if (oldKey > newKey) percolateUp (index);

		return 0;
	}
}

int BinaryHeap::getPos (HeapNode * pn) {
	return pn - &data[0];
}

void BinaryHeap::percolateUp (int index) {
	HeapNode temp = data[index];
	
	while (index > 1 && temp.key < data[index / 2].key) {           
		data[index] = data[index / 2];                        
		map->setPointer (data[index].id, &data[index]); 
		index /= 2;
	}

	data[index] = temp;
	map->setPointer (data[index].id, &data[index]);
}

void BinaryHeap::percolateDown (int index) {
	HeapNode temp = data[index];
	int child;

	while (index * 2 <= curSize) {
		child = index * 2;
		if (child < curSize && data[child + 1].key < data[child].key)
			++child; 

		if (data[child].key < temp.key) {                                     
			data[index] = data[child];                                   
			map->setPointer (data[index].id, &data[index]);        
		} else break;                                                               
		index = child;
	}

	data[index] = temp;
	map->setPointer (data[index].id, &data[index]);
}
