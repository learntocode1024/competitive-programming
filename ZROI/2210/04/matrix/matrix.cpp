#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)

int square_mul_normal() {
  int n = getrow(0), m = getcol(1);
  setmatrix(2, n, n);
  setmatrix(3, n, m);
  for (int j = 0; j < m; j += n) {
    copymatrix(2, 0, 0, 1, 0, n-1, j, min(j + n, m) - 1);
    mulmatrix(0, 2, 2);
    copymatrix(3, 0, j, 2, 0, n-1, 0, min(n, m - j) - 1);
  }
  return 3;
}

int mat;

void inv(int x, int n) {
  if (n == 1) {
    setnummatrix(1, x, 0, 0);
    divnum(0, 1, 1);
    setmatrixnum1(x, 0, 0, 1);
  }
  if (n == 2) {
    setnummatrix(1, x, 0, 0);
    setnummatrix(2, x, 0, 1);
    setnummatrix(3, x, 1, 1);
    divnum(0, 1, 1);
    divnum(0, 3, 3);
    mulnum(2, 1, 2);
    mulnum(2, 3, 2);
    subnum(4, 2, 2);
    setmatrixnum1(x, 0, 0, 1);
    setmatrixnum1(x, 0, 1, 2);
    setmatrixnum1(x, 1, 1, 3);
  }
  int m = n / 2;
  int l = ++mat, r = ++mat, u = ++mat;
  setmatrix(l, m, m);
  setmatrix(r, n-m, n-m);
  setmatrix(u, m, n-m);
  copymatrix(l, 0, 0, x, 0, m-1, 0, m-1);
  copymatrix(r, 0, 0, x, m, n-1, m, n-1);
  copymatrix(u, 0, 0, x, 0, m-1, m, n-1);
  inv(l, m);
  inv(r, n-m);
  
}

int upper_inverse() {
  setnum(0, 1);
  setnum(4, 0);
  mat = 0;
  inv(0, getrow(0));
  return 0;
}

std::vector<int> LUP_decomposition() {
return {};
}
int det() {
return 0;
}
int LU_to_mul() {
return 0;
}
int inverse_to_mul() {
return 0;
}
int shortest_path() {
  int n = getrow(0);
  setmatrix(1, n, n);
  setmatrix(2, n, n);
  copymatrix(1, 0, 0, 0, 0, n-1, 0, n-1);
  FOR(i, 0, n) setmatrixnum(2, i, i, 1);
  int x = n;
  while (x) {
    if (x & 1) mulmatrix(2, 1, 2);
    mulmatrix(1, 1, 1);
    x >>= 1;
  }
  copymatrix(1, 0, 0, 0, 0, n-1, 0, n-1);
  setnum(0, 1);
  FOR(i, 0, n) {
    setnummatrix(1, 1, i, i);
    subnum(1, 0, 1);
    setnum(1000, i);
    setmatrixnum1(1, 1000, 1000, 1);
    setnummatrix(1, 2, i, i);
    subnum(1, 0, 1);
    setmatrixnum1(2, 1000, 1000, 1);
  } // -1
  inverse(1, 1);
  mulmatrix(2, 1, 1);
  setnum(0, n);
  FOR(i, 0, n) FOR(j, 0, n) {
    if (i == j) setmatrixnum(1, i, j, 1);
    else {
      setnummatrix(1, 1, i, j);
      subnum(0, 1, 1);
    setnum(1000, i);
    setnum(1001, j);
      setmatrixnum1(1, 1000, 1001, 1);
    }
  } // n - a[u][v]
  return 1;
}