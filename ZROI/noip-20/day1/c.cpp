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
const int N = 8e5+5;
vector<int> g[N];
int n, k;

int dp[N], sz[N];

void dfs(int u) {
  int ch = g[u].size();
  sz[u] = 1;
  int s = 0;
  for (auto v : g[u]) {
    dfs(v);
    sz[u] += sz[v];
    s += dp[v];
    if (sz[v] >= k + 1) chkmax(dp[u], dp[v] + 1);
  }
  chkmax(dp[u], s);
  if (ch >= k) {
    int t = 0;
    bool lss = 0;
    for (auto v : g[u]) {
      if (sz[v] >= k + 1) {
        if (dp[v] > 0) t += dp[v];
        else lss = 1;
      } else if (sz[v] >= 2) {
        lss = 1;
      }
    }
    if (lss) {
      chkmax(dp[u], t + 1);
    }
  }
}

void solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) g[i].clear();
  for (int i = 2, f; i <= n; ++i) {
    cin >> f;
    g[f].pb(i);
  }
    FOR(i, 1, n + 1) dp[i] = 0;
    dfs(1);
    cout << dp[1] << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef MULTI
  int T;
  cin >> T;
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
