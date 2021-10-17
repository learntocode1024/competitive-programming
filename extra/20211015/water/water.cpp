#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
typedef pair<i64, pii> plpii;
#define FOR(i, j, k) for (int i = j; i < k; ++i)
#define se second
#define fi first
const int N = 305;
int n, m;
i64 h[N][N];
bool v[N][N];
priority_queue<plpii> pq;
i64 a[N][N];
const int dx[4] = { 1, -1, 0, 0 };
const int dy[4] = { 0, 0, 1, -1 };

inline void run_height() {
  plpii ori;
  ori.fi = ori.se.fi = ori.se.se = 0;
  FOR(i, 0, n + 2) FOR(j, 0, m + 2) h[i][j] = 1e17;
  h[0][0] = 0;
  pq.push(ori);
  while (!pq.empty()) {
    pii u = pq.top().se;
    pq.pop();
    if (v[u.fi][u.se]) continue;
    v[u.fi][u.se] = 1;
    i64 w = h[u.fi][u.se];
    for (int i = 0; i < 4; ++i) {
      pii v = u;
      v.fi += dx[i];
      v.se += dy[i];
      if (v.fi < 0 || v.fi > n + 1 || v.se < 0 || v.se > m + 1) continue;
      i64 wto = max(w, 1ll * a[v.fi][v.se]);
      if (wto < h[v.fi][v.se]) {
        h[v.fi][v.se] = wto;
        pq.push({-wto, v});
      }
    }
  }
}

int main () {
  freopen("water.in", "r", stdin);
  freopen("water.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  FOR(i, 1, n + 1) FOR(j, 1, m + 1) cin >> a[i][j];
  run_height();
  FOR(i, 1, n + 1) {
    FOR(j, 1, n + 1) {
      cout << h[i][j] - a[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
