//Cardy Wei
//DSA2
//Professor Sable

//Makefile and header file based off files by Professor Sable

#ifndef __HASH_H__
#define __HASH_H__

#include <vector>
#include <string>

class HashTable {
    public:

          // The constructor initializes the hash table.
          // Uses getPrime to choose a prime number at least as large as
          // the specified size for the initial size of the hash table.
          HashTable(int size = 0);

          // Insert the specified key into the hash table.
          // If an optional pointer is provided,
          // associate that pointer with the key.
          // Returns 0 on success,
          // 1 if key already exists in hash table,
          // 2 if rehash fails.
          
        int insert (std::string const & key, void * pv = nullptr);

          // Check if the specified key is in the hash table.
          // If so, return true; otherwise, return false.
        bool contains (std::string const & key);

          // Get the pointer associated with the specified key.
          // If the key does not exist in the hash table, return NULL.
          // If an optional pointer to a bool is provided,
          // set the bool to true if the key is in the hash table,
          // and set the bool to false otherwise.
        void *getPointer (std::string const & key, bool * b = nullptr);

          // Set the pointer associated with the specified key.
          // Returns 0 on success,
          // 1 if the key does not exist in the hash table.
          bool setPointer (std::string const & key, void * pv);

          // Delete the item with the specified key.
          // Returns true on success,
          // false if the specified key is not in the hash table.
        bool remove (std::string const & key);

    private:
            // Each item in the hash table contains:
      // key - a string used as a key.
      // isOccupied - if false, this entry is empty,
      //              and the other fields are meaningless.
      // isDeleted - if true, this item has been lazily deleted.
      // pv - a pointer related to the key;
      //      NULL if no pointer was provided to insert.

        typedef struct {
            std::string key;
            bool isOccupied;
            bool isDeleted;
            void *pv;
        } HashItem;

        std::vector<HashItem> data;

        static unsigned int getPrime (int num);

        size_t key_hash (std::string const & key);
        size_t key_hash2 (std::string const & key);

        bool hash_again ();

        int capacity;
        int filled;

        int findPos (std::string const & key);
        
       
};

#endif //_HASH_H