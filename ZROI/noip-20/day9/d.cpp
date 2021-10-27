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

const int N = 55;
int n, p, q;
int d[N][N];
bool vis[N];
vector<int> g[N];

void dfs(int *d, int u, int fa) {
  for (auto v : g[u]) {
    if (v != fa) {
      d[v] = d[u] + 1;
      dfs(d, v, u);
    }
  }
}

int dst;
int mrk(int u, int fa) {
  if (u == dst) {
    if (vis[u]) return 2;
    vis[u] = 1;
    return 1;
  }
  for (auto v : g[u]) {
    if (v != fa) {
      int rt = mrk(v, u);
      if (rt == 2) return 2;
      else if (rt == 1) {
        if (vis[u]) return 2;
        vis[u] = 1;
        return 1;
      }
    }
  }
  return 0;
}

inline void solve() {
  cin >> n >> p >> q;
  if (n > 50) return;
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  ++n;
  FOR(i, 1, n) dfs(d[i], i, 0);
  int ans = 0;
  FOR(i, 1, n) FOR(j, i + 1, n) FOR(k, 1, n) FOR(l, k + 1, n) {
    if (d[i][j] == p && d[k][l] == q && i != k && i != l && j != k && j != l) {
      dst = j;
      mrk(i, 0);
      dst = l;
      if (mrk(k, 0) == 1) {
        //println(i, j, k, l);
        ans += 4;
      }
      FOR(i, 1, n) vis[i] = 0;
    }
  }
  cout << ans % 998244353 << '\n';
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
