/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 *
 *********************************************************************/

#include <bits/stdc++.h>
using namespace std;

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
// #define MULTI
const int n = 8, N = 1 << n;

int a[1<<n], b[n + 1][N], ans[N + 1];
int rch[N + 1];

inline void work() {
  FOR(i, 0, N) b[0][i] = a[i], rch[i + 1] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < (1 << (n - i)); ++j) {
      b[i][j] = max(b[i - 1][j << 1], b[i - 1][j << 1 | 1]);
      rch[b[i][j]] = i;
    }
  }
}

void sol() {
  for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
      swap(a[i], a[j]);
      work();
      chkmax(ans[a[i]], rch[a[i]]);
      chkmax(ans[a[j]], rch[a[j]]);
      swap(a[i], a[j]);
    }
  }
  FOR(i, 0, N) cerr << ans[i + 1] << ' ';
  cerr << '\n';
}

void solve() {
  mt19937 gen(chrono::steady_clock().now().time_since_epoch().count());
  iota(a, a + N, 1);
  shuffle(a, a + N, gen);
  cout << n << '\n';
  FOR(i, 0, N) cout << a[i] << ' ';
  cout << '\n';
  sol();
}

int main() {
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
