//Cardy Wei
//DSA2
//Professor Sable

#include "hash.h"

HashTable::HashTable (int size) {
    int optimalSize = getPrime (size);
    this->capacity = optimalSize;
    this->filled = 0;
    HashItem hashable;
    hashable.key = "";
    hashable.isOccupied = false;
    hashable.isDeleted = false;
    hashable.pv = nullptr;
    this->data.resize (optimalSize, hashable);
}

//prime list
unsigned int HashTable::getPrime (int num) {
    static unsigned int primelist[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289,24593, 49157, 98317, 196613, 393241, 786433,1572869, 3145739, 6291469, 12582917, 25165843,50331653, 100663319, 201326611, 402653189,805306457, 1610612741};
    int i = 0;
    while (primelist[i] < 2 * num) {
        ++i;
    }
    return primelist[i];
}

int HashTable::insert (std::string const & key, void * pv) {
    if (this->findPos (key) < 0) {
        unsigned int position, shifted;
        position = this->key_hash (key) % this->capacity;
        shifted = this->key_hash2 (key) % (this->capacity - 1) + 1;
        for (int i = 0; i < this->capacity; ++i) {
            position = (position + i * shifted) % this->capacity;
            HashItem & item = this->data.at (position);
            if (!item.isOccupied) {
                item.key = key;
                item.pv = pv;
                item.isOccupied = true;
                ++this->filled;
                break;
            } 
            else if (item.isDeleted && item.key == key) {
                item.isDeleted = false;
                break;
            }
        }
    } 
    else {
        return 1; 
    }
    if ((float) this->filled / (float) this->capacity > 0.5){
        if (!this->hash_again ()) {
            return 2;
        }
    }
    return 0;
}
//lazy delete
bool HashTable::remove (std::string const & key) {
    int position2 = this->findPos (key);
    if (position2 >= 0) {
        (this->data.at (position2)).isDeleted = true;
        return true;
    }
    else {
        return false;
    }
}

bool HashTable::contains (std::string const & key) {
    if (this->findPos (key) < 0){
        return false;
    }
    else {
        return true;
    }
}


int HashTable::findPos (std::string const & key) {
    unsigned int pos, shifted;
    pos = this->key_hash (key) % this->capacity;
    shifted = this->key_hash2 (key) % (this->capacity - 1) + 1;
    int i;
    HashItem item;
    for (i = 0; i < this->capacity; ++i) {
        pos = (pos + i * shifted) % this->capacity;
        item = this->data.at (pos);
        if (item.isOccupied && !item.isDeleted && item.key == key)
            return pos;
        else if (!item.isOccupied)
            return -1;
    }
}


size_t HashTable::key_hash (std::string const & key) {
    size_t hash = 14695981039346656037UL;
    char const * str = key.c_str ();
    unsigned int c;
    while (c = *str++) {    
        hash ^= c;
        hash *= 1099511628211;
    }
    return hash;
}

size_t HashTable::key_hash2 (std::string const & key) {
    size_t hash = 14695981039346656037UL;
    char const * str = key.c_str ();
    unsigned int c;
    while (c = *str++) {    
        hash *= 1099511628211;
        hash ^= c;
    }
    return hash;
}

bool HashTable::hash_again () {
    int prev = this->capacity;
    this->capacity = getPrime (this->capacity);
    HashItem prev2;
    HashItem hashable_again;
    hashable_again.key = "";
    hashable_again.isOccupied = false;
    hashable_again.isDeleted = false;
    hashable_again.pv = nullptr;
    std::vector<HashItem> tempData;
    tempData.resize (this->capacity, hashable_again);
    if (tempData.size () != this->capacity) return false;
    unsigned int pos, shifted;
    int i, j;
    for (i = 0; i < prev; ++i) {
        prev2 = this->data.at (i); 
        if (prev2.isOccupied && !prev2.isDeleted) {
            pos = this->key_hash (prev2.key) % this->capacity;
            shifted = this->key_hash2 (prev2.key) % (this->capacity - 1) + 1;
            for (j = 0; j < prev; ++j) {
                pos = (pos + j * shifted) % this->capacity;
                HashItem & temp = tempData.at (pos);
                if (!temp.isOccupied) {
                    temp.key = prev2.key;
                    temp.pv = prev2.pv;
                    temp.isOccupied = true;
                    break;
                }
            }
        }
    }
    this->data = tempData;
    return true;
}

void * HashTable::getPointer (std::string const & key, bool * b) {
    int pos = this->findPos (key);
    if (pos >= 0) {
        if (b != nullptr) {
            *b = true;
        }
        return (this->data.at (pos)).pv;
    } else {
        if (b != nullptr) {
            *b = false;
        }
        return nullptr;
    }
}

bool HashTable::setPointer (std::string const & key, void * pv) {
    int pos = this->findPos (key);
    if (pos >= 0) {
        (this->data.at (pos)).pv = pv;
        return true;
    } 
    else {
        return false;
    }
}
