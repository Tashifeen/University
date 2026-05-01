#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DisjointSets {
public:
  DisjointSets(unsigned numElements): num_elements(numElements) {
    s = new int[numElements];
    for(unsigned i=0; i<numElements; i++)
      s[i] = -1;                   // roots are negative number
  }

  ~DisjointSets() {delete[] s;}

  void union_(int root1, int root2) {
    if (s[root2]<s[root1]) {         // root2 is deeper
      s[root1] = root2;              // make root2 the root$\pause$
    } else {
      if (s[root1]==s[root2])      
	s[root1]--;                // update height if same
      s[root2] = root1;            // make root1 new root
    }
  }

  int find(int index) {
    if (s[index]<0)
      return index;
    else
      return s[index] = find(s[index]);
  }

  unsigned size() const {return num_elements;}

private:
  unsigned num_elements;
  int* s;
};

#endif
