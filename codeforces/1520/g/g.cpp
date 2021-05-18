/*
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define printb(x)                                                              \
  if ((bool)x)                                                                 \
    printf("YES");                                                             \
  else                                                                         \
    printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 4000005

LL a[MX], b[MX], c[MX];

LL w;
int m, n;
int adj[4];

queue<int> q;
void bfs(int init, LL* dist) {
  dist[n * m] = INT64_MAX;
  if (a[init] > 0) dist[n * m] = a[init];
  q.push(init);
  while(q.size()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int v = u + adj[i];
      if (v < 0 || v >= n * m || (v % m != u % m && v / m != u / m)) continue;
      if (a[v] == -1 || dist[v] != 0) continue;
      dist[v] = dist[u] + w;
      if (a[v] > 0) dist[n * m] = min(dist[n * m], dist[v] + a[v]);
      q.push(v);
    }
  }
}

void solve() {
  cin >> n >> m >> w;
  for (int i = 0; i < n * m; ++i) {
    cin >> a[i];
  }
  adj[0] = 1;
  adj[1] = -1;
  adj[2] = m;
  adj[3] = -m;
  bfs(0, b);
  bfs(n * m - 1, c);
  LL ans = INT64_MAX;
  if (b[n * m - 1] > 0) ans = min(ans, b[m * n - 1]);
  if (b[m * n] != INT64_MAX && c[m * n] != INT64_MAX) ans = min(ans, b[n * m] + c[n * m]);
  if (ans != INT64_MAX) cout << ans << endl;
  else cout << -1 << endl;
}

int main() {
  solve();
  return 0;
}
