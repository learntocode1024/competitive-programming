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

#define MULTI
const int N = 3005;
vector<int> g[N];
int d[N], son[N], l[N];
int n;
int f[N];

void dfs(int u, int fa) {
  for (auto v : g[u]) if (v != fa) {
    d[v] = d[u] + 1;
    dfs(v, u);
    if (l[v] > l[son[u]]) son[u] = v;
  }
  int ll = -1;
  for (auto v : g[u]) if (v != fa && v != son[u]) {
    chkmax(ll, l[v]);
  }
  ++ll;
  l[u] = l[son[u]] + 1;
  if (ll+d[u]) chkmax(f[ll+d[u]-1], l[u]+ll);
}

inline void solve() {
  FOR(i, 0, n + 1) d[i] = son[i] = l[i] = f[i]  = 0;
  l[0] = -1;
  cin >> n;
  FOR(i, 1, n + 1) g[i].clear();
  for (int i = 1; i < n; ++i) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  // FOR(i, 0, n) f[i] = i;
  dfs(1, 0);
  int mxd = l[1];
  ROF(i, 0, n-1) chkmax(f[i], f[i+1]);
  int ans = 0;
  for (int x = 1; x <= n; ++x) {
    while (ans < mxd && ans < (f[ans]+1)/2+x) ++ans;
    cout << ans << " \n"[x==n];
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

