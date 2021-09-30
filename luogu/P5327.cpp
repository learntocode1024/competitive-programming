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
#include <cassert>
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
const int N = 1e5+5;
int n, m;
vector<int> G[N];
vector<int> f[N];
int dep[N], dfn[N], rnk[N], rmq[21][N << 1], tot, _fa[N], tot2, dsn[N];
void dfs(int u, int fa) {
  dfn[u] = ++tot;
  dsn[u] = ++tot2;
  rnk[tot2] = u;
  _fa[u] = fa;
  dep[u] = dep[fa] + 1;
  rmq[0][tot] = u;
  for (auto v : G[u]) {
    if (v != fa) dfs(v, u), rmq[0][++tot] = u;
  }
}
inline int gmin(int a, int b) {
  return dep[a] < dep[b] ? a : b;
}
inline void init() {
  // dep[0] = -1;
  dfs(1, 0);
  dep[0] = 0;
  FOR(i, 1, 21) {
    for (int j = 1; j + (1 << i) - 1 <= tot; ++j) {
      rmq[i][j] = gmin(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
    }
  }
}
int lca(int a, int b) {
  int x = dfn[a], y = dfn[b];
  if (x > y) swap(x, y);
  int t = 31 - __builtin_clz(y - x + 1);
  return gmin(rmq[t][x], rmq[t][y + 1 - (1 << t)]);
}

struct DS {
  struct node {
    int _lc, _rc;
    int l, r, s, u;
    int cnt;
  } a[N << 5];
  int all;
  #define lc a[a[p]._lc]
  #define rc a[a[p]._rc]
  #define P a[p]
  inline void up(int p) {
    if (lc.l && rc.l) {
      P.l = lc.l;
      P.r = rc.r;
      P.s = lc.s + rc.s - dep[lca(rnk[lc.r], rnk[rc.l])];
      P.u = lca(lc.u, rc.u);
    } else {
      P.l = lc.l | rc.l;
      P.r = lc.r | rc.r;
      P.s = lc.s | rc.s;
      P.u = lc.u | rc.u;
    }
  }
  void merge(int &p, int q, int l, int r) { // Even segtree merge operation needs l, r arguments (to avoid leaves being overwrited)
    if (!p || !q) {
      p |= q;
      return;
    }
    if (r - l == 1) {
      a[p].cnt += a[q].cnt;
      a[p].l |= a[q].l;
      a[p].r |= a[q].r;
      a[p].u |= a[q].u;
      a[p].s |= a[q].s;
      return;
    }
    int mid = (l + r) >> 1;
    merge(a[p]._lc, a[q]._lc, l, mid);
    merge(a[p]._rc, a[q]._rc, mid, r);
    up(p);
  }
  void ins(int &p, int l, int r, int pos, int v) {
    if (!p) p = ++all;
    if (r - l == 1) {
      P.cnt += v;
      if (P.cnt > 0) {
        P.l = P.r = l;
        P.u = rnk[l];
        P.s = dep[rnk[l]];
      } else {
        P.l = P.r = P.s = P.u = 0;
      }
      return;
    }
    int mid = (l + r) >> 1;
    if (pos < mid) ins(a[p]._lc, l, mid, pos, v);
    else ins(a[p]._rc, mid, r, pos, v);
    up(p);
  }
  int get(int rt) {
    return a[rt].s - dep[a[rt].u];
  }
  #undef lc
  #undef rc
  #undef P
} T;

int rts[N];
i64 ans;

void calc(int u, int fa) {
  for (auto v : G[u]) {
    if (v != fa) {
      calc(v, u);
      T.merge(rts[u], rts[v], 1, n + 1);
    }
  }
  for (auto v : f[u]) {
    if (v > 0) {
      T.ins(rts[u], 1, n + 1, v, 1);
    } else {
      T.ins(rts[u], 1, n + 1, -v, -1);
    }
  }
  ans += T.get(rts[u]);
  // cerr << "clac(" << u << ") = " << T.get(rts[u]) << '\n';
}

void solve() {
  n = rd(), m = rd();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  init();
  FOR(i, 0, m) {
    int s = rd(), t = rd();
    if (s == t) continue;
    int x = dsn[s], y = dsn[t], z = lca(s, t);
    f[s].push_back(x);
    f[s].push_back(y);
    f[t].push_back(x);
    f[t].push_back(y);
    f[z].push_back(-x);
    f[z].push_back(-y);
    f[_fa[z]].push_back(-x);
    f[_fa[z]].push_back(-y);
  }
  calc(1, 0);
  cout << ans / 2 << '\n';
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
