// Original Author: misaka18931
// Date: 03-03-21
// tag:
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define init(T, x)                                                             \
  T x;                                                                         \
  cin >> x;
#define printb(x)                                                              \
  if ((bool)x)                                                                 \
    printf("YES");                                                             \
  else                                                                         \
    printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define min(X, Y) ((X) < (Y) ? (X) : (Y))
#define max(X, Y) ((X) > (Y) ? (X) : (Y))
#define MX 605
const LL mod = 998244353l;

int n, m;

#define add_edge(X, Y)                                                         \
  to[++tot] = Y;                                                               \
  nxt[tot] = head[X];                                                          \
  head[X] = tot;
int head[MX], to[MX * 2], nxt[MX * 2], tot;
int dist[MX][MX];

queue<int> q;
void bfs(int root, int dist[]) {
  q.push(root);
  dist[root] = 1;
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = nxt[i]) {
      int &v = to[i];
      if (v != root && !dist[v]) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
}

LL ans[MX][MX];

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 0, a, b; i < m; ++i) {
    cin >> a >> b;
    add_edge(a, b) add_edge(b, a)
  }
  for (int i = 1; i <= n; ++i)
    bfs(i, dist[i]);
  for (int u = 1; u <= n; ++u) {
    ans[u][u] = 1;
    for (int v = 1; v <= n; ++v) {
      if (v == u)
        continue;
      int cnt = 0;
      for (int i = head[v]; i; i = nxt[i]) {
        cnt += (dist[u][to[i]] == dist[u][v] - 1);
      }
      ans[u][u] = ans[u][u] * cnt % mod;
    }
  }
  for (int u = 1; u <= n; ++u) {
    for (int v = u + 1; v <= n; ++v) {
      int cnt_inpath = 0;
      for (int i = 1; i <= n; ++i)
        cnt_inpath = cnt_inpath + (dist[u][i] + dist[v][i] == dist[u][v] + 1);
      LL ans = 1;
      if (cnt_inpath != dist[u][v])
        ans = 0;
      for (int t = 1; ans && t <= n; ++t) {
        if (dist[u][t] + dist[v][t] == dist[u][v] + 1) continue;
        int cnt = 0;
        for (int i = head[t]; i; i = nxt[i]) {
          cnt += (dist[u][to[i]] == dist[u][t] - 1) *
                 (dist[v][to[i]] == dist[v][t] - 1);
        }
        ans = ans * cnt % mod;
      }
      ::ans[u][v] = ::ans[v][u] = ans;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << ans[i][j] << ' ';
    }
    cout << endl;
  }
  return 0;
}
