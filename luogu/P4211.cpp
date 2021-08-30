#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

const int N = 50005;
vector<int> G[N];
vector<pii> q[N];

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
  void inc(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return a[p] += (r - l), ++b[p], void();
    int mid = l + ((r - l) >> 1);
    down if (s < mid) inc(p << 1, l, mid, s, min(mid, t));
    if (t > mid) inc((p << 1) | 1, mid, r, max(mid, s), t);
    a[p] += t - s;
  }
} T;

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

int ans[N];
void solve() {
  int n = rd(), m = rd();
  FOR(i, 2, n + 1) { G[rd() + 1].pb(i); }
  dfs1(1, 0);
  dfs2(1, 1);
  FOR(i, 0, m) {
    int l = rd(), r = rd() + 1, x = rd() + 1;
    q[l].eb(-x, i);
    q[r].eb(x, i);
  }
  FOR(i, 1, n + 1) {
    int u = i;
    while (u) {
      T.inc(1, 1, n + 1, dfn[top[u]], dfn[u] + 1);
      u = f[top[u]];
    }
    for (auto p : q[i]) {
      int u = abs(p.fi);
      while (u) {
        if (p.fi > 0)
          ans[p.se] += T.sum(1, 1, n + 1, dfn[top[u]], dfn[u] + 1);
        else
          ans[p.se] -= T.sum(1, 1, n + 1, dfn[top[u]], dfn[u] + 1);
        u = f[top[u]];
      }
    }
  }
  FOR(i, 0, m) cout << ans[i] % 201314 << '\n';
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
