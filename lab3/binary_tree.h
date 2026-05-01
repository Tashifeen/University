#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
using namespace std;

template <typename T>
class binary_tree {
private:
  class Node {
  public:
    T element;
    Node* parent;
    Node* left = 0;
    Node* right = 0;

    Node(const T& value, Node* parent_node) {
      element = value;
      parent = parent_node;
    }
  };

  unsigned no_elements = 0;
  Node* root = 0;

public:

  class iterator {
    Node* current;
  public:
    iterator(Node* node) {current=node;}
    T operator*() const {return current->element;}
    iterator operator++() {
      current = successor(current);
      return *this;
    }
    bool operator!=(const iterator& other) {
      return current!=other.current;
    }
  };

  binary_tree(): no_elements(0), root(0) {}

  ~binary_tree() {clean_up(root);}

  void clean_up(Node* node) {
    if (node==0)
      return;
    clean_up(node->left);
    clean_up(node->right);
    delete node;
  }


  pair<iterator, bool> insert(const T& element) {
    if (no_elements==0) {
      root = new Node(element, 0);
       ++no_elements;
       return pair<iterator, bool>(iterator(root), true);
    }
    Node* parent = 0;
    Node* current = root;
    while(current != 0) {
      if (current->element == element) {
	return pair<iterator, bool>(iterator(0), false);
      }
      parent = current;
      if (element < current->element) {
	current = current->left;
      } else {
	current = current->right;
      }
    }
    current = new Node(element, parent);
    if (element < parent->element) {
      parent->left = current;
    } else {
      parent->right = current;
    }
    ++no_elements;
    return pair<iterator, bool>(iterator(current), true);
  }

  inline
  unsigned size() const {return no_elements;}

  inline
  void show_tree() const {
    cout << show_subtree(root) << endl;
  }
  
  string show_subtree(Node* node) const {
    if (node==0) {
      return "*";
    } else {
      return "(" + to_string(node->element) + ";" + show_subtree(node->left)
	+ "," + show_subtree(node->right) + ")";
    }
  }

  iterator find(const T& element) {
    Node* current = root;
    while (current!=0) {
      if (current->element == element) {
	return iterator(current);
      }
      if (element < current->element) {
	current = current->left;
      } else {
	current = current->right;
      }
    }
    return iterator(0);
  }

  static Node* successor(Node* current) {
    Node* next;
    if (current->right != 0) {
      next = current->right;
      while (next->left != 0) {
	next = next->left;
      }
      return next;
    }
    next = current;
    while(next->parent != 0) {
      if (next->parent->right == next) {
	next = next->parent;
      } else {
	return next->parent;
      }
    }
    return 0;
  }



  iterator begin() {
    if (root==0)
      return iterator(0);
    Node* current = root;
    while (current->left != 0) {
      current = current->left;
    }
    return iterator(current);
  }
  
  iterator end() {return iterator(0);}

  int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][255]) {
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->element);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
    
    return left + width + right;
  }

  void print_tree(){
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(root, 0, 0, 0, s);

    for (int i = 0; i < 10; i++)
        printf("%s\n", s[i]);
  }

  int compute_total_depth(Node* node, int depth) const {
      if (node == 0) return 0;
      return depth
           + compute_total_depth(node->left, depth + 1)
           + compute_total_depth(node->right, depth + 1);
  }
  
  double average_depth() const {
      if (no_elements == 0) return 0.0;
      int total = compute_total_depth(root, 0);
      return double(total) / no_elements;
  }
  

  

};


#endif
