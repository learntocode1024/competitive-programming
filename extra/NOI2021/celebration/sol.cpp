#include <algorithm>
#include <bitset>
#include <cstdio>
#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef long long i64;
typedef unsigned i32;
typedef unsigned long long u64;
template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template<typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
#define FILEIO(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);
#define MX 300005
int n, m, q, k;
vector<int> G[MX];
int a[MX * 2], b[MX * 2];

namespace sol {
int dfn[MX], low[MX], tot;
int s[MX], tt;
bool ins[MX];
int scc[MX], cnt;
int sz[MX];
vector<int> G1[MX];
void tarjan(int u) {
  low[u] = dfn[u] = ++tot;
  ins[u] = 1;
  s[++tt] = u;
  for (auto v : G[u]) {
    if (!dfn[v]) {
      tarjan(v);
      chkmin(low[u], low[v]);
    } else if (ins[v]) chkmin(low[u], low[v]);
  }
  if (low[u] == dfn[u]) {
    ++cnt;
    while (s[tt] != u) {
      ++sz[cnt];
      scc[s[tt]] = cnt;
      ins[s[tt]] = 0;
      --tt;
    }
    ++sz[cnt];
    scc[u] = cnt;
    ins[u] = 0;
    --tt;
  }
}
int in[MX];
int top[MX], rnk[MX], ttt;
queue<int> Q;
void topo() {
  for (int i = 1; i <= cnt; ++i) {
    for (auto v : G1[i]) {
      ++in[v];
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    if (in[i] == 0) Q.push(i);
  }
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    top[ttt++] = u;
    for (auto v : G1[u]) {
      --in[v];
      if (in[v] == 0) Q.push(v);
    }
  }
  for (int i = 0; i < cnt; ++i) {
    rnk[top[i]] = i + 1;
  }
}
void f[MX][25], v[MX][25];
int ga[MX], gb[MX], totg;
vector<int> GT[MX];
int v_dfn[MX], v_tot;

void v_dfs(int u) {
  v_dfn[u] = ++v_tot;
  for (auto v : TG[u]) {
    v_dfs(v);
  }
}

void work() {
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) tarjan(i);
  }
  for (int i = 0; i < m; ++i) {
    if (scc[a[i]] != scc[b[i]]) {
      gb[totg] = scc[b[i]];
      ga[totg++] = scc[a[i]];
      G1[scc[a[i]]].push_back(scc[b[i]]);
    }
  } // tarjan-scc G->G1
  topo();
  for (int i = 0; i < totg; ++i) {
    if (rnk[ga[i]] > rnk[f[gb[i]][0]]) {
      f[gb[i]][0] = ga[i];
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    v[i][0] = sz[i];
  }
  for (int i = 1; i <= 24; ++i) {
    for (int j = 1; j <= cnt; ++j) {
      f[j][i] = f[f[j][i - 1]][i - 1];
      v[j][i] = v[j][i - 1] + v[f[j][i - 1]][i - 1];
    }
  } // lca-prework
  for (int i = 1; i <= cnt; ++i) {
    TG[f[i][0]].push_back(i);
  }
  v_dfs(top[0]);
  // virtual-tree-prework
}
int vc[7];
int u1, v1, u2, v2;
void solve() {
  work();
  while (q--) {
    int s, t;
    cin >> s >> t;
    vc[0] = scc[s], vc[1] = scc[t];
    if (k) {
      
    }
  }
}
}

int main() {
  // FILEIO("celebration")
  cin.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q >> k;
  for (int i = 0; i < m; ++i) {
    cin >> a[i] >> b[i];
    G[a[i]].push_back(b[i]);
  }
  sol::solve();
  return 0;
}
