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
const int N = 1e5+5;
u32 f[N];
vector<int> g[N];
int n;

void dfs(int u, int fa) {
  u32 c1 = 0, c2 = 0;
  for (auto v : g[u]) if (v != fa) {
    dfs(v, u);
    c2 |= c1 & f[v];
    c1 |= f[v];
    c1 &= ~c2;
  }
  if (!c1 && !c2) f[u] = 1;
  else {
    u32 U = 0;
    if (c2) U = (1u << (32 - __builtin_clz(c2))) - 1;
    U |= c1;
    u32 cur = 1u << __builtin_ctz(~U);
    int rcur = ~(cur-1);
    f[u] = rcur&(cur|c1|c2);
  }
}

inline void solve() {
  cin >> n;
  FOR(i, 1, n) {
    int u, v;
    rd(u,v);
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs(1, 0);
  println(31-__builtin_clz(f[1]));
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

