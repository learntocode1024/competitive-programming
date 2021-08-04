#include <algorithm>
#include <cstdio>
#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long i64;
typedef unsigned i32;
typedef unsigned long long u64;
#define FILEIO(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);
#define fi first
#define se second 
#define MX 100005
int n, m;
vector<int> G[MX];

namespace SEG {
struct node {
  int l, r, c, t;
} a[MX << 2];
#define cur a[p]
#define tag a[p].t
#define lc a[p << 1]
#define rc a[(p << 1) + 1]
void down(int p, int l, int r) {
  if (tag) {
    int mid = l + (r - l) / 2;
    lc.t = lc.r = lc.l = tag;
    lc.c = mid - l - 1;
    rc.t = rc.r = rc.l = tag;
    rc.c = r - mid - 1;
    tag = 0;
  }
}
void build(int p = 1, int l = 0, int r = n) {
  cur.l = cur.r = cur.c = cur.t = 0;
  if (r - l == 1) return;
  int mid = l + (r - l) / 2;
  build(p << 1, l, mid);
  build((p << 1) + 1, mid, r);
}
void up(int p) {
  cur.l = lc.l;
  cur.r = rc.r;
  cur.c = lc.c + rc.c + ((lc.r == rc.l) && (lc.r));
}
int get_t(int pos, int p = 1, int l = 0, int r = n) {
  if (l == pos) return cur.l;
  down(p, l, r);
  int mid = l + (r - l) / 2;
  if (pos < mid) return get_t(pos, p << 1, l, mid);
  return get_t(pos, (p << 1) + 1, mid, r);
}
int get_c(int s, int t, int p = 1, int l = 0, int r = n) {
  if (s == l && t == r) {
    return cur.c;
  }
  down(p, l, r);
  int mid = l + (r - l) / 2;
  int ret = 0;
  if (s < mid) ret += get_c(s, min(mid, t), p << 1, l, mid);
  if (t > mid) ret += get_c(max(s, mid), t, (p << 1) + 1, mid, r);
  return ret + ((s < mid) && (t > mid) && lc.r == rc.l && lc.r); 
}
void renew(int s, int t, int v, int p = 1, int l = 0, int r = n) {
  if (s == l && t == r) {
    cur.c = r - l - 1;
    cur.l = cur.r = cur.t = v;
    return;
  }
  down(p, l, r);
  int mid = l + (r - l) / 2;
  if (s < mid) renew(s, min(mid, t), v, p << 1, l, mid);
  if (t > mid) renew(max(s, mid), t, v, (p << 1) + 1, mid, r);
  up(p);
}
}

namespace sol {
int sz[MX], son[MX], dep[MX], fa[MX], rnk[MX], dfn[MX], top[MX], tot;
void dfs1(int u, int fa) {
  sz[u] = 1;
  sol::fa[u] = fa;
  dep[u] = dep[fa] + 1;
  son[u] = 0;
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    sz[u] += sz[v];
    if (sz[v] > sz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int top) {
  sol::top[u] = top;
  dfn[u] = ++tot;
  rnk[tot] = u;
  if (son[u]) dfs2(son[u], top);
  for (auto v : G[u]) {
    if (dfn[v]) continue;
    dfs2(v, v);
  }
}

void set(int a, int b, int col) {
  while (top[a] != top[b]) {
    if (dep[top[a]] < dep[top[b]]) swap(a, b);
    SEG::renew(dfn[top[a]] - 1, dfn[a], col);
    a = fa[top[a]];
  }
  if (dep[a] < dep[b]) swap(a, b);
  SEG::renew(dfn[b] - 1, dfn[a], col);
}

int sum(int a, int b) {
  int ret = 0;
  while (top[a] != top[b]) {
    if (dep[top[a]] < dep[top[b]]) swap(a, b);
    ret += SEG::get_c(dfn[top[a]] - 1, dfn[a]);
    int c1 = SEG::get_t(dfn[top[a]] - 1), c2 = SEG::get_t(dfn[fa[top[a]]] - 1);
    ret += (c1 == c2 && c1);
    a = fa[top[a]];
  }
  if (dep[a] < dep[b]) swap(a, b);
  ret += SEG::get_c(dfn[b] - 1, dfn[a]);
  return ret;
}

inline void solve() {
  dfs1(1, 0);
  dfs2(1, 1);
  // hld
  SEG::build();
  int op, a, b;
  for (int i = 1; i <= m; ++i) {
    cin >> op >> a >> b;
    if (op == 1) {
      set(a, b, i);
    } else {
      cout << sum(a, b) << '\n';
    }
  }
  for (int i = 0; i <= n; ++i) {
    sz[i] = son[i] = dep[i] = fa[i] = rnk[i] = dfn[i] = top[i] = 0;
  }
  tot = 0;
  for (int i = 0; i <= n; ++i) {
    G[i].clear();
  }
}
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 1, u, v; i < n; ++i) {
      cin >> u >> v;
      G[u].emplace_back(v);
      G[v].emplace_back(u);
    }
      sol::solve();
  }
  return 0;
}
