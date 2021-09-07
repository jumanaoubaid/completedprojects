//TypedHeap.cpp
/*
Jumana Oubaid 
project 4 
due: 11/19/19
*/
using namespace std;
#include <cctype>
#include <string>
#include "TypedHeap.h"

//explicit TypedHeap::TypedHeap(pri_fn pri) : intHeap(pri), stringHeap(pri), totalHeap(pri) {};

// Provide a vector of strings.  For each string, deterimine whether
// it represents an integer; if so, insert it into the integer skew
// heap.  Otherwise, insert it into the string skew heap.
void TypedHeap::insertToHeaps(vector<string> vec){
    //set a flag; 
    bool flag = true; 
    //loop through the whole vector
    for(int i = 0; i < vec.size(); i++){
        //set the flag to true.
        flag = true;
        //loop through each index in the vector.
        for(int j = 0; j < vec.at(i).length(); j++){
            //check if each character is a number.
            if(isdigit(vec.at(i).at(j)) == false){
                //set the flag to false. 
                flag = false;
            }
        }
        //if the flag is true insert the digit into the integer heap.
        if(flag == true){
            intHeap.insert(stoi(vec.at(i)));
        }
        else{
            //if its false enter the string into the string heap.
            stringHeap.insert(vec.at(i));
        }
    }
}

// Merge the integer and string heaps; save in totalHeap.
//After combineHeaps() is called, the merged heap will be in totalHeap and the string and integer heaps will be empty.
void TypedHeap::combineHeaps(){
    //call the merging function on both int and string heaps and set it in totalheap.
    totalHeap.skewHeapMerge(intHeap);
    totalHeap.skewHeapMerge(stringHeap);
}

// Print all three heaps (integer, string, total).
void TypedHeap::printHeaps() const{ 
    cout << endl;
    //call the dumpfunction on each heap.
    cout << "IntHeap Holds: " << endl;
    intHeap.dump();
    cout << "StringHeap Holds: " << endl;
    stringHeap.dump();
    cout << "TotalHeap Holds: " << endl;
    totalHeap.dump();
    
}

// Change the priority function.
void TypedHeap::changePriority(pri_fn pri){
    //call the set priority function to each of the skewheaps.
    intHeap.setPriFn(pri);
    stringHeap.setPriFn(pri);
    totalHeap.setPriFn(pri);
}