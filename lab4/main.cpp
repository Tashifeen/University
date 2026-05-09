/* Abstract base class for Huffman tree */
class HuffmanTree {
protected:
  unsigned occurrence_frequency;
public:
  int occurrence() const { return occurrence_frequency; }

  virtual void extractCodes(std::map<char, std::string>& codeMap, std::string codeString) const = 0
};

/* Leaf node for Huffman tree */
class HuffmanTreeLeaf: public HuffmanTree {
private:
  char character;
public:
  HuffmanTreeLeaf(char ch, int occ) {
    ...
  }
  ...
};

/* Non-leaf node */
class HuffmanTreeNode: public HuffmanTree {
private:
  HuffmanTree* left_child;
  HuffmanTree* right_child;
public:
  HuffmanTreeNode(HuffmanTree* left, HuffmanTree* right) {
    ...
  }
  ...
};


/* Class used to sort Huffman subtrees */
class CompareHuffman {
public:
  bool operator()(HuffmanTree* ht1, HuffmanTree* ht2) {
    return ht1->occurrence() > ht2->occurrence();
  }
};

int main() {
	// Step 2 & 3: build
}   
