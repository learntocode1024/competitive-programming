#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

const int N = 200005;
int a[N], c[N];
vector<int> G[N], q[N];
int n, m;
int x[N], y[N], t[N], T[N], f[18][N];

int get(int x) {
  int ret = 0;
  while (x) {
    ret += c[x];
    x -= x & -x;
  }
  return ret;
}

void ch(int x, int v) {
  while (x <= n) {
    c[x] += v;
    x += x & -x;
  }
}

int d[N], s[N], tot, dep[N];
void dfs(int u) {
  d[u] = ++tot;
  s[u] = 1;
  for (auto v : G[u]) {
    dep[v] = dep[u] + 1, dfs(v), s[u] += s[v];
  }
}

int lca(int a, int b) {
  if (dep[a] < dep[b]) swap(a, b);
  int x = dep[a] - dep[b];
  ROF(i, 0, 18) {
    if ((x >> i) & 1) a = f[i][a];
  }
  if (a == b) return a;
  ROF(i, 0, 18) {
    if (f[i][a] != f[i][b]) a = f[i][a], b = f[i][b];
  }
  return f[0][a];
}

int ans[N], ss[N];
void solve() {
  n = rd();
  int rt;
  FOR(u, 1, n + 1) {
    int v = rd();
    f[0][u] = v;
    if (!v) rt = u;
    else {
      G[v].pb(u);
    }
  }
  m = rd();
  dep[rt] = 1;
  dfs(rt);
  FOR(i, 1, 18) {
    FOR(j, 1, n + 1) {
      f[i][j] = f[i - 1][f[i - 1][j]];
    }
  }
  FOR(i, 0, m) {
    T[i] = rd();
    if (T[i] == 2) {
      t[i] = rd();
      ans[i] = -1;
    } else {
      x[i] = rd();
      y[i] = rd();
      q[max(0, i - rd())].pb(i);
    }
  }
  FOR(i, 0, m) {
    for (auto p : q[i]) {
      int r = lca(x[p], y[p]);
      ss[p] = dep[x[p]] + dep[y[p]] - dep[r] - dep[f[0][r]];
      ans[p] = get(d[x[p]]) + get(d[y[p]]) - get(d[r]) - get(d[f[0][r]]);
    }
    if (T[i] == 2) {
      ch(d[t[i]], 1);
      ch(d[t[i]] + s[t[i]], -1);
    }
  }
  FOR(i, 0, m) {
    if (ans[i] != -1) cout << ss[i] << ' ' << ans[i] << '\n';
  }
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
