#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 1e4+5, K = 100;
int a[K][N], b[K][N<<1], p[K][N<<1], l[K];

int query(int x, int k) {
  int p = lower_bound(b[0], b[0] + l[0], x) - b[0];
  for (int i = 0; i < k; ++i) {
    ``
  }
}

void solve() {
  int n = rd(), k = rd(), q = rd(), d = rd();
  FOR(i, 0, k) FOR(j, 0, n) a[i][j] = rd();
  FOR(i, 0, n) b[k-1][i] = a[k-1][i];
  l[k-1] = n;
  ROF(_k, 0, k - 1) {
    l[_k] = n + l[_k+1] / 2;
    int l1 = l[_k], l2 = l[_k + 1];
    int p1 = n - 1, p2 = (l2 - 1) & (0xfffffffe);
    for (int i = l[_k] - 1; i >= 0; --i) {
      if (a[_k][p1] >= b[_k+1][p2]) { // type 1
        b[_k][i] = a[_k][p1];
        p[_k][i] = l2;
        l1 = i;
        --p1;
      } else { // type 2
        b[_k][i] = b[_k+1][p2];
        p[_k][i] = l1;
        l2 = p2;
        p2 -= 2;
      }
    }
  } // build
  FOR(i, 0, q) {
    query(rd());
  }
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

