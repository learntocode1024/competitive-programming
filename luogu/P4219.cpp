#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

const int N = 100005;
vector<int> G[N];
int n, m;

struct DS {
  int a[N << 2], b[N << 2];
#define down\
  a[p << 1] += (mid - l) * b[p], a[(p << 1) | 1] += (r - mid) * b[p];\
  b[p << 1] += b[p], b[(p << 1) | 1] += b[p];\
  b[p] = 0;
  int sum(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return a[p];
    int ret = 0;
    int mid = l + ((r - l) >> 1);
    down if (s < mid) ret += sum(p << 1, l, mid, s, min(mid, t));
    if (t > mid) ret += sum((p << 1) | 1, mid, r, max(mid, s), t);
    return ret;
  }
  void inc(int p, int l, int r, int s, int t, int v) {
    if (l == s && r == t) return a[p] += v * (r - l), b[p] += v, void();
    int mid = l + ((r - l) >> 1);
    down if (s < mid) inc(p << 1, l, mid, s, min(mid, t), v);
    if (t > mid) inc((p << 1) | 1, mid, r, max(mid, s), t, v);
    a[p] = a[p << 1] + a[(p << 1) | 1];
  }
} T;

struct dsu {
  int a[N], s[N];
  void init() {
    FOR(i, 1, n + 1) a[i] = i, s[i] = 1;
  }
  int get(int x) {
    if (a[x] == x) return x;
    a[x] = get(a[x]);
    return a[x];
  }
  int gets(int x) {
    return s[get(x)];
  }
  void uni(int fr, int to) {
    s[get(to)] += s[get(fr)];
    a[get(fr)] = get(to);
  }
} U;

int sz[N], son[N], dep[N], f[N], dfn[N], rnk[N], top[N], tot;
void dfs1(int u, int fa) {
  f[u] = fa;
  sz[u] = 1;
  dep[u] = dep[fa] + 1;
  for (auto v : G[u]) {
    if (v != fa) {
      dfs1(v, u);
      sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++tot;
  rnk[tot] = u;
  if (son[u]) dfs2(son[u], t);
  for (auto v : G[u]) {
    if (!dfn[v]) dfs2(v, v);
  }
}

char op[N];
int x[N], y[N];

int ans[N];
void solve() {
  n = rd(), m = rd();
  FOR(i, 0, m) op[i] = IO::rdch(), x[i] = rd(), y[i] = rd();
  FOR(i, 0, m) if (op[i] == 'A') G[x[i]].pb(y[i]), G[y[i]].pb(x[i]);
  for (int i = 1; i <= n; ++i) {
    if (!sz[i]) {
      dfs1(i, 0);
      dfs2(i, i);
    }
  }
  U.init();
  T.inc(1, 1, n + 1, 1, n + 1, 1);
  FOR(i, 0, m) {
    int u = x[i], v = y[i];
    if (dep[u] > dep[v]) swap(u, v);
    if (op[i] == 'A') {
      int siz = U.gets(v);
      int rt = U.get(u);
      int a = u;
      while (top[a] != top[rt]) {
        T.inc(1, 1, n + 1, dfn[top[a]], dfn[a] + 1, siz);
        a = f[top[a]];
      }
      T.inc(1, 1, n + 1, dfn[rt], dfn[a] + 1, siz);
      U.uni(v, u);
    } else {
      int siz = U.gets(u);
      int sub = T.sum(1, 1, n + 1, dfn[v], dfn[v] + 1);
      cout << (siz - sub) * sub << '\n';
    }
  }
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
