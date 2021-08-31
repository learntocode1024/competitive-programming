#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "modint"
#include "io"

using mint = MontgomeryModInt<1000000009>;

const int N = 20, S = 1 << N;
mint a[N + 1][S], b[N + 1][S], c[N + 1][S];

void fwt(mint *a, int len) {
  for (int i = 1; i < len; i <<= 1) {
    for (int j = 0; j < len; j += i << 1) {
      for (int k = j; k < j + i; ++k) {
        a[k + i] += a[k];
      }
    }
  }
}

void ifwt(mint *a, int len) {
  for (int i = 1; i < len; i <<= 1) {
    for (int j = 0; j < len; j += i << 1) {
      for (int k = j; k < j + i; ++k) {
        a[k + i] -= a[k];
      }
    }
  }
}

void solve() {
  int n = rd();
  int lim = 1 << n;
  for (int i = 0; i < lim; ++i) {
    a[__builtin_popcount(i)][i] = rd();
  }
  for (int i = 0; i < lim; ++i) {
    b[__builtin_popcount(i)][i] = rd();
  }
  for (int i = 0; i <= n; ++i) fwt(a[i], lim), fwt(b[i], lim);
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      for (int k = 0; k < lim; ++k) {
        c[i][k] += a[j][k] * b[i - j][k];
      }
    }
  }
  for (int i = 0; i <= n; ++i) ifwt(c[i], lim);
  for (int i = 0; i < lim; ++i) {
    cout << c[__builtin_popcount(i)][i] << ' ';
  }
  cout << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/