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

//#define MULTI
const int N = 2e5+5;
int n, x, y, d[N], e[N], f[N];
bool s[N];
vector<int> g1[N], g2[N];
int ans = 0;

void dfs1(int u, int fa) {
  if (e[u] >= d[u]) return;
  if (s[u]) {
    ans = -1;
    return;
  } else if (ans != -1) {
    chkmax(ans, d[u]);
  }
  for (auto v : g1[u]) if (fa != v) {
    e[v] = e[u] + 1;
    dfs1(v, u);
  }
}

void dfs2(int u, int fa) {
  for (auto v : g2[u]) if (v != fa) {
    f[v] = u;
    d[v] = d[u] + 1;
    dfs2(v, u);
  }
}

inline void solve() {
  rd(n, x, y);
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g1[u].pb(v);
    g1[v].pb(u);
  }
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g2[u].pb(v);
    g2[v].pb(u);
  }
  dfs2(y, 0);
  FOR(u, 1, n + 1) {
    for (auto v : g1[u]) {
      if (!(f[u] == v || f[v] == u || f[f[u]] == v || f[f[v]] == u || f[u] == f[v])) s[u] = s[v] = 1;
    }
  }
  dfs1(x, 0);
  println(ans == -1 ? -1 : ans*2);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
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

