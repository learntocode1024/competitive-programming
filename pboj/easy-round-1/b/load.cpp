#include <stdlib.h>
#include <string.h>
using namespace std;

#include "load.h"

namespace {
const int N = 4e4+7, W = 18;
int ch[N][2];
int fa[N], f[W][N];
int lst[N];
int id[N], tid = -1;
int rnk[N];
int d[N];
void dfs(int u, int fa) {
  if (u < 0) return;
  f[0][u] = fa;
  d[u] = d[fa] + 1;
  dfs(ch[u][0], u);
  id[++tid] = u;
  dfs(ch[u][1], u);
}
int lca(int u, int v) {
  if (d[u] < d[v]) swap(u, v);
  int x = d[u] - d[v];
  for (int i = 0; i < W; ++i) if ((x>>i)&1) u = f[i][u];
  if (u == v) return u;
  for (int i = W - 1; i >= 0; --i) if (f[i][u] != f[i][v]) u = f[i][u], v = f[i][v];
  return f[0][u];
}
}

std::vector<int> solve_queries(int subtask_id, int n,
        const std::string &bits,
        const std::vector<int> &a, const std::vector<int> &b) {
  for (int i = 0; i < n; ++i) ch[i][0] = ch[i][1] = -1;
  for (int i = 0; i < n + 5; ++i) lst[i] = -1;
  int u = n;
  int tot = -1;
  for (auto cur : bits) {
    if (cur == '0') {
      ++tot;
      ch[u][0] = tot;
      if (lst[u] != -1) ch[lst[u]][1] = tot;
      lst[u] = tot;
      fa[tot] = u;
      u = tot;
    } else {
      u = fa[u];
    }
  }
  dfs(0, 0);
  for (int i = 0; i < n; ++i) rnk[id[i]] = i;
  for (int i = 1; i < W; ++i) for (int j = 0; j < n; ++j) {
    f[i][j] = f[i-1][f[i-1][j]];
  }
  std::vector<int> ans;
  for (int i = 0; i < a.size(); ++i) ans.push_back(rnk[lca(id[a[i]], id[b[i]])]);
  return ans;
}
