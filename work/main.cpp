#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

const int N = 200005;

vector<int> G[N];
int a[N];
int n, m;

namespace LCA {
int st[17][N];
int dep[N], dfn[N], tot;
void dfs0(int u, int fa) {
  st[0][++tot] = u;
  dep[u] = dep[fa] + 1;
  dfn[u] = tot;
  for (auto v : G[u]) {
    if (v != fa) dfs0(v, u);
  }
}
void init() {
  dfs0(1, 0);
  dep[0] = 1e9;
  FOR(i, 1, 17) {
    FOR(j, 1, n + 1) {
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
