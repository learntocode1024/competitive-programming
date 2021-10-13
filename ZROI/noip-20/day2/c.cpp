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

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
}  // namespace IO

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
using IO::rd;
// #define MULTI
const int N = 3e5+5;
vector<int> g[N];
int dp[N];
int a, b, n;

namespace task1 {
void dfs(int u, int fa) {
  vector<int> V;
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs(v, u);
    V.pb(dp[v]);
  }
  sort(V.begin(), V.end());
  int t = V.size();
  if (t == 0) dp[u] = 0;
  else {
    dp[u] = 0;
    for (auto v : V) {
      chkmax(dp[u], v + t--);
    }
  }
}
inline void work() {
  dfs(a, b);
  dfs(b, a);
  cout << max(dp[a], dp[b]) << '\n';
}
}

namespace task2 {
int ban1, ban2;
int s[N], tot;
bool dfs1(int u, int fa) {
  s[++tot] = u;
  if (u == b) return 1;
  for (auto v : g[u]) {
    if (v != fa) {
      if (dfs1(v, u)) return 1;
    }
  }
  --tot;
  return 0;
}
void dfs(int u, int fa) {
  vector<int> V;
  for (auto v : g[u]) {
    if (v == fa) continue;
    if (v == ban1 && u == ban2) continue;
    if (u == ban1 && v == ban2) continue;
    dfs(v, u);
    V.pb(dp[v]);
  }
  sort(V.begin(), V.end());
  int t = V.size();
  if (t == 0) dp[u] = 0;
  else {
    dp[u] = 0;
    for (auto v : V) {
      chkmax(dp[u], v + t--);
    }
  }
}
inline void work() {
  dfs1(a, 0);
  // for (int i = 1; i < tot; ++i) {
  //   ban1 = s[i], ban2 = s[i + 1];
  //   dfs(a, 0);
  //   dfs(b, 0);
  //   chkmin(ans, max(dp[a], dp[b]));
  // }
  int l = 1, r = tot;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    ban1 = s[mid], ban2 = s[mid + 1];
    dfs(a, 0);
    dfs(b, 0);
    if (dp[a] > dp[b]) r = mid;
    else l = mid;
  }
  int ans = 1e7;
  for (int i = max(1, l - 10); i < min(tot, l + 10); ++i) {
    ban1 = s[i], ban2 = s[i + 1];
    dfs(a, 0), dfs(b, 0);
    chkmin(ans, max(dp[a], dp[b]));
  }
  cout << ans << '\n';
}
}

void solve() {
  n = rd();
  a = rd(), b = rd();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    g[u].pb(v);
    g[v].pb(u);
  }
  for (auto v : g[a]) {
    if (v == b) {
      task1::work();
      return;
    }
  }
  task2::work();
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
