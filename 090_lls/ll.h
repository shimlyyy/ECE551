#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
struct overbound : public std::exception {
  const char * what() const throw() { return "Overbound\n"; }
};
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & d, Node * a, Node * b) : data(d), next(a), prev(b) {}
    // Node(const T & d, Node *a):data(d),next(a),prev(NULL){}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    Node ** current = &head;
    while ((*current) != NULL && (*current)->data != item) {
      current = &(*current)->next;
    }
    if ((*current) == NULL) {
      return false;
    }
    Node * temp = (*current);

    if ((*current)->next == NULL) {
      tail = (*current)->prev;
    }
    else {
      (*current)->next->prev = (*current)->prev;
    }
    *current = (*current)->next;
    size--;
    delete temp;
    return true;
  }
  T & operator[](int index) {
    try {
      if (index < 0 || index >= size) {
        throw overbound();
      }
    }
    catch (std::exception & e) {
      std::cerr << "exception caught: " << e.what() << '\n';
      exit(EXIT_FAILURE);
    }
    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  const T & operator[](int index) const {
    try {
      if (index < 0 || index >= size) {
        throw overbound();
      }
    }
    catch (std::exception & e) {
      std::cerr << "exception caught: " << e.what() << '\n';
      exit(EXIT_FAILURE);
    }
    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  int find(const T & item) const {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }

  LinkedList(const LinkedList & rhs) {
    size = 0;
    head = NULL;
    tail = NULL;

    for (int i = 0; i < rhs.size; i++) {
      (*this).addBack(rhs[i]);
    }
  }
  void swap(LinkedList & rhs) {
    std::swap(this->size, rhs.size);
    std::swap(this->head, rhs.head);
    std::swap(this->tail, rhs.tail);
  }
  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList temp(rhs);
    swap(temp);
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
  }

  int getSize() const { return size; }
  friend void testList(void);
};
#endif
