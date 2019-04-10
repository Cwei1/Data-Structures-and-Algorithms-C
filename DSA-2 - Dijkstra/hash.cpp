#include "hash.hpp"

HashTable::HashTable (int size) {
	int optimalSize = getPrime (size);

	capacity = optimalSize;
	numOccupied = 0;

	HashItem emptyItem;
	emptyItem.key = "";
	emptyItem.isOccupied = false;
	emptyItem.isDeleted = false;
	emptyItem.pv = nullptr;

	data.resize (optimalSize, emptyItem);
}

unsigned int HashTable::getPrime (int num) {
	static unsigned int prime[] = {
		53, 97, 193, 389, 769, 1543, 3079, 6151, 12289,
		24593, 49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189,
		805306457, 1610612741
	};

	int i = 0;
	while (prime[i] < 2 * num) ++i;

	return prime[i];
}

int HashTable::insert (std::string const & key, void * pv) {
	if (getPos (key) < 0) {

		unsigned int pos, offset;
		pos = keyHash (key) % capacity;
		offset = keyHash2 (key) % (capacity - 1) + 1;

		int i;

		for (i = 0; i < capacity; ++i) {
			pos = (pos + i * offset) % capacity;
			HashItem & item = data.at (pos);

			if (!item.isOccupied) {
				item.key = key;
				item.pv = pv;
				item.isOccupied = true;
				++numOccupied;
				break;
			} else if (item.isDeleted && item.key == key) {
				item.isDeleted = false;
				break;
			}
		}
	} else return 1;

	if ((float) numOccupied / (float) capacity > 0.5)
		if (!rehash ()) return 2;

	return 0;
}

bool HashTable::remove (std::string const & key) {

	int pos = getPos (key);
	if (pos >= 0) {
		(data.at (pos)).isDeleted = true;
		return true;
	} else return false;
}

bool HashTable::contains (std::string const & key) {
	if (getPos (key) < 0) return false;
	else return true;
}

void * HashTable::getPointer (std::string const & key, bool * b) {
	int pos = getPos (key);
	if (pos >= 0) {
		if (b != nullptr) *b = true;
		return (data.at (pos)).pv;
	} else {
		if (b != nullptr) *b = false;
		return nullptr;
	}
}

bool HashTable::setPointer (std::string const & key, void * pv) {
	int pos = getPos (key);
	if (pos >= 0) {
		(data.at (pos)).pv = pv;
		return true;
	} else return false;
}

size_t HashTable::keyHash (std::string const & key) {
	size_t hash = 14695981039346656037UL;
	char const * str = key.c_str ();
	unsigned int c;

	while (c = *str++) {	
		hash ^= c;
		hash *= 1099511628211;
	}

	return hash;
}

size_t HashTable::keyHash2 (std::string const & key) {
	size_t hash = 14695981039346656037UL;
	char const * str = key.c_str ();
	unsigned int c;

	while (c = *str++) {	
		hash *= 1099511628211;
		hash ^= c;
	}

	return hash;
}

bool HashTable::rehash () {
	int oldSize = capacity;
	capacity = getPrime (capacity);

	HashItem item;
	HashItem emptyItem;
	emptyItem.key = "";
	emptyItem.isOccupied = false;
	emptyItem.isDeleted = false;
	emptyItem.pv = nullptr;

	std::vector<HashItem> tempData;
	tempData.resize (capacity, emptyItem);

	// memory allocation fail-safe
	if (tempData.size () != capacity) return false;

	unsigned int pos, offset;

	int i, j;
	for (i = 0; i < oldSize; ++i) {
		item = data.at (i); 
		
		if (item.isOccupied && !item.isDeleted) {
			pos = keyHash (item.key) % capacity;
			offset = keyHash2 (item.key) % (capacity - 1) + 1;

			for (j = 0; j < oldSize; ++j) {
				pos = (pos + j * offset) % capacity;
				HashItem & tempItem = tempData.at (pos);

				if (!tempItem.isOccupied) {
					tempItem.key = item.key;
					tempItem.pv = item.pv;
					tempItem.isOccupied = true;
					break;
				}
			}
		}
	}

	data = tempData;

	return true;
}

int HashTable::getPos (std::string const & key) {
	unsigned int pos, offset;
	pos = keyHash (key) % capacity;
	offset = keyHash2 (key) % (capacity - 1) + 1;
	
	int i;
	HashItem item;

	for (i = 0; i < capacity; ++i) {
		pos = (pos + i * offset) % capacity;
		item = data.at (pos);

		if (item.isOccupied && !item.isDeleted && item.key == key)
			return pos;

		else if (!item.isOccupied)
			return -1;
	}
}

