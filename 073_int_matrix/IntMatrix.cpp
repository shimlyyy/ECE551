#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  if (r == 0) {
    rows = NULL;
  }
  else {
    rows = new IntArray *[r];
    for (int i = 0; i < r; i++) {
      if (c == 0) {
        rows[i] = new IntArray();
      }
      rows[i] = new IntArray(c);
    }
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
  if (numRows == 0) {
    rows = NULL;
  }
  else {
    rows = new IntArray *[numRows];
    for (int i = 0; i < numRows; i++) {
      if (numColumns == 0) {
        rows[i] = new IntArray();
      }
      else {
        rows[i] = new IntArray(numColumns);
        for (int j = 0; j < numColumns; j++) {
          rows[i][j] = rhs.rows[i][j];
        }
      }
    }
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete[] rows[i];
  }
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    if (rhs.numRows == 0) {
      rows = NULL;
    }
    else {
      rows = new IntArray *[rhs.numRows];
      for (int i = 0; i < rhs.numRows; i++) {
        if (rhs.numColumns == 0) {
          ro rows[i] = new IntArray(rhs.numColumns);
        }

        int IntMatrix::getRows() const {}
        int IntMatrix::getColumns() const {}
        const IntArray & IntMatrix::operator[](int index) const {}
        IntArray & IntMatrix::operator[](int index) {}

        bool IntMatrix::operator==(const IntMatrix & rhs) const {}

        IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {}

        std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {}
