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
vector<int> g[N];
i64 a[N], b[N], c[N];
int n;

bool ok = 1;

i64 d1(int u, int fa) {
  i64 ret = 0;
  if (g[u].size() == 1 && g[u][0] == fa) return a[u];
  for (auto v : g[u]) if (v != fa) ret += d1(v, u);
  b[u] = a[u] - ret;
  if (b[u] > 0) ok = 0;
  return ret;
}

i64 d2(int u, int fa) {
  i64 ret = 0;
  for (auto v : g[u]) if (v != fa) ret += d2(v, u) * 2;
  b[u] += ret;
  if (b[u] > 0) ok = 0;
  b[u] = -b[u];
  return b[u];
}

void d3(int u, int fa) {
  if (g[u].size() == 1 && g[u][0] == fa) {
    c[u] = a[u];
    return;
  }
  for (auto v : g[u]) if (v != fa) {
    d3(v, u);
    c[u] += c[v];
  }
  int dif = -1;
  for (auto v : g[u]) if (v != fa) {
    if (c[v] > c[u] / 2) dif = c[u] - c[v];
  }
  if (dif == -1) dif = c[u] / 2;
  if (dif < b[u]) ok = 0;
  c[u] -= b[u] * 2;
}

inline void solve() {
  rd(n);
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  int rt = -1;
  FOR(i, 1, n + 1) if (g[i].size() > 1) {
    rt = i;
    break;
  }
  d1(rt, 0);
  d2(rt, 0);
  d3(rt, 0);
  if (c[rt]) ok = 0;
  println(ok ? "YES" : "NO");
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

