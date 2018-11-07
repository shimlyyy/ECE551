#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <iostream>

#include "map.h"
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
    Node() {}
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else if (key == (*current)->key) {
        (*current)->value = value;
      }
      else {
        current = &(*current)->right;
      }
    }
    *current = new Node(key, value);
  }
  /*  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    try {
      if (current == NULL) {
        throw std::invalid_argument("no such key");
      }
    }
    catch (std::invalid_argument & ia) {
      std::cerr << " Invalid_argument " << ia.what() << std::endl;
    }
    }*/
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

  /* virtual void remove(const K & key) {
    Node ** current = &root;
    while ((*current) != NULL) {
      if (key == (*current)->key) {
        if ((*current)->left == NULL) {
          Node * temp = (*current);
          (*current) = (*current)->right;
          delete temp;
        }
        else if ((*current)->right == NULL) {
          Node * temp = (*current);
          (*current) = (*current)->left;
          delete temp;
        }
        else {
          Node * parent = *current;
          Node * child = (*current)->right;
          while (child->left != NULL) {
            parent = child;
            child = child->left;
          }
          (*current)->key = child->key;
          (*current)->value = child->value;
          if (parent == (*current)) {
            (*current)->right = child->right;
          }
          else {
            parent->left = child->right;
          }
          delete child;
        }
      }
      else if (key < (*current)->key) {
        *current = (*current)->left;
      }
      else {
        *current = (*current)->right;
      }
    }
    }*/

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

  Node * FinMin(Node * current) {
    if (current->left != NULL)
      return FinMin(current->left);
    else
      return current;
  }

  void destory(Node * node) {
    if (node != NULL) {
      destory(node->left);
      destory(node->right);
      delete node;
    }
  }
  virtual ~BstMap() { destory(root); }
  void copytree(Node * curr) {
    if (curr != NULL) {
      copytree(curr->left);
      copytree(curr->right);
      add(curr->key, curr->value);
    }
  }

  BstMap(const BstMap & rhs) { copytree(rhs.root); }
  void swap(BstMap & rhs) { std::swap(this->root, rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    BstMap temp(rhs);
    swap(temp);
    return *this;
  }
};
#endif
