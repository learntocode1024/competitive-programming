// Original Author: misaka18931
// Date: 01-04-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#define MX 30//0005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

int head[MX], to[MX * 2], nxt[MX * 2], tot;
int col[MX], cnt;
bool vis[MX];

inline void add_edge(const int &a, const int &b) {
  to[++tot] = b;
  nxt[tot] = head[a];
  head[a] = tot;
}

void count(int u) {
  ++cnt;
  vis[u] = true;
  for (int i = head[u]; i; i = nxt[i]) {
    const int &v = to[i];
    if (!vis[v]) {
      count(v);
    }
  }
}

bool dfs(int u, int color) {
  col[u] = color;
  for (int i = head[u]; i; i = nxt[i]) {
    const int &v = to[i];
    if (!col[v]) {
      if (!dfs(v, 3 - color)) return false;
    } else {
      if (col[v] == color) return false;
    }
  }
  return true;
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0, a, b; i < m; ++i) {
    cin >> a >> b;
    add_edge(a, b);
    add_edge(b, a);
  }
  count(1);
  bool flag = true;
  // for (int i = 1; flag && i <= n; ++i) {
  //   if (!col[i] && !dfs(i, 2)) flag = false;
  // }
  if (dfs(1, 2) && cnt == n) {
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      if (col[i] == 2) ++ans;
    }
    cout << "YES\n" << ans << "\n";
    for (int i = 1; i <= n; ++i) {
      if (col[i] == 2)
       cout << i << " ";
    }
    cout << endl;
  } else cout << "NO" << endl;
  for (int i = 0; i < n + 5; ++i) {
    vis[i] = col[i] = head[i] = 0;
  }
  for (int i = 0; i < 2 * n + 10; ++i) {
    to[i] = nxt[i] = 0;
  }
  cnt = tot = 0; // recover
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
