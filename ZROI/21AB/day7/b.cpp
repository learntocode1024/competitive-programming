/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug 10, 2021
 * Algorithm: hld, BST
 * Difficulty: mid
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
char in[1 << 23]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int rd() {
  unsigned u = 0, s = 0;

  while (*o && *o <= 32)
    ++o; // skip whitespaces...

  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign

  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)

  return static_cast<int>((u ^ s) + !!s);
}

char *rdstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
  return s;
}
} // namespace IO

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX 200005

int ch[2][MX];
int n, q;
int c[MX], C[MX];
int dfn[MX], rnk[MX], tot;

#define lc ch[0][u]
#define rc ch[1][u]

void dfs(int u) {
  if (lc) {
    dfs(lc);
  }
  dfn[u] = ++tot;
  rnk[tot] = u;
  if (rc) {
    dfs(rc);
  }
}

namespace hld {
int fa[MX], sz[MX], dfn[MX], rnk[MX], dep[MX], top[MX], tot;
void dfs1(int u) {
  sz[u] = 1;
  if (lc) {
    dep[lc] = dep[u] + 1;
    fa[lc] = u;
    dfs1(lc);
  }
  if (rc) {
    fa[rc] = u;
    dep[rc] = dep[u] + 1;
    dfs1(rc);
  }
  sz[u] += sz[lc] + sz[rc];
}
void dfs2(int u, int t) {
  dfn[u] = ++tot;
  rnk[tot] = u;
  top[u] = t;
  if (sz[u] == 1) return;
  if (lc && sz[lc] >= sz[rc]) {
    dfs2(lc, t);
    if (rc) dfs2(rc, rc);
  } else {
    dfs2(rc, t);
    if (lc) dfs2(lc, lc);
  }
}
#undef lc
#undef rc

struct seg {
  struct node {
    int v, cnt, t;
  } a[MX << 2];
  #define lc (p << 1)
  #define rc ((p << 1) | 1)
  inline void up(int p) {
    if (a[lc].v == a[rc].v) a[p].cnt = a[lc].cnt + a[rc].cnt;
    else {
      a[p].cnt = a[lc].v < a[rc].v ? a[lc].cnt : a[rc].cnt;
      a[p].v = min(a[lc].v, a[rc].v);
    }
  }
  inline void down(int p) {
    if (a[p].t) {
      a[lc].v += a[p].t;
      a[rc].v += a[p].t;
      a[lc].t += a[p].t;
      a[rc].t += a[p].t;
      a[p].t = 0;
    }
  }
  void build(int p = 1, int l = 1, int r = n + 1) {
    if (r - l == 1) {
      a[p].cnt = 1;
      return;
    }
    int mid = l + (r - l) / 2;
    build(lc, l, mid);
    build(rc, mid, r);
    up(p);
  }
  void inc(int p, int l, int r, int s, int t, int v) {
    if (s == l && t == r) {
      a[p].v += v;
      a[p].t += v;
      return;
    }
    down(p);
    int mid = l + (r - l) / 2;
    if (s < mid) inc(lc, l, mid, s, min(t, mid), v);
    if (t > mid) inc(rc, mid, r, max(s, mid), t, v);
    up(p);
  }
} T;
void init() {
  dfs1(1);
  dfs2(1, 1);
  T.build();
}
int lca(int a, int b) {
  while (top[a] != top[b]) {
    if (dep[top[a]] > dep[top[b]]) swap(a, b);
    b = fa[top[b]];
  }
  if (dep[a] > dep[b]) swap(a, b);
  return a;
}
inline int getans() {
  if (T.a[1].v > 0) return 0;
  return T.a[1].cnt;
}
void apply(int a, int b, int t) {
  int x = lca(a, b);
  while (top[x] != 1) {
    T.inc(1, 1, n + 1, dfn[top[x]], dfn[x] + 1, t);
    x = fa[top[x]];
  }
  T.inc(1, 1, n + 1, 1, dfn[x] + 1, t);
}
}
void solve() {
  n = rd(), q = rd();
  for (int i = 1; i <= n; ++i) {
    ch[0][i] = rd(), ch[1][i] = rd();
  }
  for (int i = 1; i <= n; ++i) c[i] = rd();
  hld::init();
  dfs(1);
  for (int i = 1; i <= n; ++i) {
    C[dfn[i]] = c[i];
  }
  for (int i = 1; i < n; ++i) {
    if (C[i] > C[i + 1]) {
      hld::apply(rnk[i], rnk[i + 1], 1);
    }
  }
  while (q--) {
    int k = rd(), x = rd();
    k = dfn[k];
    if (k < n && C[k] <= C[k + 1] && x > C[k + 1]) hld::apply(rnk[k], rnk[k + 1], 1);
    if (k < n && C[k] > C[k + 1] && x <= C[k + 1]) hld::apply(rnk[k], rnk[k + 1], -1);
    if (k > 1 && C[k - 1] <= C[k] && C[k - 1] > x) hld::apply(rnk[k - 1], rnk[k], 1);
    if (k > 1 && C[k - 1] > C[k] && C[k - 1] <= x) hld::apply(rnk[k - 1], rnk[k], -1);
    C[k] = x;
    cout << hld::getans() << '\n';
  }
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}
