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

const int N = 2e5+5;
typedef multiset<int> vi;
int n, k;
vector<int> g[N];
multiset<int> f[N];
int sz[N], son[N];

void pre(int u, int fa) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v == fa) continue;
    pre(v, u);
    sz[u] += sz[v];
    if (sz[v] > sz[son[u]]) son[u] = v;
  }
}

inline void merge(vi &a, vi &b) {
  for (auto v : b) {
    a.insert(v);
  }
  b.clear();
}

void dfs(int u, int fa) {
  if (g[u].size() == 1 && g[u][0] == fa) {
    f[u] = {1};
    return;
  }
  dfs(son[u], u);
  f[u].swap(f[son[u]]);
  for (auto v : g[u]) {
    if (v == fa || v == son[u]) continue;
    dfs(v, u);
    merge(f[u], f[v]);
    f[v].clear();
  }
  int s = *(f[u].end()--);
  f[u].erase(--f[u].end());
  f[u].insert(s+1);
}

inline void solve() {
  rd(n, k);
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  pre(1, 0);
  dfs(1, 0);
  i64 ans = INT64_MIN;
  vector<int> ff(1,0);
  for (auto v : f[1]) {
    ff.pb(ff.back() + v);
  }
  int c = ff.size() - 1;
  FOR(i, 0, k + 1) {
    i64 cur = 1ll * n * i - 1ll * i * i;
    int t = ff[max(c - i, 0)];
    t = min(t, n / 2);
    cur -= 1ll * n * t - 1ll * t * t;
    chkmax(ans, cur);
  }
  println(ans);
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

