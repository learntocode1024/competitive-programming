#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

const int N = 1e5+5;
vector<int> g[N];
int n, m, cnt;
bool vis[N];
int s = 0, t = 0;

inline void dfs(int u) {
  vis[u] = 1;
  for (auto v : g[u]) {
    if (v == t) ++cnt;
    else if (!vis[v]) dfs(v);
  }
}

inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  int c1 = 0, c2 = 0;
  FOR(u, 1, n + 1) {
    if (g[u].size() & 1) {
      println("No");
      return;
    }
    if (g[u].size() >= 6) c1 = 1;
    if (g[u].size() == 4) {
      ++c2;
      if (!s) s = u;
      else t = u;
    }
  }
  if (c1 || c2 > 2) {
    println("Yes");
  } else {
    if (c2 == 2) {
      dfs(s);
      if (cnt < 4) println("Yes");
      else println("No");
    } else println("No");
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  solve();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */

