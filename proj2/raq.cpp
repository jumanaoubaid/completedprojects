// jumana oubaid
//raq.cpp
//10/8/19
#include <vector>
#include <cmath>
#include <array>
#include <iostream>
#include "raq.h"
const int THIRDNUM = 3;
//Dynamic processing constructor
RAQ::RAQ(std::vector<float> data){
  //set the matrix to the size of the data.
  m_matrix.resize(data.size());
  //loop throught the data and set the first index of the matrix.
  for(float i = 0; i < data.size(); i++){
    m_matrix[i].resize(data.size());
    m_matrix[i][i] = data[i];
    float numerator = 0;
    float denominator = 1;
    for(float j = i; j < data.size(); j++){
      //j has to be greater than or equal to i
      if (j >= i){
	//add up the numbers at data to the numerator.
	numerator += data[j];
	//set the averages to the indexes of the matrix and update denominator.
	m_matrix[i][j] = (numerator / denominator);
	denominator++;
      }
    }
  }
}
float RAQ::query(int i, int j) const{
  //domain error
  if (j < i){
    throw std::domain_error("Out of bounds.");
  }
  //pull the index thats wanted out of the matrix. 
  return m_matrix[i][j];
}


void RAQ::dump() const{
  //loop through the matrix
  for (int i = 0; i < m_matrix.size(); i++){
    for ( int j = 0; j < m_matrix[i].size(); j++){
      //to create the correct shape i is greater than j.
      if(i <= j)
	std::cout << m_matrix[i][j] << " " ;
     
    }
    std:: cout << std::endl;
  }
}

BlockRAQ::BlockRAQ(std::vector<float> data){
  //create a copy of the data into another vector to be used in query.
  for(float i = 0; i < data.size(); i++){ 
    m_dataCopy.push_back(data[i]);
  }
  //get the size of the block by taking the square root of the num of items in data.
  m_sizeOfBlock = sqrt(data.size());
  //the number of blocks by dividing the size of the data by the size of the block
  m_numOfBlock = (data.size() / m_sizeOfBlock);
  int  m_sumOfBlock = 0;
  int m_count = 0;
  //loop through the number of blocks and add up the data.
  for(int i = 0; i < m_numOfBlock; i++){
      for(int j = 0; j < m_sizeOfBlock; j++){
	m_sumOfBlock += data[m_count];
	m_count++;
      }
      //push the sums into a vector that holds the sums
      m_storage.push_back(m_sumOfBlock);
      //set the sum variable back to 0 so that it can add up the new blocks. 
      m_sumOfBlock = 0;
  } 
}



float BlockRAQ::query(int i, int j) const{
  if (j < i){
    throw std::domain_error("Out of bounds.");
  }
  
  int lowerCount = i;
  int upperCount = j;
  int m_sumOfBlock = 0;

  //if all the blocks are the same (j-i) size add up the data. 
  if((j - i) == 1){
    m_sumOfBlock += m_dataCopy[i];
    m_sumOfBlock += m_dataCopy[j];
  }
  //if(m_sizeOfBlock == 1){
  //for(int i = i; i < j; i++){
  //  m_sumOfBlock += m_dataCopy[i];
  //}
  //}

  //if there are three items in the vector, add them all up.
  else if(m_dataCopy.size() == THIRDNUM){
    for(int i = 0; i < THIRDNUM; i++){
      m_sumOfBlock += m_dataCopy[i];
    }
  }
  
  else{
    //add up the blocks and increment lowerCount from i to the start of the block.
    for (int k = i; (k % m_sizeOfBlock) != 0; k++){
      lowerCount++;
      //add up the data.
      m_sumOfBlock += m_dataCopy[k];
    }

    //loop through from j to the end of the full block.
    for (int m = j; (m % m_sizeOfBlock) != (m_sizeOfBlock - 1) && m != -1 ; m--){
      //decrement upperCount.
      upperCount--;
      //add up the data.
      m_sumOfBlock += m_dataCopy[m];
    }
    //add up the full blocks.
    for (int n = lowerCount; n < upperCount; n += m_sizeOfBlock){
      //add the sums from the storage vector.
      int startNewBlock = (n / m_sizeOfBlock);
      m_sumOfBlock += m_storage[startNewBlock];
    }
   
  }
  //create a variable and set it to how many elements there are.
  float denominator = (j - i) + 1;
  return (m_sumOfBlock / denominator);

  
}

void BlockRAQ::dump() const{
  //print out the blocks, sizes and numbers, and averages.
  std::cout << "Num blocks: " << m_numOfBlock << std::endl;
  std::cout << "Block size: " << m_sizeOfBlock << std::endl;
  std::cout << "Block sums: " << std::endl;
  for (int i = 0; i < m_storage.size(); i++){
    std::cout << m_storage[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Block averages: " << std::endl;
  for(int i = 0; i < m_storage.size(); i++){
    std:: cout << m_storage[i] / m_sizeOfBlock << " ";
  }
  std::cout << std::endl;

}






