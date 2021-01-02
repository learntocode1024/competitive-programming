// Original Author: misaka18931
// Date: 01-02-21
// tag: dfs, prefix-sum(on-tree)
// AC

#include <cstdio>
#include <cstring>
#include <iostream>
#define MX 200005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;

std::pair<int, int> edge[MX];
int depth[MX];
int head[MX], to[MX * 2], nxt[MX * 2], tot = 0;
LL x[MX], ans[MX];
bool vis[MX];

inline void add_edge(int a, int b) {
  to[++tot] = b;
  nxt[tot] = head[a];
  head[a] = tot;
}

void get_dep(int u, int dep) {
  depth[u] = dep;
  for (int i = head[u]; i != 0; i = nxt[i]) {
    if (!depth[to[i]]) get_dep(to[i], dep + 1);
  }
}

void dfs(int u) {
  ans[u] += x[u];
  vis[u] = true;
  for (int i = head[u]; i != 0; i = nxt[i]) {
    if (!vis[to[i]]) {
      ans[to[i]] = ans[u];
      dfs(to[i]);
    }
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1, a, b; i < n; ++i) {
    cin >> a >> b;
    add_edge(a, b);
    add_edge(b, a);
    edge[i] = std::make_pair(a, b);
  }
  get_dep(1, 1);
  int q;
  cin >> q;
  int t, e;
  LL val;
  while (q--) {
    cin >> t >> e >> val;
    int a, b;
    if (t == 1) {
      a = edge[e].first, b = edge[e].second;
    } else {
      b = edge[e].first, a = edge[e].second;
    }
    if (depth[a] > depth[b]) {
      x[a] += val;
    } else {
      x[1] += val, x[b] -= val;
    }
  }
  dfs(1);
  for (int i = 1; i <= n; ++i) {
    cout << ans[i] << endl;
  }
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
