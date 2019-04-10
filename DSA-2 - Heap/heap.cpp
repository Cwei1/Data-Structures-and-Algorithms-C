//Cardy Wei
//DSA2
//Professor Sable

#include "heap.h"

BinaryHeap::BinaryHeap (int newcapacity) {
	curSize = 0;
	capacity = newcapacity;
	data.resize (newcapacity + 1);
	mapping = new HashTable (newcapacity * 2);
}

int BinaryHeap::getPos (node * pn) {
	int pos = pn - &data[0];
	return pos;
}

int BinaryHeap::insert (std::string const & id, int key, void * pv) {
	if (!(curSize < capacity)) {
		return 1;
	}
	else if (mapping->contains (id)) {
		return 2;
	}
	else {
		node temp;
		temp.id = id;
		temp.key = key;
		temp.pv = pv;
		data[++curSize] = temp;
		mapping->insert (id, &(data[curSize]));
		percolateUp (curSize);
		return 0;
	}
}

void BinaryHeap::percolateUp (int index) {
	node temp = data[index];
	while (index > 1 && temp.key < data[index / 2].key) {           
		data[index] = data[index / 2];                       
		mapping->setPointer (data[index].id, &data[index]); 
		index /= 2;
	}
	data[index] = temp;
	mapping->setPointer (data[index].id, &data[index]);
}

void BinaryHeap::percolateDown (int index) {
	node temp = data[index];
	int leaf;
	while (index * 2 <= curSize) {
		leaf = index * 2;
		if (leaf < curSize && data[leaf + 1].key < data[leaf].key){
			++leaf; 
		}

		if (data[leaf].key < temp.key) {                                    
			data[index] = data[leaf];                                 
			mapping->setPointer (data[index].id, &data[index]);       
		} else break;                                                               
		index = leaf;
	}
	data[index] = temp;
	mapping->setPointer (data[index].id, &data[index]);
}

int BinaryHeap::remove (std::string const & id, int * pKey, void * ppData) {
	if (!mapping->contains (id)) {
		return 1;
	}
	else {
		node * pn = (node *) mapping->getPointer (id);
		if (pKey != nullptr) {
			*pKey = pn->key;
		}
		if (ppData != nullptr) {
			*((void **) ppData) = pn->pv;
		}
		mapping->remove (id);
		int oldKey = pn->key;
		*pn = data[curSize--];
		int newKey = pn->key;
		int index = getPos (pn);
		if (oldKey < newKey) {
			percolateDown (index);
		}
		else if (oldKey > newKey) {
			percolateUp (index);
		}
		return 0;
	}
}

int BinaryHeap::deleteMin (std::string * pId, int * pKey, void * ppData) {
	if (!curSize) {
		return 1;
	}
	else {
		if (pId != nullptr) {
			*pId = data[1].id;
		}
		if (pKey != nullptr) {
			*pKey = data[1].key;
		}
		if (ppData != nullptr) {
			*((void **) ppData) = data[1].pv;
		}
		mapping->remove (data[1].id);         
		data[1] = data[curSize--];  
		percolateDown (1);                  
		return 0;
	}
}

int BinaryHeap::setKey (std::string const & id, int newKey) {
	if (!mapping->contains (id)) {
		return 1;
	}
	else {
		node * pn = (node *) mapping->getPointer (id);
		int oldKey = pn->key;
		pn->key = newKey;
		int index = getPos (pn);
		if (oldKey < newKey) {
			percolateDown (index);
		}
		else if (oldKey > newKey) {
			percolateUp (index);
		}
		return 0;
	}
}

