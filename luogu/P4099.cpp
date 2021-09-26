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
#define MULTI
const int N = 1005;
vector<int> G[N];

int mod = 1000000007;

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

void solve() {
  int n;
  cin >> n;
  FOR(i, 1, n + 1) G[i].clear();
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    G[u].pb(v);
    G[v].pb(u);
  }
  dfs(1, 0);
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
