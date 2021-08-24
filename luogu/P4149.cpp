#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 200005;

vector<pii> G[N];
int n, k;
int ans = 1e8;
bool vis[N];
int sz[N], wei[N];

int tot, rt;
void centroid(int u, int fa) {
  sz[u] = 1;
  wei[u] = 0;
  for (auto v : G[u]) {
    if (vis[v.fi] || v.fi == fa) continue;
    centroid(v.fi, u);
    sz[u] += sz[v.fi];
    chkmax(wei[u], sz[v.fi]);
  }
  chkmax(wei[u], tot - sz[u]);
  if (wei[u] < wei[rt]) rt = u;
}

int buc[1000006];
int re[1000006], tt;
int len[N], wlen[N];

void getdis(int u, int fa, int w) {
  len[u] = len[fa] + 1;
  wlen[u] = wlen[fa] + w;
  // if (wlen[u] <= k) {
    // chkmin(ans, buc[k - wlen[u]] + len[u]);
    // chkmin(buc[wlen[u]], len[u]);
  //   re[++tt] = wlen[u];
  // }
  if (wlen[u] <= k) re[++tt] = u;
  for (auto v : G[u]) {
    if (!vis[v.fi] && v.fi != fa)
      getdis(v.fi, u, v.se);
  }
}

void getans(int u) {
  len[u] = wlen[u] = 0;
  int pb;
  for (auto v : G[u]) {
    if (!vis[v.fi]) {
      pb = tt;
      getdis(v.fi, u, v.se);
      FOR(i, pb + 1, tt + 1) {
        chkmin(ans, buc[k - wlen[re[i]]] + len[re[i]]);
      }
      FOR(i, pb + 1, tt + 1) {
        chkmin(buc[wlen[re[i]]], len[re[i]]);
      }
    }
  }
  while (tt) buc[wlen[re[tt--]]] = 1e8;
}

void reduce(int u) {
  vis[u] = 1;
  getans(u);
  for (auto v : G[u]) {
    if (!vis[v.fi]) {
      tot = sz[v.fi];
      rt = 0;
      centroid(v.fi, u);
      reduce(rt);
    }
  }
}

void solve() {
  n = rd(), k =rd();
  FOR(i, 0, k) buc[i + 1] = 1e8;
  FOR(i, 1, n) {
    int u = rd() + 1, v = rd() + 1, w = rd();
    G[u].eb(v, w);
    G[v].eb(u, w);
  }
  wei[0] = 1e8;
  tot = n, rt = 0;
  centroid(1, 0);
  reduce(rt);
  cout << (ans > n ? -1 : ans) << '\n';
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
