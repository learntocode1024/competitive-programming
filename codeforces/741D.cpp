#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

const int N = 500005;
int n;
vector<pii> G[N];
int ans[N];
int sz[N], son[N];
int l[N], r[N], dfn;
int dep[N], rnk[N], msk[N];
int dt[1 << 23];

void dfs(int u, int fa) {
  sz[u] = 1;
  dep[u] = dep[fa] + 1;
  rnk[++dfn] = u;
  l[u] = dfn;
  for (auto v : G[u]) {
    if (v.fi != fa) {
      msk[v.fi] = msk[u] ^ (1 << v.se);
      dfs(v.fi, u);
      sz[u] += sz[v.fi];
      if (sz[v.fi] > sz[son[u]]) son[u] = v.fi;
    }
  }
  r[u] = dfn + 1;
}

void dsu(int u, int fa, bool kpt) {
  for (auto v : G[u]) {
    if (v.fi != fa && v.fi != son[u])
      dsu(v.fi, u, 0), chkmax(ans[u], ans[v.fi]);
  }
  if (son[u]) dsu(son[u], u, 1), chkmax(ans[u], ans[son[u]]);
  if (dt[msk[u]]) chkmax(ans[u], dt[msk[u]] - dep[u]);
  for (int i = 0; i < 23; ++i) {
    if (dt[msk[u] ^ (1 << i)]) chkmax(ans[u], dt[msk[u] ^ (1 << i)] - dep[u]);
  }
  chkmax(dt[msk[u]], dep[u]);
  for (auto v : G[u]) {
    if (v.fi != fa && v.fi != son[u]) {
      for (int i = l[v.fi]; i < r[v.fi]; ++i) {
        if (dt[msk[rnk[i]]])
          chkmax(ans[u], dt[msk[rnk[i]]] + dep[rnk[i]] - 2 * dep[u]);
        for (int j = 0; j < 23; ++j) {
          if (dt[msk[rnk[i]] ^ (1 << j)])
            chkmax(ans[u], dt[msk[rnk[i]] ^ (1 << j)] + dep[rnk[i]] - 2 * dep[u]);
        }
      }
      for (int i = l[v.fi]; i < r[v.fi]; ++i) {
        chkmax(dt[msk[rnk[i]]], dep[rnk[i]]);
      }
    }
  }
  if (!kpt) {
    for (int i = l[u]; i < r[u]; ++i) {
      dt[msk[rnk[i]]] = 0;
    }
  }
}

void solve() {
  n = rd();
  FOR(i, 2, n + 1) {
    int v = rd(), w = IO::rdch() - 'a';
    G[i].eb(v, w);
    G[v].eb(i, w);
  }
  dfs(1, 0);
  dsu(1, 0, 1);
  FOR(i, 0, n) cout << ans[i + 1] << ' ';
  cout << '\n';
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
