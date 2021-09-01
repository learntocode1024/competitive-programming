#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 100005;
int n, m;
int a[N];
int rts[N], rtsf[N];
int sz[N], mson[N], fa[N], dep[N], sub[N], subf[N];
bool vis[N];
int rt, all;
vector<int> G[N];

namespace seg {
int s[N << 5], lc[N << 5], rc[N << 5], tot;
void add(int &p, int l, int r, int t, int v) {
  if (!p) p = ++tot;
  if (r - l == 1) {
    s[p] += v;
    return;
  }
  int mid = (l + r) >> 1;
  if (t < mid) add(lc[p], l, mid, t, v);
  else add(rc[p], mid, r, t, v);
  s[p] = s[lc[p]] + s[rc[p]];
}
int get(int p, int l, int r, int a, int b) {
  if (!p) return 0;
  if (a == l && b == r) {
    return s[p];
  }
  int ret = 0;
  int mid = (l + r) >> 1;
  if (a < mid) ret += get(lc[p], l, mid, a, min(mid, b));
  if (b > mid) ret += get(rc[p], mid, r, max(a, mid), b);
  return ret;
}
} // namespace seg

namespace LCA {
int st[21][N << 1];
int dep[N], dfn[N], tot;
void dfs0(int u, int fa) {
  st[0][++tot] = u;
  dep[u] = dep[fa] + 1;
  dfn[u] = tot;
  for (auto v : G[u]) {
    if (v != fa) dfs0(v, u), st[0][++tot] = u;
  }
}
void init() {
  dfs0(1, 0);
  dep[0] = 1e9;
  for (int i = 1; (1 << i) <= tot; ++i) {
    for (int j = 1; j + (1 << i) <= tot; ++j) {
      st[i][j] = dep[st[i - 1][j]] < dep[st[i - 1][j + (1 << (i - 1))]]
                     ? st[i - 1][j]
                     : st[i - 1][j + (1 << (i - 1))];
    }
  }
}
inline int lca(int x, int y) {
  if (dfn[y] > dfn[x]) swap(x, y);
  int t = 31 - __builtin_clz(dfn[x] - dfn[y] + 1);
  return dep[st[t][dfn[y]]] < dep[st[t][dfn[x] - (1 << t) + 1]]
             ? st[t][dfn[y]]
             : st[t][dfn[x] - (1 << t) + 1];
}
inline int dis(int x, int y) {
  return dep[x] + dep[y] - (dep[lca(x, y)] << 1);
}
}  // namespace LCA
using LCA::dis;

void centroid(int u, int fa) {
  sz[u] = 1;
  mson[u] = 0;
  for (auto v : G[u]) {
    if (vis[v] || v == fa) continue;
    centroid(v, u);
    sz[u] += sz[v];
    chkmax(mson[u], sz[v]);
  }
  chkmax(mson[u], all - sz[u]);
  if (mson[u] < mson[rt]) rt = u;
}

void work(int u, int fa) {
  dep[u] = dep[fa] + 1;
  sz[u] = 1;
  seg::add(rts[rt], 0, sub[rt], dep[u], a[u]);
  if (::fa[rt]) seg::add(rtsf[rt], 0, subf[rt], dis(::fa[rt], u), a[u]);
  for (auto v : G[u]) {
    if (v == fa || vis[v]) continue;
    work(v, u);
    sz[u] += sz[v];
  }
}

void build(int u) {
  work(u, 0);
  vis[u] = 1;
  for (auto v : G[u]) {
    if (vis[v]) continue;
    rt = 0;
    all = sz[v];
    centroid(v, u);
    fa[rt] = u;
    sub[rt] = sz[v];
    subf[rt] = sz[v] + dis(u, rt);
    build(rt);
  }
}

void modify(int u, int x) {
  int c = u;
  int t = x - a[u];
  a[u] = x;
  while (u) {
    seg::add(rts[u], 0, sub[u], dis(u, c), t);
    if (fa[u]) seg::add(rtsf[u], 0, subf[u], dis(fa[u], c), t);
    u = fa[u];
  }
}
int getans(int u, int k) {
  int ret = 0;
  int c = u;
  while (u) {
    ret += seg::get(rts[u], 0, sub[u], 0, min(k - dis(u, c) + 1, sub[u]));
    if (fa[u]) ret -= seg::get(rtsf[u], 0, subf[u], 0, min(k - dis(fa[u], c) + 1, subf[u]));
    u = fa[u]; 
  }
  return ret;
}

void solve() {
  n = rd();
  m = rd();
  FOR(i, 1, n + 1) a[i] = rd();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  LCA::init();
  rt = 0;
  all = n;
  centroid(1, 0);
  sub[rt] = sz[1];
  build(rt);
  int lastans = 0;
  for (int i = 0; i < m; ++i) {
    int op = rd();
    int x = rd() ^ lastans, y = rd() ^ lastans;
    if (op) modify(x, y);
    else cout << (lastans = getans(x, y)) << '\n';
  }
}

int main() {
  dep[0] = -1;
  mson[0] = 1e9;
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