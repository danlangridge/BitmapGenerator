


struct BinaryTree {
  
public:
  void swapNodes(char* byteArray, unsigned indexI, unsigned indexJ);
  unsigned traverseToParent(unsigned currentNode);
  unsigned parent(unsigned currentNode) {
  char getParent(char* byteArray, unsigned currentNode);
  unsigned leftChild(unsigned currentNode);
  unsigned rightChild(unsigned currentNode);
  char* buildBinaryTree(char* byteArray);
};
