#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <iostream>
#include <stdexcept>

#include "set.h"
template<typename T>
class BstSet : public Set<T>
{
 private:
  class Node
  {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & key) : key(key), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) {
    root = NULL;
    assign(rhs.root);
  }
  void assign(Node * curr) {
    if (curr != NULL) {
      assign(curr->left);
      assign(curr->right);
      add(curr->key);
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
  virtual ~BstSet() { free(root); }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      free(root);
      root = NULL;
      assign(rhs.root);
    }
    return *this;
  }

  virtual void add(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else {
        curr = &(*curr)->right;
      }
    }
    *curr = new Node(key);
  }
  virtual bool contains(const T & key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return true;
      }
      if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    return false;
  }

  Node * FinMin(Node * current) {
    if (current->left != NULL)
      return FinMin(current->left);
    else
      return current;
  }
  Node * remove_helper(Node * curr, const T & key) {
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
        curr->right = remove_helper(curr->right, temp->key);
      }
    }
    return curr;
  }

  virtual void remove(const T & key) { root = remove_helper(root, key); }
  void printHelper(Node * current) {
    if (current != NULL) {
      std::cout << current->key << "  ";
      printHelper(current->left);
      printHelper(current->right);
    }
  }
  void printtest() {
    printHelper(root);
    std::cout << "\n";
  }
};
#endif
