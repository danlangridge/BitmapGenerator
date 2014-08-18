#include "BinaryTree.h"


void BinaryTree::swapNodes(char* byteArray, unsigned indexI, unsigned indexJ) {
  char tempd = byteArray[indexI];
  byteArray[indexI] = byteArray[indexJ];
  byteArray[indexJ] = tempd;   
  return;  
}

unsigned BinaryTree::parent(unsigned currentNode) {
  if (currentNode == 1) return currentNode; 
  return currentNode/2; 
}

unsigned BinaryTree::leftChild(unsigned currentNode) {
  return currentNode*2; 
}

unsigned BinaryTree::rightChild(unsigned currentNode) {
  return currentNode*2+1; 
}

unsigned BinaryTree::getParent(char* byteArray, unsigned currentNode) {
  return byteArray[currentNode/2];
}

char* BinaryTree::buildBinaryTree(char* byteArray) {
  char* binaryTree = new char[sizeof(byteArray)]; 
  return new char();
}
