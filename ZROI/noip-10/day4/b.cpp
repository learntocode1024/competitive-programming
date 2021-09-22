/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
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
const int N = 4005;
int n;
int a[N*N/4];

namespace bf { 
int c[N][N], b[N][N];
void solve() {
  int tot = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; j += 2) {
      c[i][j] = ::a[tot++];
      if (j == i + 1) b[i][j] = c[i][j];
    }
  }
  for (int len = 4; len <= n; len += 2) {
    for (int i = 0; i + len <= n; ++i) {
      int j = i + len - 1;
      int cur = max(c[i][j], b[i+1][j-1]);
      for (int k = i + 1; k < j; k += 2) {
        chkmin(cur, max(b[i][k], b[k+1][j]));
      }
      b[i][j] = cur;
    }
  }
  cout << b[0][n-1] << '\n';
}
}

void solve() {
  cin >> n;
  FOR(i, 0, n*n/4) cin >> a[i];
  
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
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
