#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  if (r == 0) {
    rows = NULL;
  }
  else {
    rows = new IntArray *[r];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new IntArray(numColumns);
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
      rows[i] = new IntArray(rhs[i]);
    }
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    if (rhs.numRows == 0) {
      IntArray ** temp = NULL;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = temp;
    }
    else {
      IntArray ** temp = new IntArray *[rhs.numRows];
      for (int i = 0; i < rhs.numRows; i++) {
        temp[i] = new IntArray(rhs[i]);
      }
      this->~IntMatrix();
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = temp;
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}

int IntMatrix::getColumns() const {
  return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows);
  return *rows[index];
}

IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  if (numRows == rhs.numRows && (numColumns == rhs.numColumns)) {
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if ((*this)[i][j] != rhs[i][j]) {
          return false;
        }
      }
    }
  }

  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  IntMatrix sum(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      sum[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return sum;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  if (rhs.getRows() != 0 && rhs.getColumns() == 0) {
    s << "[ ";
    for (int i = 0; i < rhs.getRows(); i++) {
      if (i == rhs.getRows() - 1) {
        s << "{} ]";
        break;
      }
      s << "{},\n";
    }
    return s;
  }

  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << "{";

    for (int j = 0; j < rhs.getColumns(); j++) {
      if (j == rhs.getColumns() - 1) {
        s << rhs[i][j] << "},\n";
        break;
      }
      s << rhs[i][j] << ", ";
    }
  }
  s << "{";
  for (int j = 0; j < rhs.getColumns(); j++) {
    if (j == rhs.getColumns() - 1) {
      s << rhs[rhs.getRows() - 1][j] << "} ]";
      break;
    }
    s << rhs[rhs.getRows() - 1][j] << ", ";
  }
  return s;
}
