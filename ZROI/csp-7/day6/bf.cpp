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
const int N = 2e5+5;
vector<int> g[N];

int x[N], y[N];

int sz[N];
int ans = 1e7;
int n;

inline int getans(int a, int b, int c) {
  return max(a, max(b, c)) - min(a, min(b, c));
}

bool vis[N];

void dfs1(int u, int fa) {
  vis[u] = 1;
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    sz[u] += sz[v];
  }
}

int I, J;

void _solve() {
  FOR(i, 1, n + 1) vis[i] = 0, g[i].clear(), sz[i] = 0;
  FOR(i, 1, n) {
    if (i == I || i == J) continue;
    int u = x[i], v = y[i];
    g[u].pb(v);
    g[v].pb(u);
  }
  int s[3];
  int c = 0;
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      dfs1(i, 0);
      s[c++] = sz[i];
    }
  }
  chkmin(ans, getans(s[1], s[2], s[0]));
}

void solve() {
  cin >> n;
  FOR(i, 1, n) {
    cin >> x[i] >> y[i];
  }
  for (I = 1; I <= n; ++I) {
    for (J = I + 1; J < n; ++J) {
      _solve();
    }
  }
  cout << ans << '\n';
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
