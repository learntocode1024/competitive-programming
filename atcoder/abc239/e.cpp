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
const int N = 1e5+5, W = 60;
int a[N][W], c[N], x[N];
vector<int> g[N];
int n, q;
int tmp[W];

void dfs(int u, int fa) {
  c[u] = 1;
  a[u][0] = x[u];
  for (auto v : g[u]) if (v != fa) {
    dfs(v, u);
    merge(a[u], a[u] + c[u], a[v], a[v] + c[v], tmp);
    c[u] = min(c[u] + c[v], 20);
    FOR(i, 0, c[u]) a[u][i] = tmp[i];//, cout << tmp[i] << " \n"[i==c[u]-1];
  }
}

inline void solve() {
  rd(n, q);
  FOR(i, 1, n + 1) cin >> x[i], x[i] = -x[i];
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs(1, 0);
  FOR(i, 0, q) {
    int v, k;
    rd(v, k);
    println(-a[v][k-1]);
  }
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

