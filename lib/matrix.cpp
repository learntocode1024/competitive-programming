#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class matrix {
  vector<vector<T>> _data;
  int _col, _row;
public:
  matrix() : _row(), _col(), _data() {};
  matrix(int row, int col) : _row(row), _col(col), _data(row, vector<T>(col)) {};
  matrix(int rank) : _row(rank), _col(rank), _data(rank, vector<T>(rank)) {};
  static matrix E(int rank) {
    matrix ret(rank);
    for (int i = 0; i < rank; ++i) {
      ret[i][i] = 1;
    }
    return ret;
  }
  vector<T> &operator[](int k) {
    return _data[k];
  }
  const vector<T> &operator[](int k) const {
    return _data[k];
  }
  friend matrix operator* (const matrix& x, const matrix& y) {
    matrix ret(x._row, y._col);
    for (int i = 0; i < x._row; ++i) {
      for (int j = 0; j < y._col; ++j) {
        for (int k = 0; k < x._col; ++k) {
          ret[i][j] += x[i][k] * y[k][j];
        }
      }
    }
    return ret;
  }
  friend matrix operator+ (const matrix& x, const matrix& y) {
    matrix ret(x._row, y._col);
    for (int i = 0; i < x._row; ++i) {
      for (int j = 0; j < y._col; ++j) {
        ret[i][j] = x[i][j] + y[i][j];
      }
    }
    return ret;
  }
  friend T det(matrix x) {
    if (x._row != x._col) return 0;
    T sig = 1, ret = 1;
    int cur = 0;
    for (int i = 0; i < x._col; ++i) {
      int j;
      for (j = cur; j < x._row; ++j) {
        if (x._data[j][i] != 0) break;
      }
      if (j == x._row) continue;
      swap(x._data[j], x._data[cur]);
      if (j != cur) sig = -sig;
      for (++j; j < x._row; ++j) {
        if (x._data[j][i] != 0) {
          T fac = x._data[j][i] / x._data[cur][i];
          for (int k = i; k < x._col; ++k) {
            x._data[j][k] -= fac * x._data[cur][k];
          }
        }
      }
      ++cur;
    }
    for (int i = 0; i < x._col; ++i) {
      ret *= x[i][i];
    }
    return ret * sig;
  }
  friend matrix inv(matrix x) {
    matrix y = matrix::E(x._row);
    if (x._row != x._col) return matrix();
    int cur = 0;
    for (int i = 0; i < x._col; ++i) {
      int j;
      for (j = cur; j < x._row; ++j) {
        if (x._data[j][i] != 0) break;
      }
      if (j == x._row) continue;
      swap(x._data[j], x._data[cur]);
      swap(y._data[j], y._data[cur]);
      if (x._data[cur][i] != 1) {
        T fac = (T)1 / x._data[cur][i];
        for (int k = i; k < x._col; ++k) {
          x._data[cur][k] *= fac;
        }
        for (int k = 0; k < x._col; ++k) {
          y._data[cur][k] *= fac;
        }
      }
      for (j = 0; j < x._row; ++j) {
        if (j == cur) continue;
        if (x._data[j][i] != 0) {
          T fac = x._data[j][i];
          for (int k = i; k < x._col; ++k) {
            x._data[j][k] -= fac * x._data[cur][k];
          }
          for (int k = 0; k < x._col; ++k) {
            y._data[j][k] -= fac * y._data[cur][k];
          }
        }
      }
      ++cur;
    }
    if (cur != x._row) return matrix();
    return y;
  }
  void print() {
    if (!_col) cout << "No Solution\n";
    for (int i = 0; i < _row; ++i) {
      for (int j = 0; j < _col; ++j) {
        cout << _data[i][j] << ' ';
      }
      cout << '\n';
    }
    cerr << endl;
  }
};
