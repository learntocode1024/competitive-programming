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

#include <bits/stdc++.h>
using namespace std;

/********************************** buffer IO *********************************/

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
const int n = 6, N = n * 4;
map<pii, int> m;
int g[N][N];
pii rnk[N];
int tot = 0;
short lst[1 << N][N];
short ok[1 << N][N];
int dx[8] = {1, 2, -1, -2, 1, -2, -1, 2};
int dy[8] = {2, 1, -2, -1, -2, 1, 2, -1};
int _tot = 0;

bool dfs(int u, int l) {
  if (ok[u][l]) {
    return ok[u][l] == 1;
  }
  int v = u ^ (1 << l);
  for (int j = 0; j < N; ++j) {
    if (g[j][l] && (v >> j) & 1) {
      if (dfs(v, j)) {
        ok[u][l] = 1;
        lst[u][l] = j;
        return 1;
      }
    }
  }
  ok[u][l] = 2;
  return 0;
}

void print(int u, int l) {
  if (!u) return;
  int v = u ^ (1 << l);
  cout << rnk[l].fi << ' ' << rnk[l].se << '\n';
  print(v, lst[u][l]);
}

void solve() {
  for (int i = 1; i <= 4; ++i) for (int j = 1; j <= n; ++j) {
    m[mkp(i, j)] = tot;
    rnk[tot] = mkp(i, j);
    ++tot;
  }
  FOR(i, 0, N) {
    ok[1 << i][i] = 1;
    lst[1 << i][i] = i;
  }
  for (int i = 1; i <= 4; ++i) for (int j = 1; j <= n; ++j) {
    for (int k = 0; k < 8; ++k) {
      int x = i + dx[k], y = j + dy[k];
      if (x < 1 || y < 1 || x > 4 || y > n) continue;
      pii u = mkp(i, j), v = mkp(x, y);
      g[m[u]][m[v]] = 1;
      g[m[v]][m[u]] = 1;
    }
  }
  for (int i = 0; i < N; ++i) {
    if (dfs((1 << N) - 1, i)) {
      print((1 << N) - 1, i);
      return;
    }
  }
}

int main() {
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  cout << _tot << '\n';
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
