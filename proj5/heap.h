//jumana oubaid 
// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.
  void heapify(int root); 
  //void swap(T &first, T &second);
  void parentHeap(int number);
};


template <class T> 
Heap<T>::Heap(){
  //nothing is used and we add a placement for 0 index in the vector. 
  _used = false;
  T object; 
  _heap.push_back(object);
}

template <class T> 
void Heap<T>::insert(const T& object){
  //push back if theres only one thing in the vector. 
  int vecSize = _heap.size();
  if(vecSize == ROOT){
    _heap.push_back(object);
    //set the used variable to used. 
    _used = true;
  }
  else{
    //if theres more than one then insert 
    _heap.push_back(object);
    //set used to true
    _used = true;
    //correct the max heap property 
    parentHeap(size());
    //heapify(vecSize - 1);
  }
}

template<class T> 
void Heap<T>::parentHeap(int number){
  //parent is the temp. 
  int temp = number / 2;
  //if the parent is non existant then return. 
  if (temp == 0){
    return;
  }
  //if the priorities are off then swap. 
  if(_heap[number].priority() > _heap[temp].priority()){
    swap(_heap[number], _heap[temp]);
  }
  //recursively call the function. 
  parentHeap(temp);
}

template <class T> 
T Heap<T>::readTop() const{
  if (empty()){
    throw std::domain_error("heap is empty");
  }
  //returns the top of the heap.
  return _heap[ROOT];

}

template <class T>
void Heap<T>::heapify(int root){
  //set the size and left and right children. 
  int size = _heap.size();
  int max = root;
  int left = 2 * root;
  int right = 2 * root + 1;
  //check the priorities and then set parent. 
  if(left < size && _heap[left].priority() > _heap[max].priority()){
    max = left;
  }
  //check priorites again 
  if(right < size && _heap[right].priority() > _heap[max].priority()){
    max = right;
  }
  //if the highest isnt the root then swap.
  if(max != root){
    //swap(_heap[root], _heap[max]);
    T temp = _heap[root];
    _heap[root] = _heap[max];
    _heap[max] = temp;
    //call heapify again recursively.
    heapify(max);
  }
}
template <class T>
void Heap<T>::removeTop(){
  if (empty()){
    throw std::domain_error("heap is empty");
  }
  //if its empty then used is false. 
  if(empty()){
    _used = false;
  }

  int vecSize = size();
  //swap the root and the last element 
  swap(_heap[ROOT], _heap[vecSize]);
  //pop back the root which deletes it. 
  _heap.pop_back();
  //make sure the max heap property is still there. 
  heapify(ROOT);
}

template <class T> 
void Heap<T>::dump() const{
  //loop through the vector and print out the contents at each index. 
  for(unsigned int i = ROOT; i < _heap.size(); i++){
    cout << _heap.at(i) << endl;
  }
}

#endif
