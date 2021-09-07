// CMSC 341 - Fall 2019 - Project 3
// File: treap.cpp

using namespace std ;

#include "treap.h"

//constructor
Treap::Treap() {
  _nptr = nullptr ;
}

//copy constructor
Treap::Treap(const Treap& other) {
  _nptr = preorder(other);
}

//preorder: helper function for copy constructor. creates a copy of nodes using preorder traversal.
TreapNode* Treap::preorder(const Treap& other) {
  if ( other.empty() ) return nullptr;
  //create a new treapnode and traverse left and right. 
  TreapNode* newTreap = new TreapNode(other._nptr->_data, other._nptr->_pri);
  newTreap->_height = other._nptr->_height;
  newTreap->_left._nptr = preorder(other._nptr->_left);
  newTreap->_right._nptr = preorder(other._nptr->_right) ;
  return newTreap;
}

//destructor
Treap::~Treap() {
  if(_nptr != nullptr){ 
    //delete the root.
   delete _nptr;
  }
}
//overloaded assignment operator
const Treap& Treap::operator=(const Treap& rhs) {
  if(this != &rhs){
    //delete the root and call the preorder function.
    delete _nptr;
    _nptr = nullptr;
   _nptr = preorder(rhs);
  }
  return *this;
  
}

// Return -1 if the treap is empty; otherwise, return value in _height.
int Treap::height() const {
  return _nptr ? _nptr->_height : -1 ;
}

// Return the priority of the root node of a Treap.
// Note: numeric_limits<priority_t>::min() returns the minimum value
// of the priority type.  We will only use int priorities, so this is
// the minimum integer value.
priority_t Treap::priority() const {
  return _nptr ? _nptr->_pri : numeric_limits<priority_t>::min() ;
}

//find function. Traverses through tree to find x.
const data_t* Treap::find(const data_t& x) {
  if ( empty() ){
    return nullptr;
  }

  //check the right side of tree for x.
  if (_nptr->_data < x) { 
    return _nptr->_right.find(x);

    
    //check the left side of 
  } else if (x < _nptr->_data ) {
    return _nptr->_left.find(x);
  }
  //if the x is found return the pointer. 
  if(_nptr->_data == x){
      data_t* ptr = &_nptr->_data;
      return ptr;
    }
}

// Inorder traversal.  Recommend you NOT change this!!!
void Treap::inorder() {

  if ( empty() ) return ;

  cout << "(" ;
  _nptr->_left.inorder() ;

  cout << _nptr->_data << ":" << priority() << ":" << height() ;

  _nptr->_right.inorder() ;
  cout << ")" ;

  return  ;
}

// Used for debugging and grading.  Interprets the characters in
// position[] as directions in the tree.  E.g., "RLR" means, "starting
// from root, go right, then left, then right."  If position[] is an
// empty string, then it just locats the value a the root.
// See project description for details.
bool Treap::locate (const char position[], data_t& x, priority_t& p, int& h, int offset) {

  if (_nptr == nullptr) return false ;

  if (position[offset] == '\0') {
    x = _nptr->_data ;
    p = _nptr->_pri ;
    h = _nptr->_height ;
    return true ;
  }

  if (position[offset] == 'L') {
    return _nptr->_left.locate(position, x, p, h, offset+1) ;
  }

  if (position[offset] == 'R') {
    return _nptr->_right.locate(position, x, p, h, offset+1) ;
  }

  cerr << "Bad position character!\n" ;
  exit(17) ;

  return false ; 
}


// Basic BST insertion.  Does not allow duplicate values.
//
// Complete this function to do Treap insertion.
//
//helper function to update height. 
void Treap::newHeight(){
  if(_nptr == nullptr){
    return;
  }
  int leftHeight = _nptr->_left.height();
  int rightHeight = _nptr->_right.height();
  _nptr->_height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight );
}


