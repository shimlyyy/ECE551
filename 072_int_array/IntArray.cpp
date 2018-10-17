#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {}

IntArray::IntArray(int n) {
  if (n <= 0) {
    data = NULL;
    numElements = 0;
  }
  else {
    data = new int[n];
    numElements = n;
  }
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < numElements);
  return data[index];
}

int & IntArray::operator[](int index) {
  assert(index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements == 0 && rhs.numElements == 0) {
    return true;
  }
  if (numElements == rhs.numElements) {
    int i = 0;
    while (data[i] == rhs.data[i]) {
      if (i == numElements - 1) {
        return true;
      }
      i++;
    }
  }
  return false;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return true;
  }

  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return true;
    }
  }

  return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() <= 0) {
    s << "{}";
    return s;
  }
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    if (i == rhs.size() - 1) {
      s << rhs.operator[](i) << "}";
      break;
    }
    s << rhs.operator[](i) << ", ";
  }
  return s;
}
