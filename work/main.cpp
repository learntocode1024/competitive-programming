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
int sz[N], mson[N], fa[N];
bool vis[N];
int rt, all;
vector<int> G[N];
void centroid(int u, int fa) {
  sz[u] = 1;
  mson[u] = 0;
  for (auto v : G[u]) {
    if (vis[v] || v == fa) continue;
    centroid(v, u);
    sz[u] += sz[v];
    chkmax(mson[u], mson[v]);
  }
  chkmax(mson[u], all - sz[u]);
  if (mson[u] < mson[rt]) rt = u;
}

void build(int u) {
  vis[u] = 1;
  for (auto v : G[u]) {
    if (vis[v]) continue;
    rt = 0;
    centroid(v, u);
    build(rt);
  }
}

void modify(int u, int x);
int getans(int u, int k) {

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
  for (int i = 0; i < m; ++i) {
    int op = rd();
    int x = rd(), y = rd();
    if (op) modify(x, y);
    else cout << getans(x, y) << '\n';
  }
}

int main() {
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
