#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 500005;
vector<int> G[N];
int n, q;

namespace LCA {
int dep[N], dfn[N], rmq[21][N << 1], tot;
void dfs(int u, int fa) {
  dfn[u] = ++tot;
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
  dfs(1, 0);
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
inline int dis(int a, int b) {
  return dep[a] + dep[b] - (dep[lca(a, b)] << 1);
}
}
using LCA::dis;



void solve() {
  n = rd(), q = rd();
  
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