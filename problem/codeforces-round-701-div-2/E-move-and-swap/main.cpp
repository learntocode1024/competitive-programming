// Original Author: misaka18931
// Date: 02-12-21
// tag: dp, tree, optimization, step-by-step, sort
// AC

#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 200005
#define add_edge(X, Y) { \
  to[++tot] = Y; \
  nxt[tot]  = head[X]; \
  head[X]   = tot; \
}
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

vector<vector<int> > node;
int head[MX], nxt[2 * MX], to[2 * MX], tot;
int fa[MX];
LL minv[MX], maxv[MX];
LL val[MX];
LL dp[MX], tmp[MX];

void dfs(int u, int dep, int fa) {
  ::fa[u] = fa;
  if (node.size() == dep) {
    node.push_back(vector<int>());
    minv[dep] = maxv[dep] = val[u];
  } else {
    minv[dep] = min(minv[dep], val[u]);
    maxv[dep] = max(maxv[dep], val[u]);
  }
  node[dep].push_back(u);
  for (int i = head[u]; i; i = nxt[i]) {
    if (to[i] != fa) dfs(to[i], dep + 1, u);
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 2, x; i <= n; ++i) {
    cin >> x;
    add_edge(x, i)
    add_edge(i, x)
  }
  for (int i = 2; i <= n; ++i) {
    cin >> val[i];
  }
  dfs(1, 0, 0);
  int t = node.size();
  for (int i = 0; i < node[t - 1].size(); ++i){
    dp[node[t - 1][i]] =
      max(maxv[t - 1] - val[node[t - 1][i]], val[node[t - 1][i]] - minv[t - 1]);
    tmp[fa[node[t - 1][i]]] = max(tmp[fa[node[t - 1][i]]], dp[node[t - 1][i]]);
    }
  for (int i = t - 2; i >= 0; --i) {
    sort(node[i].begin(), node[i].end(), [](int a, int b) { return val[a] < val[b]; });
    // # optimized: O(n^2) -> O(n)
    // for (int j = 0; j < node[i].size(); ++j) {
    //   int &u = node[i][j];
    //   dp[u] = max(val[u] - minv[i], maxv[i] - val[u]) + tmp[u];
    //   for (int k = 0; k < node[i].size(); ++k) {
    //     int &v = node[i][k];
    //     dp[u] = max(dp[u], abs(val[u] - val[v]) + tmp[v]);
    //   }
    //   tmp[fa[u]] = max(tmp[fa[u]], dp[u]);
    // }
    for (int j = 0; j < node[i].size(); ++j) {
      int &u = node[i][j];
      dp[u] = max(val[u] - minv[i], maxv[i] - val[u]) + tmp[u];
      tmp[fa[u]] = max(tmp[fa[u]], dp[u]);
    }
    LL mval = tmp[node[i][0]];
    for (int j = 1; j < node[i].size(); ++j) {
      int &u = node[i][j];
      dp[u] = max(dp[u], mval + val[node[i][j]] - val[node[i][j - 1]]);
      tmp[fa[u]] = max(tmp[fa[u]], dp[u]);
      mval = max(mval + val[node[i][j]] - val[node[i][j - 1]], tmp[node[i][j]]);
    }
    mval = tmp[*node[i].rbegin()];
    for (int j = node[i].size() - 2; j >= 0; --j) {
      int &u = node[i][j];
      dp[u] = max(dp[u], mval + val[node[i][j + 1]] - val[node[i][j]]);
      tmp[fa[u]] = max(tmp[fa[u]], dp[u]);
      mval = max(mval + val[node[i][j + 1]] - val[node[i][j]], tmp[node[i][j]]);
    }
  }
  cout << tmp[1] << endl;
  tot = 0;
  for (int i = 1; i <= n; ++i) {
    head[i] = dp[i] = tmp[i] = 0;
  }
  node.clear();
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}