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
const int N = 5005;
vector<int> G[N];
int k;
int a[N][N/3];
int maxd[N/3];
inline i64 c2(i64 x) { return x * (x - 1) / 2; }

i64 ans = 0;
int t2[N][N];
void dfs1(int u, int fa) {
  a[u][0] = 1;
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    chkmax(maxd[u], maxd[v] + 1);
    for (int d = 1; d <= maxd[u]; ++d) {
      ans += t2[u][d] * a[v][d - 1];
      t2[u][d] += a[u][d] * a[v][d - 1];
      a[u][d] += a[v][d - 1];
    }
  }
}

void dfs2(int u, int fa) {
  if (u != 1) {
    for (int d = 1; d <= maxd[u]; ++d) {
      int tmp = a[fa][d - 1];
      if (d > 1) tmp -= a[u][d - 2];
      ans += tmp * t2[u][d];
      a[u][d] += tmp;
    }
  }
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs2(v, u);
  }
}

void solve() {
  int n;
  cin >> n;
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    G[u].pb(v);
    G[v].pb(u);
  }
  dfs1(1, 0);
  dfs2(1, 0);
  cout << ans << '\n';
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
