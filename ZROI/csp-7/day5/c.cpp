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
#include <queue>
#include <set>
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
const int N = 50005, M = 200005;
int n, m;
pii e[M];
vector<int> G[N], g[N];
int a[N], rnk[N];
set<pii> edge;
int in[N];

void topo() {
  queue<int> q;
  FOR(i, 1, n + 1) if (!in[i]) q.push(i);
  for (int i = 1; i <= n; ++i) {
    a[i] = q.front();
    int u = a[i];
    rnk[u] = i;
    q.pop();
    for (auto v : G[u]) {
      --in[v];
      if (in[v] == 0) q.push(v);
    }
  }
}

int l1[N], l2[N];
int d1[N], d2[N];

void solve() {
  n = rd(), m = rd();
  FOR(i, 0, m) {
    int u = rd(), v = rd();
    e[i] = mkp(u, v);
    if (edge.find(e[i]) == edge.end()) {
      G[u].pb(v);
      g[v].pb(u);
      ++in[v];
      edge.insert(e[i]);
    }
  }
  topo();
  int col = 1;
  // for (int i = 1; i <= n; ++i) { // layer 1
  //   int v = a[i];
  //   for (auto u : g[v]) {
  //     if (l1[u] == col) chkmax(d1[v], d1[u]);
  //   }
  //   ++d1[v];
  //   l1[v] = col;
  //   if (d1[v] >= 42) ++col;
  // }
  // for (int i = 1; i <= n; ++i) { // layer 2
  //   int v = a[i];
  //   for (auto u : g[v]) {
  //     if (l1[u] != l1[v] && l2[u] == col) chkmax(d2[v], d2[u]);
  //   }
  //   ++d2[v];
  //   l2[v] = col;
  //   if (d2[v] >= 42) ++col;
  // }
  const int B = 40;
  for (int i = 1; i <= n; ++i) {
    l1[a[i]] = (i-1) / B + 1;
  }
  const int T = B * B;
  for (int i = 1; i <= n; ++i) {
    l2[a[i]] = (i-1) / T + 1;
  }
  // cout << n << ' ' << m << '\n';
  for (int i = 0; i < m; ++i) {
    int u = e[i].fi, v = e[i].se;
    // cout << u << ' ' << v << ' ';
    if (l1[u] == l1[v]) {
      cout << "R\n";
    } else if (l2[u] == l2[v]) {
      cout << "G\n";
    } else cout << "B\n";
  }
}

int main() {
  freopen("ex.in", "r", stdin);
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
