//jumana oubaid 
// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  
};

template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash){
  //set the variables and make a new rtable, 
  _hash = hash;
  _N = size;
   _table = new Heap<T>[_N];
}

template <class T>
HashTable<T>::~HashTable(){
  //delete the array and set the variables to 0.
    delete [] _table;
    _N = 0;
    _n = 0;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht){
  //set the bariables and loop through the array and copy the contents. 
  _N = ht._N;
  _n = ht._n;
  _hash = ht._hash;
  _table = new Heap<T>[_N];
  for(unsigned int i = 0; i < _N; i++){
    _table[i] = ht._table[i];
  }
}
template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht){
  //same as copy constructor then return this. 
  if(this != ht){
    _N = ht._N;
    _n = ht._n;
    _hash = ht._hash;
    _table = new Heap<T>[_N];
    for(unsigned int i = 0; i < _N; i++){
    _table[i] = ht._table[i];
    }
  }
  return *this;

}

template <class T>
bool HashTable<T>::insert(const T& object){
  //get the index  
  int index = _hash(object.key()) % tableSize();
  int original = index;
  //loop until the table is empty or the keys are the same. 
  while ((_table[index].empty()) == false && (object.key() != _table[index].readTop().key())){
    //increment index
    index++;
    //same as index % tablesize. 
    if (index == _N) {
      index = 0;
    }
    //if the array is full then return false. 
    if (original == index){
      return false;
    }
  }
  //insert into the table and return true if it inserts. 
  _table[index].insert(object);
  return true;  
}

template <class T>
bool HashTable<T>::getNext(string key, T& obj){
  //get the index 
  unsigned int index = _hash(key) % _N;
  unsigned int original = index;
  int newSize = _table[index].size();
  //make sure the index size isn't zero. 
  if (newSize == 0){
    return false;
  } 
  //loop until there isnt a used space and the keys arent the same.
  while ((_table[index].used()) == false || ((key != _table[index].readTop().key()))){
    index++;
    //set the index 
    if (index == _N) {
      index = 0;
    }
    //if the table is full return false. 
    if (original == index){
      return false;
    }
    //return false;
  }

  //if(key == _table[index].readTop().key()){
    //read the top of the table and set it to the obj. 
    obj = _table[index].readTop();
    //remove the top. 
    _table[index].removeTop();
  //}
  return true;
}

template <class T>
void HashTable<T>::dump() const{
  //loop throught the table and print out the contents of the index. 
  for(int i = 0; i < _N; i++){ 
   cout << "[ " << i << " ]:" << endl;
    _table[i].dump();    
  }

}
#endif