//insert function. 
void Treap::insert(const data_t& x, const priority_t& p) {
  //if its empty create a new treapnode with the data values. 
  if ( empty() ) {
    _nptr = new TreapNode(x, p) ;
  }
  //DOESNT ALLOW DUPLICATE VALUES
  if(_nptr->_data == x){
    return;
  }
  //compare the data and insert based off the data. 
  if (_nptr->_data < x) { 
    _nptr->_right.insert(x, p) ;
    
  } else if (x < _nptr->_data ) {
    _nptr->_left.insert(x, p) ;

  }

  //update height
  newHeight();
  //if the left priotity is greater than the root priority. 
  if((_nptr->_left).priority() > _nptr->_pri){
    //check if theres a left node. 
    if(_nptr->_left._nptr != nullptr){
      //rotate right and update height. 
      rotateRight();
      newHeight();
      _nptr->_right.newHeight();
    }
  }
  //check if the right priority is greater than the root pointer
  if((_nptr->_right).priority() > _nptr->_pri){
    //check to see if theres a right node. 
    if(_nptr->_right._nptr != nullptr){
      //rotate left and update height. 
      rotateLeft();
      newHeight(); 
      _nptr->_left.newHeight();
    }
  }
  //update height. 
  newHeight();
}

//left rotation.
void Treap::rotateLeft(){
  //create a pointer node for each part of the tree
  TreapNode *y = _nptr;
  TreapNode *x = y->_right._nptr;
  TreapNode *b = x->_left._nptr;
  TreapNode *a = y->_left._nptr;
  TreapNode *c = x->_right._nptr;
  //point the nodes to their new children. 
  x->_left._nptr = y;
  _nptr = x;
  y->_right._nptr = b;
}

//right rotation 
void Treap::rotateRight(){
  //create a pointer node for each part of the tree
	TreapNode *x = _nptr;
	TreapNode *y = x->_left._nptr;
	TreapNode *a = y->_left._nptr;
	TreapNode *b = y->_right._nptr;
	TreapNode *c = x->_right._nptr;
  //point the nodes to their new children. 
  y->_right._nptr = x;
  _nptr = y;
  x->_left._nptr = b;
}

//remove function
bool Treap::remove(const data_t& x) {
  //check to see if theres a root. return false if not found.
  if (_nptr == nullptr) {
    return false;
  }
//check right and recurse through tree to remove. 
  if (_nptr->_data < x) { 
   _nptr->_right.remove(x);
  } 
  //check left and recurse through tree to remove. 
  else if (x < _nptr->_data ) {
    _nptr->_left.remove(x);
  }

  //no child
  else{
    //compare to see if there is left and right children and delete the node. 
    if(_nptr->_right._nptr == nullptr && _nptr->_left._nptr == nullptr){
      delete _nptr;
      _nptr = nullptr;
     //found so return true. 
      return true;
    }
  //compare the left and right priorities and rotate if left is greater than right.
    else if((_nptr->_left).priority() > _nptr->_right.priority()){
      rotateRight();
      _nptr->_right.newHeight();
      //update height and call the same function.
      newHeight();
      _nptr->_right.remove(x);
    }
    //compare the priorities and rotate left if right priority is greater than left. 
    else if((_nptr->_right).priority() > _nptr->_left.priority()){
      rotateLeft();
      //update height and call remove. 
      _nptr->_left.newHeight();
      newHeight(); 
      _nptr->_left.remove(x);
     }
  }
  //update height and return true since found. 
  newHeight();
  return true;
}
 
// Treap::dump() just calls TreapNode::dump()
void Treap::dump() {
  if ( !empty() ) _nptr->dump() ;
}


ostream& operator<< (ostream& os, const Treap& T) {
  os << T._nptr ; 
  return os ;
}


TreapNode::TreapNode() : _height(0) {
  // Empty constructor body
}

TreapNode::TreapNode(const data_t& x, const priority_t& p) 
  : _data(x), _pri(p), _height(0) { 
  // Empty constructor body
}

TreapNode::~TreapNode() {
  // Empty destructor
  // Retained for debugging
}

// Dump the contents of a node
void TreapNode::dump() {
  cout << "===== TreapNode::dump()\n" ;
  cout << "      this = " << this << endl ; 
  cout << "      left = " << _left << endl ; 
  cout << "      right= " << _right << endl ; 
  cout << "      data = " << _data << endl ;
  cout << "      height = " << _height << endl ;
  _left.dump() ;
  _right.dump() ;
}
