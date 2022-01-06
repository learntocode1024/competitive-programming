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
const int N = 2e6+5;
const int p = 998244353;
int n, x;
vector<pii> g[N];

int Q_pow(i64 x, int y) {
  i64 ret = 1;
  while (y) {
    if (y & 1)
      ret = ret * x % p;
    x = x * x % p;
    y >>= 1;
  }
  return ret;
}

inline i64 inv(int x) { return Q_pow(x, p - 2); }
namespace sub1 {
int c[N];
bool v[N];
i64 q[N], t = 1;
i64 s[N];
i64 f[N], g[N];

void work() {
  int c0 = -1;
  FOR(i, 1, n + 1) if (g[i].size() == 1) {
    c0 = i;
    break;
  }
  if (c0 == -1) return;
  v[c0] = 1;
  s[0] = 1;
  while (t < n) {
    for (auto nxt : g[c0]) {
      if (!v[nxt.fi]) {
        q[t] = nxt.se;
        s[t] = (p + 1 - q[t]) * s[t - 1] % p;
        ++t;
        c0 = nxt.fi;
        break;
      }
    }
  }
  i64 ans = 0;
  q[0] = 1;
  FOR(i, 0, x) g[i] = 1;
  for (int i = x; i < n; ++i) {
    f[i] = s[i] * inv(s[i - x]) % p * q[i - x] % p;
    if (i > x) f[x] = f[x] * g[i - x - 1] % p;
    g[i] = (g[i - 1] - f[i] +  p )% p;
    ans = (ans + f[i]) % p;
  }
  println(ans);
}

}

namespace sub2 {
int d[N];
int dfs(int u, int fa) {
  d[u] = d[fa] + 1;
  int ret = u;
  for (auto v : g[u]) {
    if (v.fi != fa) {
      int to = dfs(v.fi, u);
      if (d[to] > d[ret]) ret = to;
    }
  }
  return ret;
}
inline void work() {
  d[0] = -1;
  int r = dfs(1, 0);
  println((d[dfs(r, 0)] <= x) ? 1 : 0);
}
}

inline void solve() {
  int da, db;
  rd(n, da, db);
  if (da <= db * 2) println(1);
  else {
    x = db << 1;
    bool t2 = 1;
    FOR(i, 1, n) {
      int u, v, w;
      rd(u, v, w);
      w = 61689804ll * w % p;
      if (w) t2 = 0;
      g[u].eb(v, w);
      g[v].eb(u, w);
    }
    if (t2) sub2::work();
    else sub1::work();
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

