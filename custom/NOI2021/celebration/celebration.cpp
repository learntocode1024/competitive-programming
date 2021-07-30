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

namespace T7 {
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
bitset<1005> dp[MX];
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
    rnk[top[i]] = i;
  }
}
void ssolve(int s, int t) {
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) tarjan(i);
  }
  for (int i = 0; i < m; ++i) {
    if (scc[a[i]] != scc[b[i]]) {
      G1[scc[a[i]]].push_back(scc[b[i]]);
    }
  }
  topo();
  s = scc[s];
  t = scc[t];
  dp[s].set(s);
  for (int i = rnk[s]; i < rnk[t]; ++i) {
    int u = top[i];
    if (dp[u] == 0) continue;
    dp[u].set(u);
    for (auto v : G1[u]) {
      dp[v] |= dp[u];
    }
  }
  if (dp[t] == 0) cout << "0\n";
  else {
  dp[t].set(t);
  int ans = 0;
  for (int i = 1; i <= cnt; ++i) if (dp[t][i]) ans += sz[i];
  cout << ans << '\n';
}
  for (int i = 0; i <= cnt; ++i) dp[i] = 0;
  for(int i = 0; i <= cnt; ++i) sz[i] = top[i] = 0, G1[i].clear();
  for (int i = 0; i <= n; ++i) low[i] = dfn[i] = 0;
  ttt = 0;
  cnt = 0;
}
void solve() {
  while (q--) {
    int s, t;
    cin >> s >> t;
    for (int i = 0; i < k; ++i) {
      cin >> a[m] >> b[m];
      G[a[m]].push_back(b[m]);
      ++m;
    }
    ssolve(s, t);
    for (int i = 0; i < k; ++i) {
      G[a[m - 1]].pop_back();
      a[m - 1] = b[m - 1] = 0;
      --m;
    }
  }
}
}

namespace T9 {
int in[MX];
int f[MX][30], dep[MX];
int rt = 0;
void dfs(int u, int fa) {
  f[u][0] = fa;
  dep[u] = dep[fa] + 1;
  for (auto v : G[u]) {
    dfs(v, u);
  }
}
bool lca(int s, int t) {
  if (dep[s] > dep[t]) return 0;
  int x = dep[t] - dep[s];
  for (int i = 25; i >= 0; --i) {
    if (x & (1 << i)) t = f[t][i];
  }
  return s == t;
}
void solve() {
  for (int i = 1; i <= n; ++i) {
    for (int v : G[i]) {
      ++in[v];
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!in[i]) {
      rt = i;
      break;
    }
  }
  dfs(rt, 0);
  for (int i = 1; i = 25; ++i) {
    for (int j = 1; j <= n; ++j) {
      f[j][i] = f[f[j][i - 1]][i - 1];
    }
  }
  for (int i = 0; i < q; ++i) {
    int s, t;
    cin >> s >> t;
    if (!lca(s, t)) cout << "0\n";
    else cout << dep[t] - dep[s] + 1 << '\n';
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
  if (n <= 1000 && q <= 1000) {
    T7::solve();
  } else if (m == n - 1 && k == 0) {
    T9::solve();
  }
  return 0;
}

