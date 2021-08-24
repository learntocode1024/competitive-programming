#include <algorithm>
#include <iostream>
#include <vector>

#include "io"
#include "utils"
const int N = 100005, bitln = 50;
int n, m;
i64 a[N];
int fa[bitln][N], d[N];
vector<int> G[N];

void lca_init() {
  for (int i = 1; i < 32 - __builtin_clz(n); ++i) {
    for (int j = 1; j <= n; ++j) {
      fa[i][j] = fa[i - 1][fa[i - 1][j]];
    }
  }
}

int lca(int u, int v) {
  if (d[u] < d[v]) swap(u, v);
  int x = d[u] - d[v];
  for (int i = 20; i >= 0; --i) {
    if ((x >> i) & 1) u = fa[i][u];
  }
  if (u == v) return u;
  for (int i = 20; i >= 0; --i) {
    if (fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
  }
  return fa[0][u];
}

struct trie {
  int ch[N * bitln][2], cnt[N * bitln], rts[N];
  int tot;
  int cpy(int p) {
    int ret = ++tot;
    cnt[ret] = cnt[p];
    ch[ret][0] = ch[p][0];
    ch[ret][1] = ch[p][1];
    return ret;
  }
  void insert(int fa, int to, i64 x) {
    int p = cpy(rts[fa]);
    rts[to] = p;
    ++cnt[p];
    for (int i = bitln - 2; i >= 0; --i) {
      ch[p][(x >> i) & 1] = cpy(ch[p][(x >> i) & 1]);
      p = ch[p][(x >> i) & 1];
      ++cnt[p];
    }
  }
  i64 kth(int u, int v, int k) {
    int x = lca(u, v);
    int x1 = fa[0][x];
    i64 ret = 0;
    int p = rts[u], q = rts[v], r = rts[x], s = rts[x1];
    if (cnt[p] + cnt[q] - cnt[r] - cnt[s] < k) throw "shit";
    for (int i = bitln - 2; i >= 0; --i) {
      int cl = cnt[ch[p][0]] + cnt[ch[q][0]] - cnt[ch[r][0]] - cnt[ch[s][0]];
      if (cl >= k) {
        p = ch[p][0];
        q = ch[q][0];
        r = ch[r][0];
        s = ch[s][0];
      } else {
        p = ch[p][1];
        q = ch[q][1];
        r = ch[r][1];
        s = ch[s][1];
        k -= cl;
        ret |= 1ll << i;
      }
    }
    return ret;
  }
} T;

void dfs(int u, int fa) {
  d[u] = d[fa] + 1;
  ::fa[0][u] = fa;
  T.insert(fa, u, a[u]);
  for (auto v : G[u]) {
    if (v != fa) dfs(v, u);
  }
}

int main() {
  IO::init_in();
  n = rd(), m = rd();
  FOR(i, 1, n + 1) a[i] = rdll();
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  dfs(1, 0);
  lca_init();
  i64 last = 0;
  FOR(i, 0, m) {
    int u = rdll() ^ last, v = rd(), k = rd();
    cout << (last = T.kth(u, v, k)) << '\n';
  }
}