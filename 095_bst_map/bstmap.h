#ifndef __bstMAP_H__
#define __bstMAP_H__
#include <cstdlib>
#include <iostream>

#include "map.h"
using namespace std;
template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}
    Node(K k, V v, Node * left, Node * right) : key(k), value(v), left(left), right(right) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) { assign(rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      free(root);
      root = NULL;
      assign(rhs.root);
    }
    return *this;
  }
  ~BstMap() { free(root); }
  void assign(Node * curr) {
    if (curr != NULL) {
      assign(curr->left);
      assign(curr->right);
      add(curr->key, curr->value);
    }
  }
  void free(const Node * curr) {
    if (curr != NULL) {
      free(curr->left);
      free(curr->right);
      delete curr;
      curr = NULL;
    }
  }
  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else {
        curr = &(*curr)->right;
      }
    }
    *curr = new Node(key, value, NULL, NULL);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return curr->value;
      }
      if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    throw std::invalid_argument("No such key in the tree");
  }
  Node * FinMin(Node * current) {
    if (current->left != NULL)
      return FinMin(current->left);
    else
      return current;
  }
  Node * remove_helper(Node * curr, const K & key) {
    if (curr == NULL) {
      return NULL;
    }
    if (key < curr->key) {
      curr->left = remove_helper(curr->left, key);
    }
    else if (key > curr->key) {
      curr->right = remove_helper(curr->right, key);
    }
    else {
      if (curr->left == NULL && curr->right == NULL) {
        delete curr;
        curr = NULL;
      }
      else if (curr->left == NULL) {
        Node * temp = curr;
        curr = curr->right;
        delete temp;
      }
      else if (curr->right == NULL) {
        Node * temp = curr;
        curr = curr->left;
        delete temp;
      }
      else {
        Node * temp = FinMin(curr->right);
        curr->key = temp->key;
        curr->value = temp->value;
        curr->right = remove_helper(curr->right, temp->key);
      }
    }
    return curr;
  }
  virtual void remove(const K & key) { root = remove_helper(root, key); }
  void printHelper(Node * current) {
    if (current != NULL) {
      cout << current->key << "  ";
      printHelper(current->left);
      printHelper(current->right);
    }
  }
  void printtest() {
    printHelper(root);
    cout << "\n";
  }
};
#endif
