// Original Author: misaka18931
// Date: $DATE
// tag:
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 100005
int n, q, dfn[MX], f[MX][32], dep[MX], tot;
vector<int> G[MX];

void dfs(int u, int fa) {
  dfn[u] = ++tot;
  f[u][0] = fa;
  dep[u] = dep[fa] + 1;
  for (auto v : G[u]) {
    if (dfn[v]) continue;
    else dfs(v, u);
  }
}

int s[MX], tt;

int lca(int a, int b) {
  if (dep[a] < dep[b]) swap(a, b);
  int x = dep[a] - dep[b];
  for (int i = 31; i >= 0; --i) {
    if (x & (1 << i)) a = f[a][i];
  }
  if (a == b) return a;
  for (int i = 31; i >= 0; --i) {
    if (f[a][i] != f[b][i]) a = f[a][i], b = f[b][i];
  }
  return f[a][0];
}
int qry[MX];
int virt() {
  int k;
  cin >> k;
  int ret = 0;
  for (int i = 0; i < k; ++i) cin >> qry[i];
  sort(qry, qry + k, [] (auto a, auto b) { return dfn[a] < dfn[b]; });
  for (int i = 0; i < k; ++i) {
    int cur = qry[i];
    if (!tt) {
      s[++tt] = cur;
      continue;
    }
    int z = lca(s[tt], cur);
    while (tt && dep[s[tt]] > dep[z]) --tt;
    if (!tt) ret += dep[s[1]] - dep[z];
    if (!tt || s[tt] != z) s[++tt] = z;
    ret += dep[cur] - dep[s[tt]];
    s[++tt] = cur;
  }
  tt = 0;
  return ret;
}

void solve() {
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].pb(v);
    G[v].pb(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= 20; ++i) {
    for (int j = 1; j <= n; ++j) {
      f[j][i] = f[f[j][i - 1]][i - 1];
    }
  }
  cin >> q;
  while (q--) {
    cout << n - virt() - 1 << endl;
  }
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}
