/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  7, 2021
 * Algorithm: segtree
 * Difficulty: easy
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
char in[1 << 26];  // sizeof in varied in problem
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
  return s;
} 
}  // namespace IO

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}

/*********************************** solution *********************************/
using IO::rd;
#define MX 1000005
vector<int> G[MX];
int p[3];
int n;
int lt[MX], sz[MX];
i64 ans = 0;

namespace seg {
struct node {
  int lc, rc, c;
} a[MX << 4];
int tot;
int rts[MX];
bool vis[MX];
inline void up(int u) { a[u].c = a[a[u].lc].c + a[a[u].rc].c; }
void ins(int &p, int l, int r, int v) {
  if (!p) p = ++tot;
  if (r - l == 1) {
    a[p].c = 1;
    return;
  }
  int mid = l + (r - l) / 2;
  if (v < mid)
    ins(a[p].lc, l, mid, v);
  else
    ins(a[p].rc, mid, r, v);
  up(p);
}

int merge(int p, int q) {
  if (!p || !q) return p | q;
  a[p].lc = merge(a[p].lc, a[q].lc);
  a[p].rc = merge(a[p].rc, a[q].rc);
  up(p);
  return p;
}

int qry(int p, int l, int r, int v) {
  if (!p) return 0;
  if (r == v) return a[p].c;
  int mid = l + (r - l) / 2;
  if (v <= mid)
    return qry(a[p].lc, l, mid, v);
  else
    return a[a[p].lc].c + qry(a[p].rc, mid, r, v);
}

void dfs1(int u) {
  vis[u] = 1;
  i64 dif = 0;
  for (auto v : G[u]) {
    if (vis[v]) continue;
    dfs1(v);
    i64 ig = sz[v] - qry(rts[v], 1, n + 1, u);
    dif += ig * (ig - 1) / 2;
    rts[u] = merge(rts[u], rts[v]);
    sz[u] += sz[v];
  }
  lt[u] = qry(rts[u], 1, n + 1, u);
  ins(rts[u], 1, n + 1, u);
  sz[u] += 1;
  i64 il = lt[u], ig = sz[u] - lt[u] - 1, ol = u - il - 1, og = n - u - ig;
  ans += ig * (ig - 1) / 2 + ig * og - dif;
}
void dfs2(int u) {
  vis[u] = 1;
  i64 dif = 0;
  for (auto v : G[u]) {
    if (vis[v]) continue;
    dfs2(v);
    i64 il = qry(rts[v], 1, n + 1, u), ig = sz[v] - il;
    dif += il * ig;
    rts[u] = merge(rts[u], rts[v]);
    sz[u] += sz[v];
  }
  lt[u] = qry(rts[u], 1, n + 1, u);
  ins(rts[u], 1, n + 1, u);
  sz[u] += 1;
  i64 il = lt[u], ig = sz[u] - lt[u] - 1, ol = u - il - 1, og = n - u - ig;
  ans += il * ig + og * il + ol * ig - dif;
}
void dfs3(int u) {
  vis[u] = 1;
  i64 dif = 0;
  for (auto v : G[u]) {
    if (vis[v]) continue;
    dfs3(v);
    i64 il = qry(rts[v], 1, n + 1, u);
    dif += il * (il - 1) / 2;
    rts[u] = merge(rts[u], rts[v]);
    sz[u] += sz[v];
  }
  lt[u] = qry(rts[u], 1, n + 1, u);
  ins(rts[u], 1, n + 1, u);
  sz[u] += 1;
  i64 il = lt[u], ig = sz[u] - lt[u] - 1, ol = u - il - 1, og = n - u - ig;
  ans += il * (il - 1) / 2 + il * ol - dif;
}
}  // namespace seg
// void s1() {
//   for (int i = 1; i <= n; ++i) {
// i64 il = lt[i], ig = sz[i] - lt[i] - 1, ol = i - il - 1, og = n - i - ig;
// ans += ig * (ig - 1) / 2 + ig * og;
//   }
// }

// void s2() {
//   for (int i = 1; i <= n; ++i) {
//     i64 il = lt[i], ig = sz[i] - lt[i] - 1, ol = i - il - 1, og = n - i - ig;
//     ans += og * il + ol * ig;
//   }
// }

// void s3() {
//   for (int i = 1; i <= n; ++i) {
//     i64 il = lt[i], ig = sz[i] - lt[i] - 1, ol = i - il - 1, og = n - i - ig;
//     ans += il * (il - 1) /2 + il * ol;
//   }
// }

void solve() {
  n = rd();
  REP(i, 0, 3) p[i] = rd();
  for (int i = 1, u, v; i < n; ++i) {
    u = rd(), v = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  if (p[1] == 1)
    seg::dfs1(1);
  else if (p[1] == 2)
    seg::dfs2(1);
  else
    seg::dfs3(1);
  cout << ans << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}
