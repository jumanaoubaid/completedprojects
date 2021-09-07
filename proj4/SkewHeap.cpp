
/*
Jumana Oubaid 
project 4 
due: 11/19/19
*/

#include "SkewHeap.h"
using namespace std;

// Constructor.  Must specify priority function.
SkewHeap::SkewHeap(pri_fn pri){
    priority = pri;
    m_heap = nullptr;
}

// Destructor
SkewHeap::~SkewHeap(){
    if(empty()){
        m_heap = nullptr;
    }
    else{
    recursiveDelete(m_heap);
    } 
}

//destructor helper function
void SkewHeap::recursiveDelete(Node* root){
    if(root == nullptr){
        return;
    }
    //delete left then right then root. 
    recursiveDelete(root->left);
    recursiveDelete(root->right);
    delete root;
}

//copy constructor 
SkewHeap::SkewHeap(const SkewHeap& rhs){
    priority = rhs.priority;
    //call the copy constructor helper function on rhs.
    m_heap = copyHelp(rhs.m_heap);
    

}
//helper function for copy contructor 
Node* SkewHeap::copyHelp(Node *root){
    //check to see if its empty.
    if (root == nullptr) return nullptr;
    Node* newNode = nullptr;
    //check if its in int or string.
    if(root->tagged_union == ISINT){
        //create a new node with the proper data.
        newNode = new Node(root->data_int);
    }
    else{
        newNode = new Node(root->data_string);
    }
    //copy the left and right nodes.
    newNode->left = copyHelp(root->left);
    newNode->right = copyHelp(root->right);
    //reaturn the new node. 
    return newNode;
}
//assignment operator 
const SkewHeap& SkewHeap::operator=(const SkewHeap& rhs){
    //check if its empty then call delete on the root. 
    if(this != &rhs){
        if(empty()){
            m_heap = nullptr;
        }
        else{
        recursiveDelete(m_heap);
        }
        //set the priortiy and copy.
            priority = rhs.priority;
            m_heap = copyHelp(rhs.m_heap);
    }
    return *this;
}


// Priority function get and set
pri_fn SkewHeap::getPriFn() const{
    return priority;
}

//setter for the priority
void SkewHeap::setPriFn (pri_fn pri){
    //use copy constructor to make a new skewheap 
    SkewHeap newHeap(pri);
    //check if its empty and check the data.
    while(!empty()){
        
        if(m_heap->tagged_union == ISINT){
            //insert the heap with the correct data.
            newHeap.insert(m_heap->data_int);
       }
       else{
            newHeap.insert(m_heap->data_string);
       }
       //remove the top node. 
       removeTop();
    }
    *this = newHeap;
}

// Return true if the skew heap is empty
bool SkewHeap::empty() const{
    if(m_heap == nullptr){
        return true;
    }
    return false;
}

// Overloaded insertion operators: string data
void SkewHeap::insert(string data){
    //create a new node and merge it with the existing heap
    Node *temp = new Node(data);
    m_heap = merge(m_heap, temp);
    

}
//integer data.
void SkewHeap::insert(int data){
    Node *temp = new Node(data);
    m_heap = merge(m_heap, temp);
}

// Access highest priority element in the skew heap.
Node* SkewHeap::front() const{
    if(m_heap == nullptr){
        return nullptr;
    }
    //returns the top node. 
    return m_heap;
}

// Remove the highest priority element from the skew heap.
// didnt have temp.
void SkewHeap::removeTop(){
    //creates a temporary root node. 
    Node* root = m_heap;
    if(empty()){
        return;
    }
    //merge heap's left and right nodes and delete the root.
    m_heap = merge(m_heap->left, m_heap->right);
    delete root;
}

// Merge two heaps.  Merged heap in *this; sh is empty afterwards.
void SkewHeap::skewHeapMerge(SkewHeap& sh){
    if (*this->priority != sh.priority){
        throw domain_error("Can't merge due to same priority");
  }
    m_heap = merge(m_heap, sh.m_heap);
    //empty the sh.
    sh.m_heap = nullptr;
}

//merge helper function. takes in two nodes and returns a node.
Node* SkewHeap::merge(Node* p1, Node* p2){
    //create a temp node.
    Node *temp;
    //check the first node
    if(p1 == nullptr){
        return p2;
    }
    //check the second node. 
    if(p2 == nullptr){
        return p1;
    }
    //check the priorities 
    if (priority(p1) < priority(p2)){
        //swap the parents 
        temp = p1;
        p1 = p2;
        p2 = temp;
    }
    //swap the children 
    temp = p1->left;
    p1->left = p1->right;
    p1->right = temp;
    //recursively call merge on p1s left and p2.
    p1->left = merge(p1->left, p2);
    
    return p1;
}


// Print inorder traversal.
void SkewHeap::inorder() const{
    recursiveInorder(m_heap);
}

//inorder helper function
void SkewHeap::recursiveInorder(Node* other)const{
     if (other == nullptr){
        return;
    }
    else{
       cout << "("; 
       //recurse the left 
       recursiveInorder(other->left);
        //check the data type (string or int)
       if(other->tagged_union == ISINT){
           //print out data 
           cout << other->data_int;
       }
       else{
           cout << other->data_string;
       }
       //crecurse the right 
       recursiveInorder(other->right);
       cout << ")";
    }
}

// Dump the contents of the heap in decreasing priority order.
void SkewHeap::dump() const{
    //create a new skewheap using the copy constructor. 
    SkewHeap newHeap(*this);
    while(newHeap.m_heap != nullptr){
        //check the data and print the data.
        if(newHeap.m_heap->tagged_union == ISINT){
           cout << "Data is:   " << newHeap.m_heap->data_int;
       }
        else{
           cout << "Data is:    " << newHeap.m_heap->data_string;
      }
      //print the priority and remove the top so it could loop through the whole treap.
        cout << "    Priority is:    " << priority(newHeap.m_heap) << endl;
        newHeap.removeTop();
    }
}
