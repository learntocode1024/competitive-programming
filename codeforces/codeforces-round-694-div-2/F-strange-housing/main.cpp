// Original Author: misaka18931
// Date: 01-04-21
// tag: dfs, greedy, dyeing
// AC

#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#define MX 300005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;

int head[MX], to[MX * 2], nxt[MX * 2], tot;
int col[MX];

inline void add_edge(const int &a, const int &b) {
  to[++tot] = b;
  nxt[tot] = head[a];
  head[a] = tot;
}

void dfs(int u) {
  col[u] = 2;
  for (int i = head[u]; i; i = nxt[i]) {
    const int &v = to[i];
    if (col[v] == 2) {
      col[u] = 1;
    }
  }
  for (int i = head[u]; i; i = nxt[i]) {
    const int &v = to[i];
    if (!col[v]) {
      dfs(v);
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n + 5; ++i) {
    col[i] = head[i] = 0;
  }
  for (int i = 0; i < 2 * n + 10; ++i) {
    to[i] = nxt[i] = 0;
  }
  tot = 0;
  for (int i = 0, a, b; i < m; ++i) {
    cin >> a >> b;
    add_edge(a, b);
    add_edge(b, a);
  }
  dfs(1);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (!col[i]) {
      cout << "NO" << endl;
      return;
    }
    if (col[i] == 2) ++ans;
  }
  cout << "YES\n" << ans << "\n";
  for (int i = 1; i <= n; ++i) {
    if (col[i] == 2) {
      cout << i << " ";
    }
  }
  cout << endl;
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
