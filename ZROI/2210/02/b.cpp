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
typedef pair<int, i64> pil;
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
const i64 N = 3.5e5+5;
i64 n;
typedef pair<i64, i64> pll;
map<pil, pll> G;
int low[N], p[N], tot;
pll cnt[N];

pll g(int k, i64 n) {
  if (k == 1) {
    return {n/4-1+((n&3)>=1), n/4+((n&3)>=3)};
  }
  if (G.find({k, n}) != G.end()) return G[{k, n}];
  i64 c1 = 0, c2 = 0;
  pll x = g(k-1, n), y = {0, 0}, z = {0, 0};
  if (n >= 1ll * p[k] * p[k]) {
    y = g(k-1, n / p[k]), z = g(k-1, p[k-1]);//cnt[k-1];
  }
  if ((p[k] & 3) == 1) {
    c1 = x.fi - y.fi + z.fi;
    c2 = x.se - y.se + z.se;
  } else {
    c1 = x.fi - y.se + z.se;
    c2 = x.se - y.fi + z.fi;
  }
  G[{k, n}] = {c1, c2};
  return {c1, c2};
}

inline void solve() {
  FOR(i, 2, N) {
    if (!low[i]) {
      low[i] = p[++tot] = i;
      if ((i & 3) == 1) ++cnt[tot].fi;
      else if (i != 2) ++cnt[tot].se;
    }
    for (int j = 1; j <= tot && p[j] <= low[i] && i * p[j] < N; ++j) {
      low[p[j] * i] = p[j];
    }
  }
  FOR(i, 3, N) {
    cnt[i].fi += cnt[i-1].fi;
    cnt[i].se += cnt[i-1].se;
  }
  // for (int i = 10; i <= 100; i += 10) {
  //   int k = 1;
  //   while (p[k+1] * p[k+1] <= i) ++k;
  //   println(g(k, i).fi, g(k, i).se);
  // }
  // return;
  cin >> n;
  int k0 = 1, k1 = 1, k2 = 1;
  while (1ll * p[k0+1] * p[k0+1] <= n) ++k0;
  while (1ll * p[k1+1] * p[k1+1] <= n/4) ++k1;
  while (1ll * p[k2+1] * p[k2+1] <= n/16) ++k2;
  pll c1 = g(k1, n/4), c2 = g(k2, n/16);
  int ans = g(k0, n).se + c1.fi + c1.se + c2.fi + c2.se;
  println(ans+2);
  
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

