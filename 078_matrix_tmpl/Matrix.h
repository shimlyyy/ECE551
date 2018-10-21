#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}

  Matrix(int r, int c) : numRows(r), numColumns(c), rows(numRows) {
    for (int i = 0; i < numRows; ++i) {
      rows[i].resize(numColumns);
    }
  }

  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) { rows = rhs.rows; }

  ~Matrix() { rows.clear(); }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<std::vector<T> > temp(rhs.rows);  //(rhs.numRows);
      /* for (int i = 0; i < rhs.numRows; i++) {
        temp[i] = rhs.rows[i];
	}*/

      this->~Matrix();
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = temp;
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(0 <= index && index < numRows);
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(0 <= index && index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    /* if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }
   if (numRows == rhs.numRows && (numColumns == rhs.numColumns)) {
      for (int i = 0; i < numRows; i++) {
        if (rows[i] != rhs[i]) {
          return false;
        }
      }
      }*/
    if (rows != rhs.rows) {
      return false;
    }

    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix sum(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        sum.rows[i][j] = (*this)[i][j] + rhs.rows[i][j];
      }
    }
    return sum;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
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

#endif
